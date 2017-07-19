/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "SerialCommand.h"
#include <QDebug>


SerialCommand::SerialCommand(QString command, QString name, IOType ioType, int nParam, bool isRawParam, SerialOperationMode::BlockingMode blockingMode, SerialOperationMode::FluxMode fluxMode, QString terminator, QString separator, QString family, QString shortDesc,
	QRegularExpression returnExp, QString desc, QString tooltip)
	: mIsString{ true },
	mNbBytesExpected{ -1 },
	mCommand{ command.toLatin1() },
	mName{ name },
	mNParam{ nParam },
	mIsRawParam{ isRawParam },
	mReturnExp{ returnExp },
	mSeparator{ separator },
	mTerminator{ terminator },
	mFamily{ family },
	mShortDesc{ shortDesc },
	mDesc{ desc },
	mToolTip{ tooltip },
	mOperationMode{ blockingMode, fluxMode },
	mIOType{ ioType }
{
	mCommand = command.toLatin1();
	if (tooltip == "") {
		mToolTip = shortDesc;
	}
	else {
		mToolTip = tooltip;
	}
}

SerialCommand::SerialCommand(QByteArray command, QString name, IOType ioType, int nParam, bool isRawParam, SerialOperationMode::BlockingMode blockingMode, SerialOperationMode::FluxMode fluxMode, QString terminator, QString separator, QString family, QString shortDesc,
	QList<QByteArray> expectedResponses, QString desc, QString tooltip)
	: mIsString{ false },
	mNbBytesExpected{ -1 },
	mCommand{ command },
	mName{ name },
	mNParam{ nParam },
	mIsRawParam{ isRawParam },
	mSeparator{ separator },
	mTerminator{ terminator },
	mFamily{ family },
	mShortDesc{ shortDesc },
	mDesc{ desc },
	mToolTip{ tooltip },
	mOperationMode{ blockingMode, fluxMode },
	mIOType{ ioType },
	mExpectedResponses{ expectedResponses }
{
	if (tooltip == "") {
		mToolTip = shortDesc;
	}
	else {
		mToolTip = tooltip;
	}
}

SerialCommand::SerialCommand(QByteArray command, QString name, IOType ioType, int nParam, bool isRawParam, SerialOperationMode::BlockingMode blockingMode, SerialOperationMode::FluxMode fluxMode, QString terminator, QString separator, QString family, QString shortDesc,
	int nbBytesExpected, QString desc, QString tooltip)
	: mIsString{ false },
	mCommand{ command },
	mName{ name },
	mNParam{ nParam },
	mIsRawParam{ isRawParam },
	mSeparator{ separator },
	mTerminator{ terminator },
	mFamily{ family },
	mShortDesc{ shortDesc },
	mDesc{ desc },
	mToolTip{ tooltip },
	mOperationMode{ blockingMode, fluxMode },
	mIOType{ ioType },
	mNbBytesExpected{ nbBytesExpected }
{
	if (tooltip == "") {
		mToolTip = shortDesc;
	}
	else {
		mToolTip = tooltip;
	}
}

SerialCommand::~SerialCommand()
{

}

QByteArray SerialCommand::commandToSend(const QList<QVariant> & params) const {
	QByteArray command = mCommand;
	int i = 0;
	for (const QVariant &param : params) {
		if (param.isValid()) {
			QString sParam;
			if (mIsRawParam)
			{
				command += param.toByteArray();
			}
			else if (param.canConvert<int>() || param.canConvert<double>()) {
				sParam = QString::number(param.toDouble(), 'g', 10);
			}
			else {
				sParam = param.toString();
			}
			if (i > 0) {
				command += mSeparator.toLatin1();
			}
			if (mIsString) {
				command += sParam.toLatin1();
			}
			else {
				command += sParam.toDouble();
			}
		}
		i++;
	}
	if (mTerminator.length() > 0) {
		command += mTerminator.toLatin1();
	}
	return command;
}

void SerialCommand::addPushModeStopCommand(SerialCommand const * command) {
	mPushModeStopCommands.append(command);
}

bool SerialCommand::stopsPushMode(SerialCommand const &command) const {
	for (auto stopCommand : mPushModeStopCommands) {
		qDebug() << command.name();
		qDebug() << stopCommand->name();
		if (command == *stopCommand) {
			return true;
		}
	}
	return false;
}

QByteArray SerialCommand::getFirstMatch(QByteArray const &buffer)
{
	if (mIsString)
	{
		QRegularExpressionMatch match = returnExp().match(buffer);
		if (match.hasMatch())
		{
			QString firstMatch = match.captured(0);
			return firstMatch.toLatin1();
		}
		return QByteArray();
	}
	else if (mNbBytesExpected != -1)
	{
		QByteArray response;
		if (mNbBytesExpected > 0) {
			response = buffer.left(mNbBytesExpected);
		}
		return response;
	}
	else
	{
		QByteArray response;
		int index = std::numeric_limits<int>::max();
		for (auto ba : mExpectedResponses)
		{
			if (buffer.indexOf(ba) != -1 && buffer.indexOf(ba) < index)
			{
				response = ba;
				index = buffer.indexOf(ba);
			}
		}
		return response;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
// GET
/////////////////////////////////////////////////////////////////////////////////////////

QRegularExpression SerialCommand::returnExp() const {
	// Si on utilise le protocole simplifie
	if (mReturnExp.match("").hasMatch()) {
		return QRegularExpression(mCommand + ".*" + mTerminator);
	}
	else {
		return mReturnExp;
	}
}