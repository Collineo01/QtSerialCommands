/*!	\class QSerialCommand
*
*	\brief Représente une commande série.
*
*	Fonctionne de concert avec la classe QCommandSerialPort.
*	Voir sa documentation pour des détails sur la gestion des commandes selon leur mode d'opération (mOperationMode).
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
*	Pour utiliser ce protocole, on doit initialiser mReturnExp avec un constructeur vide.
*	La méthode returnExp() utilisera les variables mCommand et mTerminator pour retourner le bon QRegularExpression
*
*/



#ifndef QSERIALCOMMAND_H
#define QSERIALCOMMAND_H

#include "serialcommandslib_global.h"

#include <QString>
#include <QByteArray>
#include <QRegularExpression>
#include <QList>
#include <QVariant>
#include "SerialOperationMode.h"


class SerialCommand
{
public:
	enum class IOType { Undefined = 0, In = 1, Out = 2, Io = 3 };

	SerialCommand() {}
	SerialCommand(
		QString command,  												// cmd
		QString name, 													// name
		IOType ioType, 													// IOType
		int nParam, 													// # params
		bool isRawParam,
		SerialOperationMode::BlockingMode blockingMode, 				// BlockingMode
		SerialOperationMode::FluxMode fluxMode, 						// FluxMode	
		QString terminator, 											// Terminator
		QString separator, 												// separator
		QString family = "", 											// family
		QString shortDesc = "",											// short desc
		QRegularExpression returnExp = QRegularExpression(),			// response
		QString desc = "",												// description
		QString tooltip = "");											// tooltip

	SerialCommand(
		QByteArray command,
		QString name,
		IOType ioType,
		int nParam,
		bool isRawParam,
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
		int nParam,
		bool isRawParam,
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
		return mName == command.mName;
	}

	QString command() const { return mCommand; }
	int nParam() const { return mNParam; };
	QRegularExpression returnExp() const;

	QString family() const { return mFamily; }
	IOType ioType() const { return mIOType; }
	QString name() const { return mName; }
	QString terminator() const { return mTerminator; }
	QString shortDesc() const { return mShortDesc; }
	QString desc() const { return mDesc; }
	QString toolTip() const { return mToolTip; }
	SerialOperationMode operationMode() const { return mOperationMode; }
	QList<SerialCommand const *> pushModeStopCommands() const { return mPushModeStopCommands; }
	QList <QByteArray> expectedResponses() const { return mExpectedResponses; }
	int nbBytesExpected() const { return mNbBytesExpected; }

	QByteArray commandToSend(const QList<QVariant> & params) const;
	void addPushModeStopCommand(SerialCommand const * command);
	bool stopsPushMode(SerialCommand const &command) const;

	QByteArray getFirstMatch(QByteArray const &buffer);


private:
	bool mIsString;
	QByteArray mCommand;
	int mNParam;
	bool mIsRawParam;
	QRegularExpression mReturnExp;
	QString mSeparator;
	QString mTerminator;

	QString mFamily;
	IOType mIOType;
	QString mName;
	QString mShortDesc;
	QString mDesc;
	QString mToolTip;
	SerialOperationMode mOperationMode;
	QList <QByteArray> mExpectedResponses;
	int mNbBytesExpected;

	QList<SerialCommand const *> mPushModeStopCommands;

};

#endif // QSERIALCOMMAND_H
