/*!	\class QSerialCommand
*
*	\brief Repr�sente une commande s�rie.
*
*	Fonctionne de concert avec la classe QCommandSerialPort.
*	Voir sa documentation pour des d�tails sur la gestion des commandes selon leur mode d'op�ration (mOperationMode).
*
*	Construit la chaine de caract�res � envoyer � l'aide de la m�thode commandToSend().
*	Poss�de un constructeur pour une commande en QByteArray et un autre pour une commande en QString.
*	Normalement quand on envoie une commande, on s'attend � une r�ponse qui lui est propre.
*	Pour v�rifier qu'elle y correspond, on utilise 2 fa�ons d�pendamment du constructeur utilis�.
*	Si la commande est en QByteArray, la r�ponse sera compar� � un QList<QByteArray>.
*	Si la commande est en QString, la r�ponse sera �valu�e � l'aide d'un QRegularExpression.
*	La m�thode getFirstMatch() permet de trouver la premi�re correspondance dans un QByteArray (ou QString) pass� en param�tre.
*
*	Protocole simplifi� : on s'attend � ce que l'appareil avec lequel on communique renvoie un format de r�ponse pr�cis.
*	Ce format est : "Commande:R�ponseTerminator".
*	Pour utiliser ce protocole, on doit initialiser mReturnExp avec un constructeur vide.
*	La m�thode returnExp() utilisera les variables mCommand et mTerminator pour retourner le bon QRegularExpression
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
