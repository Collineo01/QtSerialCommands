#pragma once

/*!	\class SerialCommand
*
*	\brief Représente une commande série.
*
*	Fonctionne de concert avec la classe QMatchSerialPort.
*	Voir sa documentation pour des détails sur la gestion des commandes selon leur mode d'opération (m_operationMode).
*
*	Construit la chaine de caractères à envoyer à l'aide de la méthode commandToSend().
*	Possède un constructeur pour une commande en QByteArray et un autre pour une commande en QString.
*	Normalement quand on envoie une commande, on s'attend à une réponse qui lui est propre.
*	Pour vérifier qu'elle y correspond, on utilise 2 façons dépendamment du constructeur utilisé.
*	Si la commande est en QByteArray, la réponse sera comparé à un QList<QByteArray>.
*	Si la commande est en QString, la réponse sera évaluée à l'aide d'un QRegularExpression.
*	La méthode getFirstCommandMatch() permet de trouver la première correspondance dans un QByteArray (ou QString) passé en paramètre.
*
*	Protocole simplifié : on s'attend à ce que l'appareil avec lequel on communique renvoie un format de réponse précis.
*	Ce format est : "Commande:RéponseTerminator".
*	Pour utiliser ce protocole, on doit initialiser m_responseRegex avec un constructeur vide.
*	La méthode getResponseRegex() utilisera les variables m_command et m_terminator pour retourner le bon QRegularExpression
*
*/


#include "qtserialcommands_global.h"

#include "SerialCommandArg.h"
#include "SerialOperationMode.h"
#include "IOType.h"

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
		const QList<QByteArray> & expectedResponses,				// The exact responses we can expect from the device
		const int & nbBytesExpected,								// The exact number of bytes we expect from the device response
		const SerialOperationMode::BlockingMode & blockingMode,		// BlockingMode
		const SerialOperationMode::FluxMode & fluxMode, 			// FluxMode
		const QString & terminator = "", 							// Terminator
		const int & nbOfArgs = 0, 									// The number of arguments to send
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
		const int & nbOfArgs = 0,
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
		const int & nbOfArgs = 0,
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
		const int & nbExpectedBytes,
		const SerialOperationMode::BlockingMode & blockingMode,
		const SerialOperationMode::FluxMode & fluxMode,
		const QString & terminator = "",
		const int & nbOfArgs = 0,
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
	QList<QByteArray> getExpectedResponses() const { return m_expectedResponses; }
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

	QByteArray commandToSend() const;

private:
	QByteArray m_command;
	QString m_name;
	QRegularExpression m_responseRegex;
	QList<QByteArray> m_expectedResponses;
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
};