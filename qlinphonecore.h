#ifndef QLINPHONECORE_H
#define QLINPHONECORE_H


#include <QObject>
#include "qlchatroom.h"
#include "qlmessage.h"
#include "linphone/linphonecore.h"

static void qlinphone_global_state_changed(LinphoneCore*, LinphoneGlobalState, const char *msg);
static void qlinphone_message_received(LinphoneCore *lc, LinphoneChatRoom *room, LinphoneChatMessage *message);

class QLinphoneCore : public QObject
{
    Q_OBJECT
public:
    explicit QLinphoneCore(QObject *parent = 0);
    ~QLinphoneCore();

	LinphoneCore* core() const { return lc; }

    QList<LinphoneProxyConfig *> accounts() const;
	QList<QLChatRoom> chatRooms() const;
	LinphoneProxyConfig *createNewProxy() const;

	void addProxy(LinphoneProxyConfig *cfg);
signals:
	void chatRoomsUpdated(QList<QLChatRoom> rooms);
	void messageReceived(QLChatRoom room, QLMessage msg);

public slots:

private:
	LinphoneCore* lc;

	void onMessageReceived(LinphoneChatRoom* room, LinphoneChatMessage* msg);


// friendly statics:
	friend void qlinphone_global_state_changed(LinphoneCore*, LinphoneGlobalState, const char *msg);
	friend void qlinphone_message_received(LinphoneCore *lc, LinphoneChatRoom *room, LinphoneChatMessage *message);

};

#endif // QLINPHONECORE_H
