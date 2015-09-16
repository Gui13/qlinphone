#ifndef QLINPHONECORE_H
#define QLINPHONECORE_H


#include <QObject>
#include "qlchatroom.h"
#include "qlmessage.h"
#include "qlproxy.h"
#include "linphone/linphonecore.h"

static void qlinphone_global_state_changed(LinphoneCore*, LinphoneGlobalState, const char *msg);
static void qlinphone_message_received(LinphoneCore *lc, LinphoneChatRoom *room, LinphoneChatMessage *message);
static void qlinphone_auth_info_requested(LinphoneCore *lc, const char *realm, const char *username, const char *domain);
static void qlinphone_registration_state_changed(LinphoneCore *lc, LinphoneProxyConfig *cfg, LinphoneRegistrationState cstate, const char *message);

class QLinphoneCore : public QObject
{
    Q_OBJECT
public:
    explicit QLinphoneCore(QObject *parent = 0);
    ~QLinphoneCore();

	LinphoneCore* core() const { return lc; }

	const QList<QLChatRoom *> &chatRooms() const { return rooms; }
	QLChatRoom *addChatRoom(const QString &peer);
	void eraseChatRoom(QLChatRoom *room);

	const QList<LinphoneProxyConfig *> &accounts() const { return proxies; }
	LinphoneProxyConfig *createNewProxy() const;
	void addProxy(LinphoneProxyConfig *cfg);
	void removeProxy(LinphoneProxyConfig *cfg);
signals:
	void messageReceived(QLChatRoom room, QLMessage msg);
	void registrationStateChanged(QLProxy cfg, LinphoneRegistrationState state);

public slots:

private slots:
	void iterate();

private:
	LinphoneCore* lc;
	QList<LinphoneProxyConfig*> proxies;
	QList<QLChatRoom*> rooms;

	void onMessageReceived(LinphoneChatRoom* room, LinphoneChatMessage* msg);
	void onRegistrationStateChanged(LinphoneProxyConfig *cfg, LinphoneRegistrationState state);


// friendly statics:
	friend void qlinphone_global_state_changed(LinphoneCore*, LinphoneGlobalState, const char *msg);
	friend void qlinphone_message_received(LinphoneCore *lc, LinphoneChatRoom *room, LinphoneChatMessage *message);
	friend void qlinphone_registration_state_changed(LinphoneCore *lc, LinphoneProxyConfig *cfg, LinphoneRegistrationState cstate, const char *message);

};

#endif // QLINPHONECORE_H
