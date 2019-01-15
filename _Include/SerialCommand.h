/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

/*!	\class SerialCommand
*
*	\brief Représente une commande série.
*
*	Fonctionne de concert avec la classe QSmartSerialPort.
*	Voir sa documentation pour des détails sur la gestion des commandes selon leur mode d'opération (m_OperationMode).
*
*	Construit la chaine de caractères à envoyer à l'aide de la méthode commandToSend().
*	Possède un constructeur pour une commande en QByteArray et un autre pour une commande en QString.
*	Normalement quand on envoie une commande, on s'attend à une réponse qui lui est propre.
*	Pour vérifier qu'elle y correspond, on utilise 2 façons dépendamment du constructeur utilisé.
*	Si la commande est en QByteArray, la réponse sera comparé à un QList<QByteArray>.
*	Si la commande est en QString, la réponse sera évaluée à l'aide d'un QRegularExpression.
*	La méthode getFirstMatch() permet de trouver la première correspondance dans un QByteArray (ou QString) passé en paramètre.
*
*	Protocole simplifié : on s'attend à ce que l'appareil avec lequel on communique renvoie un format de réponse précis.
*	Ce format est : "Commande:RéponseTerminator".
*	Pour utiliser ce protocole, on doit initialiser m_ResponseRegex avec un constructeur vide.
*	La méthode responseRegex() utilisera les variables m_Command et m_Terminator pour retourner le bon QRegularExpression
*
*/



#pragma once



#include "SerialCommandArg.h"
#include "SerialOperationMode.h"

#include <QString>
#include <QPair>
#include <QByteArray>
#include <QRegularExpression>
#include <QList>
#include <QVariant>

#include "ArgType.h"


class SerialCommand
{
public:
	enum class IOType { Undefined = 0, In = 1, Out = 2, InAndOut = 3 };

	SerialCommand() {}

	SerialCommand(
		QString command,  												// What is actually sent to the device
		QString name, 													// name
		QRegularExpression responseRegex,								// The response format we epxect
		QList<QByteArray> expectedResponses,							// The exact responses we can expect from the device
		int nbBytesExpected,											// The exact number of bytes we expect from the device response
		SerialOperationMode::BlockingMode blockingMode, 				// BlockingMode
		SerialOperationMode::FluxMode fluxMode, 						// FluxMode
		QString terminator = "", 										// Terminator
		int nbOfArgs = 0, 												// The number of arguments to send
		QString argsSeparator = "", 									// separator
		IOType ioType = IOType::Undefined, 								// IOType
		QString family = "", 											// family
		QString shortDescription = "",									// short desc
		QString description = "",										// description
		QString tooltip = ""											// tooltip
	);

	SerialCommand(
		QString command,
		QString name,
		QRegularExpression responseRegex,
		SerialOperationMode::BlockingMode blockingMode,
		SerialOperationMode::FluxMode fluxMode,
		QString terminator = "",
		int nbOfArgs = 0,
		QString argsSeparator = "",
		IOType ioType = IOType::Undefined,
		QString family = "",
		QString shortDescription = "",
		QString description = "",
		QString tooltip = ""
	);

	SerialCommand(
		QString command,
		QString name,
		QList<QByteArray> expectedResponses,
		SerialOperationMode::BlockingMode blockingMode,
		SerialOperationMode::FluxMode fluxMode,
		QString terminator = "",
		int nbOfArgs = 0,
		QString argsSeparator = "",
		IOType ioType = IOType::Undefined,
		QString family = "",
		QString shortDescription = "",
		QString description = "",
		QString tooltip = ""
	);

	SerialCommand(
		QString command,
		QString name,
		int nbBytesExpected,
		SerialOperationMode::BlockingMode blockingMode,
		SerialOperationMode::FluxMode fluxMode,
		QString terminator = "",
		int nbOfArgs = 0,
		QString argsSeparator = "",
		IOType ioType = IOType::Undefined,
		QString family = "",
		QString shortDescription = "",
		QString description = "",
		QString tooltip = ""
	);

	~SerialCommand();

	inline bool operator==(SerialCommand const & command) const;
	inline bool operator!=(SerialCommand const & command) const;

	QString command() const { return m_Command; }
	int numberOfArgs() const { return m_NumberOfArgs; };
	QRegularExpression responseRegex() const { return m_ResponseRegex; }

	QString family() const { return m_Family; }
	IOType ioType() const { return m_IOType; }
	QString name() const { return m_Name; }
	QString terminator() const { return m_Terminator; }
	QString shortDesc() const { return m_ShortDescription; }
	QString desc() const { return m_Description; }
	QString toolTip() const { return m_ToolTip; }
	SerialOperationMode operationMode() const { return m_OperationMode; }
	QList<const SerialCommand *> pushModeStopCommands() const { return m_PushModeStopCommands; }
	QList<QByteArray> expectedResponses() const { return m_ExpectedResponses; }
	int nbBytesExpected() const { return m_NbExpectedBytes; }
	QList<SerialCommandArg> args() const { return m_Args; }

	QByteArray commandToSend() const;
	void addPushModeStopCommand(const SerialCommand * command);
	bool stopsPushMode(const SerialCommand & command) const;

	void setArguments(QList<SerialCommandArg> args) { m_Args = args; }


private:
	QByteArray m_Command;
	int m_NumberOfArgs;
	QRegularExpression m_ResponseRegex;
	QString m_ArgsSeparator;
	QString m_Terminator;

	QString m_Family;
	IOType m_IOType;
	QString m_Name;
	QString m_ShortDescription;
	QString m_Description;
	QString m_ToolTip;
	SerialOperationMode m_OperationMode;
	QList<QByteArray> m_ExpectedResponses;
	int m_NbExpectedBytes;

	QList<const SerialCommand *> m_PushModeStopCommands;

	QList<SerialCommandArg> m_Args;
};
