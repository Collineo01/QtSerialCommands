#pragma once

/*!	\class SerialCommand
*/


#include "qtserialcommands_global.h"

#include "SerialCommandArg.h"
#include "SerialOperationMode.h"
#include "IOType.h"
#include "MatchType.h"

#include <QString>
#include <QByteArray>
#include <QRegularExpression>
#include <QList>


class QTSERIALCOMMANDS_EXPORT SerialCommand
{
public:
	SerialCommand() {}

	SerialCommand(
		const QString & command,  									// What is actually sent to the device
		const QString & name, 										// getName
		const QRegularExpression & responseRegex,					// The response format we epxect
		const QByteArrayList & expectedResponses,					// The exact responses we can expect from the device
		const int nbBytesExpected,									// The exact number of bytes we expect from the device response
		const SerialOperationMode::BlockingMode & blockingMode,		// BlockingMode
		const SerialOperationMode::FluxMode & fluxMode, 			// FluxMode
		const QString & terminator = "", 							// Terminator
		const int nbOfArgs = 0, 									// The number of arguments to send
		const QString & argsSeparator = "", 						// separator
		const IOType & ioType = IOType::Undefined, 					// IOType
		const QString & family = "", 								// getFamily
		const QString & shortDescription = "",						// short getDescription
		const QString & description = "",							// description
		const QString & tooltip = ""								// tooltip
	);

	SerialCommand(
		const QString & command,
		const QString & name,
		const QRegularExpression & responseRegex,
		const SerialOperationMode::BlockingMode & blockingMode,
		const SerialOperationMode::FluxMode & fluxMode,
		const QString & terminator = "",
		const int nbOfArgs = 0,
		const QString & argsSeparator = "",
		const IOType & ioType = IOType::Undefined,
		const QString & family = "",
		const QString & shortDescription = "",
		const QString & description = "",
		const QString & tooltip = ""
	);

	SerialCommand(
		const QString & command,
		const QString & name,
		const QByteArrayList & expectedResponses,
		const SerialOperationMode::BlockingMode & blockingMode,
		const SerialOperationMode::FluxMode & fluxMode,
		const QString & terminator = "",
		const int nbOfArgs = 0,
		const QString & argsSeparator = "",
		const IOType & ioType = IOType::Undefined,
		const QString & family = "",
		const QString & shortDescription = "",
		const QString & description = "",
		const QString & tooltip = ""
	);

	SerialCommand(
		const QString & command,
		const QString & name,
		const int nbExpectedBytes,
		const SerialOperationMode::BlockingMode & blockingMode,
		const SerialOperationMode::FluxMode & fluxMode,
		const QString & terminator = "",
		const int nbOfArgs = 0,
		const QString & argsSeparator = "",
		const IOType & ioType = IOType::Undefined,
		const QString & family = "",
		const QString & shortDescription = "",
		const QString & description = "",
		const QString & tooltip = ""
	);

	~SerialCommand();

	inline bool operator==(SerialCommand const & command) const;
	inline bool operator!=(SerialCommand const & command) const;

	QString getCommand() const { return m_command; }
	QString getName() const { return m_name; }
	QRegularExpression getResponseRegex() const { return m_responseRegex; }
	QByteArrayList getExpectedResponses() const { return m_expectedResponses; }
	int getNbBytesExpected() const { return m_nbExpectedBytes; }
	SerialOperationMode getOperationMode() const { return m_operationMode; }
	QString getTerminator() const { return m_terminator; }
	int getNumberOfArgs() const { return m_numberOfArgs; }
	QString getArgsSeparator() const { return m_argsSeparator; }

	QString getFamily() const { return m_family; }
	QString getShortDesc() const { return m_shortDescription; }
	QString getDescription() const { return m_description; }
	IOType getIoType() const { return m_ioType; }
	QString getToolTip() const { return m_toolTip; }
	QList<const SerialCommand *> getPushModeStopCommands() const { return m_pushModeStopCommands; }
	QList<SerialCommandArg> getArgs() const { return m_args; }

	void addPushModeStopCommand(const SerialCommand * command);
	bool stopsPushMode(const SerialCommand & command) const;
	void setArgs(QList<SerialCommandArg> args) { m_args = args; }

	MatchType getMatchType() const { return m_matchType; }

	QByteArray getSerialData() const;

private:
	QByteArray m_command;
	QString m_name;
	QRegularExpression m_responseRegex;
	QByteArrayList m_expectedResponses;
	int m_nbExpectedBytes;
	SerialOperationMode m_operationMode;
	QString m_terminator;
	int m_numberOfArgs;
	QString m_argsSeparator;

	QString m_family;
	QString m_shortDescription;
	QString m_description;
	IOType m_ioType;
	QString m_toolTip;

	QList<const SerialCommand *> m_pushModeStopCommands;

	QList<SerialCommandArg> m_args;

	MatchType m_matchType;
};