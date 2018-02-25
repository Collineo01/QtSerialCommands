/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "SerialCommand.h"

#include <QCoreApplication>
#include <QDebug>


SerialOperationMode::SerialOperationMode(BlockingMode blockingMode, FluxMode fluxMode)
	: mBlockingMode{ blockingMode }, mFluxMode{ fluxMode }
{
}


SerialOperationMode::SerialOperationMode()
{
}


SerialOperationMode::~SerialOperationMode()
{
}


SerialCommand::SerialCommand(QString command, QString name, IOType ioType, int nbOfArgs, bool argsAreRaw, SerialOperationMode::BlockingMode blockingMode, SerialOperationMode::FluxMode fluxMode, QString terminator, QString separator, QString family, QString shortDesc,
	QRegularExpression responseRegex, QString desc, QString tooltip)
	: m_IsString{ true },
	m_NbBytesExpected{ -1 },
	m_Command{ command.toLatin1() },
	m_Name{ name },
	m_NumberOfArgs{ nbOfArgs },
	m_ArgsAreRaw{ argsAreRaw },
	m_ResponseRegex{ responseRegex },
	m_Separator{ separator },
	m_Terminator{ terminator },
	m_Family{ family },
	m_ShortDesc{ shortDesc },
	m_Desc{ desc },
	m_ToolTip{ tooltip },
	m_OperationMode{ blockingMode, fluxMode },
	m_IOType{ ioType }
{
	m_Command = command.toLatin1();
	if (tooltip == "") {
		m_ToolTip = shortDesc;
	}
	else {
		m_ToolTip = tooltip;
	}
}

SerialCommand::SerialCommand(QByteArray command, QString name, IOType ioType, int nbOfArgs, bool argsAreRaw, SerialOperationMode::BlockingMode blockingMode, SerialOperationMode::FluxMode fluxMode, QString terminator, QString separator, QString family, QString shortDesc,
	QList<QByteArray> expectedResponses, QString desc, QString tooltip)
	: m_IsString{ false },
	m_NbBytesExpected{ -1 },
	m_Command{ command },
	m_Name{ name },
	m_NumberOfArgs{ nbOfArgs },
	m_ArgsAreRaw{ argsAreRaw },
	m_Separator{ separator },
	m_Terminator{ terminator },
	m_Family{ family },
	m_ShortDesc{ shortDesc },
	m_Desc{ desc },
	m_ToolTip{ tooltip },
	m_OperationMode{ blockingMode, fluxMode },
	m_IOType{ ioType },
	m_ExpectedResponses{ expectedResponses }
{
	if (tooltip == "") {
		m_ToolTip = shortDesc;
	}
	else {
		m_ToolTip = tooltip;
	}
}

SerialCommand::SerialCommand(QByteArray command, QString name, IOType ioType, int nbOfArgs, bool argsAreRaw, SerialOperationMode::BlockingMode blockingMode, SerialOperationMode::FluxMode fluxMode, QString terminator, QString separator, QString family, QString shortDesc,
	int nbBytesExpected, QString desc, QString tooltip)
	: m_IsString{ false },
	m_Command{ command },
	m_Name{ name },
	m_NumberOfArgs{ nbOfArgs },
	m_ArgsAreRaw{ argsAreRaw },
	m_Separator{ separator },
	m_Terminator{ terminator },
	m_Family{ family },
	m_ShortDesc{ shortDesc },
	m_Desc{ desc },
	m_ToolTip{ tooltip },
	m_OperationMode{ blockingMode, fluxMode },
	m_IOType{ ioType },
	m_NbBytesExpected{ nbBytesExpected }
{
	if (tooltip == "") {
		m_ToolTip = shortDesc;
	}
	else {
		m_ToolTip = tooltip;
	}
}

SerialCommand::~SerialCommand()
{

}

QByteArray SerialCommand::commandToSend() const {
	QByteArray command = m_Command;
	int i = 0;
	for (const QVariant &arg : m_Args) 
	{
		if (arg.isValid()) 
		{
			QString sArg;
			if (m_ArgsAreRaw)
			{
				command += arg.toByteArray();
			}
			else if (arg.canConvert<int>() || arg.canConvert<double>()) {
				sArg = QString::number(arg.toDouble(), 'g', 10);
			}
			else {
				sArg = arg.toString();
			}
			if (i > 0) {
				command += m_Separator.toLatin1();
			}
			if (m_IsString) {
				command += sArg.toLatin1();
			}
			else {
				command += sArg.toDouble();
			}
		}
		i++;
	}
	if (m_Terminator.length() > 0) {
		command += m_Terminator.toLatin1();
	}
	return command;
}

void SerialCommand::addPushModeStopCommand(SerialCommand const * command) {
	m_PushModeStopCommands.append(command);
}

bool SerialCommand::stopsPushMode(SerialCommand const &command) const {
	for (auto stopCommand : m_PushModeStopCommands) {
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
	if (m_IsString)
	{
		QRegularExpressionMatch match = responseRegex().match(buffer);
		if (match.hasMatch())
		{
			QString firstMatch = match.captured(0);
			return firstMatch.toLatin1();
		}
		return QByteArray();
	}
	else if (m_NbBytesExpected != -1)
	{
		QByteArray response;
		if (m_NbBytesExpected > 0) {
			response = buffer.left(m_NbBytesExpected);
		}
		return response;
	}
	else
	{
		QByteArray response;
		int index = std::numeric_limits<int>::max();
		for (auto ba : m_ExpectedResponses)
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

QRegularExpression SerialCommand::responseRegex() const {
	// Si on utilise le protocole simplifie
	if (m_ResponseRegex.match("").hasMatch()) {
		return QRegularExpression(m_Command + ".*" + m_Terminator);
	}
	else {
		return m_ResponseRegex;
	}
}