#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QInputDialog>
#include <QTimer>
#include "qlinphonecore.h"
#include "linphone/linphonecore.h"


static void qlinphone_global_state_changed(LinphoneCore*, LinphoneGlobalState, const char *msg){
    qDebug() << "Global state changed:" << msg;
}

static void qlinphone_message_received(LinphoneCore *lc, LinphoneChatRoom *room, LinphoneChatMessage *message){
	QLinphoneCore* c = (QLinphoneCore*) linphone_core_get_user_data(lc);
	c->onMessageReceived(room, message);
}

static void qlinphone_auth_info_requested(LinphoneCore *lc, const char *realm, const char *username, const char *domain){
	QString message = "Please enter password for user " + QString(username) + "@" + QString(domain);
	bool ok;
	QLinphoneCore* c = (QLinphoneCore*) linphone_core_get_user_data(lc);
	QString password = QInputDialog::getText(NULL, "Authentication required", message, QLineEdit::Password, "", &ok);
	if( ok && !password.isEmpty() ){
		auto cstringArray = password.toUtf8();
		LinphoneAuthInfo* info = linphone_auth_info_new(username, NULL, cstringArray.data(), NULL, realm, domain);
		linphone_core_add_auth_info(lc, info);
	}
}

static void qlinphone_registration_state_changed(LinphoneCore *lc, LinphoneProxyConfig *cfg, LinphoneRegistrationState cstate, const char *message) {
	qDebug() << "Registration state changed:" << message;
	QLinphoneCore* c = (QLinphoneCore*) linphone_core_get_user_data(lc);
	c->onRegistrationStateChanged(cfg, cstate);
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
	vtable.auth_info_requested = qlinphone_auth_info_requested;
	vtable.registration_state_changed = qlinphone_registration_state_changed;

	lc = linphone_core_new(&vtable, config_file.toStdString().c_str() , NULL, this);

	// iterate
	QTimer *timer = new QTimer();
	connect(timer, &QTimer::timeout, this, &QLinphoneCore::iterate);
	timer->start(20);
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
	const MSList* rooms = linphone_core_get_chat_rooms(lc);
	QList<QLChatRoom> l;
	const MSList* iter = rooms;
	while(iter){
		l.append(QLChatRoom((LinphoneChatRoom*)iter->data));
		iter=iter->next;
	}
	return l;
}

LinphoneProxyConfig *QLinphoneCore::createNewProxy() const
{
	return linphone_core_create_proxy_config(lc);
}

void QLinphoneCore::addProxy( LinphoneProxyConfig *cfg){
	linphone_core_add_proxy_config(lc, cfg);
}

void QLinphoneCore::iterate()
{
	linphone_core_iterate(lc);
}

void QLinphoneCore::onMessageReceived(LinphoneChatRoom *room, LinphoneChatMessage *msg)
{
	emit messageReceived(QLChatRoom(room), QLMessage(msg));
}

void QLinphoneCore::onRegistrationStateChanged(LinphoneProxyConfig *cfg, LinphoneRegistrationState state) {
	emit registrationStateChanged(QLProxy(cfg),state);
}
