/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "SerialCommand.h"
#include "ArgType.h"

#include <QVariant>


SerialCommand::SerialCommand(
	const QString & command,
	const QString & name,
	const QRegularExpression & responseRegex,
	const QList<QByteArray> & expectedResponses,
	const int & nbExpectedBytes,
	const SerialOperationMode::BlockingMode & blockingMode,
	const SerialOperationMode::FluxMode & fluxMode,
	const QString & terminator,
	const int & nbOfArgs,
	const QString & argsSeparator,
	const IOType & ioType,
	const QString & family,
	const QString & shortDescription,
	const QString & description,
	const QString & tooltip
) :
	m_command{ command.toLatin1() },
	m_name{ name },
	m_responseRegex{ responseRegex },
	m_expectedResponses{ expectedResponses },
	m_nbExpectedBytes{ nbExpectedBytes },
	m_operationMode{ blockingMode, fluxMode },
	m_terminator{ terminator },
	m_numberOfArgs{ nbOfArgs },
	m_argsSeparator{ argsSeparator },
	m_family{ family },
	m_shortDescription{ shortDescription },
	m_description{ description },
	m_ioType{ ioType },
	m_toolTip{ tooltip }
{
}

SerialCommand::SerialCommand(
	const QString & command,
	const QString & name,
	const QRegularExpression & responseRegex,
	const SerialOperationMode::BlockingMode & blockingMode,
	const SerialOperationMode::FluxMode & fluxMode,
	const QString & terminator,
	const int & nbOfArgs,
	const QString & argsSeparator,
	const IOType & ioType,
	const QString & family,
	const QString & shortDescription,
	const QString & description,
	const QString & tooltip
) :
	SerialCommand(
		command,
		name,
		responseRegex,
		QList<QByteArray>(),
		-1,
		blockingMode,
		fluxMode,
		terminator,
		nbOfArgs,
		argsSeparator,
		ioType,
		family,
		shortDescription,
		description,
		tooltip
	)
{
}

SerialCommand::SerialCommand(
	const QString & command,
	const QString & name,
	const QByteArrayList & expectedResponses,
	const SerialOperationMode::BlockingMode & blockingMode,
	const SerialOperationMode::FluxMode & fluxMode,
	const QString & terminator,
	const int & nbOfArgs,
	const QString & argsSeparator,
	const IOType & ioType,
	const QString & family,
	const QString & shortDescription,
	const QString & description,
	const QString & tooltip
) :
	SerialCommand(
		command,
		name,
		QRegularExpression(),
		expectedResponses,
		-1,
		blockingMode,
		fluxMode,
		terminator,
		nbOfArgs,
		argsSeparator,
		ioType,
		family,
		shortDescription,
		description,
		tooltip
	)
{
}

SerialCommand::SerialCommand(
	const QString & command,
	const QString & name,
	const int & nbExpectedBytes,
	const SerialOperationMode::BlockingMode & blockingMode,
	const SerialOperationMode::FluxMode & fluxMode,
	const QString & terminator,
	const int & nbOfArgs,
	const QString & argsSeparator,
	const IOType & ioType,
	const QString & family,
	const QString & shortDescription,
	const QString & description,
	const QString & tooltip
) :
	SerialCommand(
		command,
		name,
		QRegularExpression(),
		QList<QByteArray>(),
		nbExpectedBytes,
		blockingMode,
		fluxMode,
		terminator,
		nbOfArgs,
		argsSeparator,
		ioType,
		family,
		shortDescription,
		description,
		tooltip
	)
{
}

SerialCommand::~SerialCommand()
{
}

inline bool SerialCommand::operator==(SerialCommand const& command) const
{
	return m_name == command.m_name && m_args == command.m_args;
}

inline bool SerialCommand::operator!=(SerialCommand const& command) const
{
	return m_name != command.m_name || m_args != command.m_args;
}


QByteArray SerialCommand::commandToSend() const
{
	QByteArray command = m_command;
	int i = 0;

	for (const SerialCommandArg & serialCmdArg : m_args)
	{
		const QVariant arg = serialCmdArg.getArg();
		const ArgType argType = serialCmdArg.getType();

		if (arg.isValid())
		{
			if (i > 0) {
				command += m_argsSeparator.toLatin1();
			}
			switch (argType)
			{
			case ArgType::String:
				command += arg.toString();
				break;
			case ArgType::Int:
			case ArgType::Double:
				command += QString::number(arg.toDouble(), 'g', 10);
				break;
			case ArgType::ByteArray:
				command += arg.toByteArray();
				break;
			}
			++i;
		}
	}
	if (m_terminator.length() > 0) {
		command += m_terminator.toLatin1();
	}
	return command;
}

void SerialCommand::addPushModeStopCommand(const SerialCommand * command) {
	m_pushModeStopCommands.append(command);
}

bool SerialCommand::stopsPushMode(const SerialCommand & command) const {
	for (auto stopCommand : m_pushModeStopCommands) {
		if (command == *stopCommand) {
			return true;
		}
	}
	return false;
}