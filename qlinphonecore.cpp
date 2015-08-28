#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include "qlinphonecore.h"
#include "linphone/linphonecore.h"


static void qlinphone_global_state_changed(LinphoneCore*, LinphoneGlobalState, const char *msg){
    qDebug() << "Global state changed:" << msg;
}

static void qlinphone_message_received(LinphoneCore *lc, LinphoneChatRoom *room, LinphoneChatMessage *message){
	QLinphoneCore* c = (QLinphoneCore*) linphone_core_get_user_data(lc);
	c->onMessageReceived(room, message);
}


QLinphoneCore::QLinphoneCore(QObject *parent) : QObject(parent)
{
    QDir confDir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    confDir.mkdir("Linphone");

    QString config_file = confDir.absolutePath() + "/Linphone/.linphonerc";
	qDebug() << "Config file:" << config_file;

    static LinphoneCoreVTable vtable = {0};

    vtable.global_state_changed = qlinphone_global_state_changed;
	vtable.message_received = qlinphone_message_received;

	lc = linphone_core_new(&vtable, config_file.toStdString().c_str() , NULL, this);
}

QLinphoneCore::~QLinphoneCore()
{
	if( lc ){
		linphone_core_destroy(lc);
		lc = NULL;
    }
}

/* Public API */

QList<LinphoneProxyConfig *> QLinphoneCore::accounts() const
{
    QList<LinphoneProxyConfig*> list;
	const MSList* proxies = linphone_core_get_proxy_config_list(lc);
    const MSList* proxy = proxies;
    while( proxy ){
        list.append((LinphoneProxyConfig*)proxy->data);
        proxy = proxy->next;
    }
	return list;
}

QList<QLChatRoom> QLinphoneCore::chatRooms() const
{
	MSList* rooms = linphone_core_get_chat_rooms(lc);
	QList<QLChatRoom> l;
	MSList* iter = rooms;
	while(iter){
		l.append(QLChatRoom((LinphoneChatRoom*)iter->data));
		iter=iter->next;
	}
	ms_list_free(rooms);
	return l;
}

LinphoneProxyConfig *QLinphoneCore::createNewProxy() const
{
	return linphone_core_create_proxy_config(lc);
}

void QLinphoneCore::addProxy( LinphoneProxyConfig *cfg){
	linphone_core_add_proxy_config(lc, cfg);
}

void QLinphoneCore::onMessageReceived(LinphoneChatRoom *room, LinphoneChatMessage *msg)
{
	emit messageReceived(QLChatRoom(room), QLMessage(msg));
}

