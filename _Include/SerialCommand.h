/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

/*!	\class QSerialCommand
*
*	\brief Représente une commande série.
*
*	Fonctionne de concert avec la classe QCommandSerialPort.
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



#ifndef QSERIALCOMMAND_H
#define QSERIALCOMMAND_H



#include <QString>
#include <QByteArray>
#include <QRegularExpression>
#include <QList>
#include <QVariant>


/*! \class SerialOperationMode
*
*	\brief Conteneur pour les modes d'opération d'une commande
*
*/

class SerialOperationMode
{
public:
	enum class BlockingMode
	{
		// Wait for the response before sending any other command.
		Blocking = 0,

		// Not expecting any response.
		NonBlockingNoResponse = 1,

		// Expecting as many responses as the number of commands sent.
		NonBlockingXCommandsXResponses = 2,

		// Will not send more of the same command before receiving the response (prevents spamming).
		NonBlockingWaitResponse = 3
	};

	enum class FluxMode { Pull = 0, Push = 1 };

	SerialOperationMode(BlockingMode blockingMode, FluxMode fluxMode);
	SerialOperationMode();
	~SerialOperationMode();

	FluxMode fluxMode() { return mFluxMode; }
	BlockingMode blockingMode() { return mBlockingMode; }


private:
	BlockingMode mBlockingMode;
	FluxMode mFluxMode;
};


class SerialCommand
{
public:
	enum class IOType { Undefined = 0, In = 1, Out = 2, Io = 3 };

	SerialCommand() {}
	SerialCommand(
		QString command,  												// cmd
		QString name, 													// name
		IOType ioType, 													// IOType
		int nbOfArgs, 													// # args
		bool argsAreRaw,
		SerialOperationMode::BlockingMode blockingMode, 				// BlockingMode
		SerialOperationMode::FluxMode fluxMode, 						// FluxMode	
		QString terminator, 											// Terminator
		QString separator, 												// separator
		QString family = "", 											// family
		QString shortDesc = "",											// short desc
		QRegularExpression responseRegex = QRegularExpression(),		// response
		QString desc = "",												// description
		QString tooltip = "");											// tooltip

	SerialCommand(
		QByteArray command,
		QString name,
		IOType ioType,
		int nbOfArgs,
		bool argsAreRaw,
		SerialOperationMode::BlockingMode blockingMode,
		SerialOperationMode::FluxMode fluxMode,
		QString terminator,
		QString separator,
		QString family = "",
		QString shortDesc = "",
		QList<QByteArray> expectedResponses = QList<QByteArray>(),
		QString desc = "",
		QString tooltip = "");

	SerialCommand(
		QByteArray command,
		QString name,
		IOType ioType,
		int nbOfArgs,
		bool argsAreRaw,
		SerialOperationMode::BlockingMode blockingMode,
		SerialOperationMode::FluxMode fluxMode,
		QString terminator,
		QString separator,
		QString family = "",
		QString shortDesc = "",
		int nbBytesExpected = 0,
		QString desc = "",
		QString tooltip = "");

	~SerialCommand();

	inline bool operator==(SerialCommand const & command) const {
		return m_Name == command.m_Name && m_Args == command.m_Args;
	}
	inline bool operator!=(SerialCommand const & command) const {
		return m_Name != command.m_Name && m_Args != command.m_Args;
	}

	QString command() const { return m_Command; }
	int numberOfArgs() const { return m_NumberOfArgs; };
	QRegularExpression responseRegex() const;

	QString family() const { return m_Family; }
	IOType ioType() const { return m_IOType; }
	QString name() const { return m_Name; }
	QString terminator() const { return m_Terminator; }
	QString shortDesc() const { return m_ShortDesc; }
	QString desc() const { return m_Desc; }
	QString toolTip() const { return m_ToolTip; }
	SerialOperationMode operationMode() const { return m_OperationMode; }
	QList<SerialCommand const *> pushModeStopCommands() const { return m_PushModeStopCommands; }
	QList <QByteArray> expectedResponses() const { return m_ExpectedResponses; }
	int nbBytesExpected() const { return m_NbBytesExpected; }
	QList<QVariant> args() const { return m_Args; }

	QByteArray commandToSend() const;
	void addPushModeStopCommand(SerialCommand const * command);
	bool stopsPushMode(SerialCommand const &command) const;

	QByteArray getFirstMatch(QByteArray const &buffer);

	void setArguments(QList<QVariant> args) { m_Args = args; }


private:
	bool m_IsString;
	QByteArray m_Command;
	int m_NumberOfArgs;
	bool m_ArgsAreRaw;
	QRegularExpression m_ResponseRegex;
	QString m_Separator;
	QString m_Terminator;

	QString m_Family;
	IOType m_IOType;
	QString m_Name;
	QString m_ShortDesc;
	QString m_Desc;
	QString m_ToolTip;
	SerialOperationMode m_OperationMode;
	QList <QByteArray> m_ExpectedResponses;
	int m_NbBytesExpected;

	QList<SerialCommand const *> m_PushModeStopCommands;

	QList<QVariant> m_Args;

};

#endif // QSERIALCOMMAND_H
