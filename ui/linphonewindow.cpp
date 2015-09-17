#include <QDebug>
#include <QMessageBox>
#include <QScrollBar>
#include <QtQuick>

#include "linphonewindow.h"
#include "ui_linphonewindow.h"

#include "qlinphonecore.h"
#include "accountpreferences.h"

LinphoneWindow::LinphoneWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::LinphoneWindow),
	core(new QLinphoneCore(this))
{
	qmlRegisterType<QLChatRoom,1>("QLChatRoom",1,0,"ChatRoom");
	ui->setupUi(this);
	setupProxyList();
	loadChatRooms();
	connect(core, &QLinphoneCore::registrationStateChanged, this, &LinphoneWindow::registrationStateChanged);
	connect(core, &QLinphoneCore::messageReceived, this, &LinphoneWindow::messageReceived);
}

LinphoneWindow::~LinphoneWindow()
{
	delete ui;
}

void LinphoneWindow::loadChatRooms() {
	auto chatrooms = core->chatRooms();
	ui->itemchatroomlist->clear();
	int row = 0;

	foreach (QLChatRoom* chatroom, chatrooms) {
		const LinphoneAddress *addr = linphone_chat_room_get_peer_address(chatroom->getRoom());
		auto username = linphone_address_get_username(addr);
		// TODO: use model-based version
		int unread = linphone_chat_room_get_unread_messages_count(chatroom->getRoom());
        QString itemText = username;
        if( unread != 0 ){
            itemText += QString(" (%1)").arg(unread);
        }
        ui->itemchatroomlist->addItem(itemText);
		row++;
	}
}

void LinphoneWindow::setupProxyList() {
	auto proxies = core->accounts();
	ui->accountCombo->clear();
	if( proxies.size() > 0){
		QPixmap pix = QPixmap(22,22);
		pix.fill(QColor("grey"));
		QIcon icon(pix);
		for( auto proxy : proxies ){
			ui->accountCombo->addItem(icon, linphone_proxy_config_get_identity(proxy));
		}
	} else {
		ui->accountCombo->setDisabled(true);
	}
}

void LinphoneWindow::displayProxyPreferences(LinphoneProxyConfig* proxy) {
	AccountPreferences* prefs = new AccountPreferences(core, proxy, this);
	prefs->setModal(true);
	prefs->show();
	connect(prefs, &AccountPreferences::destroyed, this, &LinphoneWindow::prefsAccepted);
}

void LinphoneWindow::prefsAccepted(QObject*) {
	setupProxyList();
}

QString LinphoneWindow::getProxyColorForState(LinphoneRegistrationState state)
{
	QString color = "red";
	switch (state) {
	case LinphoneRegistrationOk:
		color = ("green");
		break;
	case LinphoneRegistrationProgress:
		color = ("yellow");
		break;
	default:
		break;
	}

	return color;
}

void LinphoneWindow::setAccountIconColor(int proxy_index, const QString &color)
{
	QPixmap pix = QPixmap(22,22);
	pix.fill(QColor(color));
	QIcon icon(pix);
	ui->accountCombo->setItemIcon(proxy_index, icon);
}

void LinphoneWindow::registrationStateChanged(QLProxy cfg, LinphoneRegistrationState state)
{
	auto accounts = core->accounts();
	QString color = getProxyColorForState(state);

	for( int i = 0; i<accounts.size(); i++){

		if( accounts.at(i) == cfg.proxy)
		{
			setAccountIconColor(i, color);
			break;
		}
	}
}

void LinphoneWindow::messageReceived(QLChatRoom room, QLMessage message) {
	int idx = core->chatRooms().indexOf(&room);
	if( ui->itemchatroomlist->currentIndex().row() == idx ){
		linphone_chat_room_mark_as_read(room.getRoom());
	}
    loadChatRooms();
}

void LinphoneWindow::accountOptions_Action_Triggered(QAction* action ){
	qDebug() << "Action:" << action->text();
	if( action->text() == "New Account"){
		displayProxyPreferences(NULL);
	} else if( action->text() == "Remove" ) {

		auto reply = QMessageBox::question(this,
					   "Remove proxy",
					   "Do you really want to remove the proxy for " + ui->accountCombo->currentText(),
					   QMessageBox::Yes|QMessageBox::No);

		if( reply == QMessageBox::Yes) {
			core->removeProxy(getCurrentSelectedProxy());
			setupProxyList();
		}

	} else if( action->text() == "Edit" ){
		displayProxyPreferences(getCurrentSelectedProxy() );
	}
}

LinphoneProxyConfig *LinphoneWindow::getCurrentSelectedProxy() {
	auto proxies = core->accounts();
	if( proxies.size() )
		return proxies.at(ui->accountCombo->currentIndex());
	else
		return NULL;
}

void LinphoneWindow::on_addConversationBtn_clicked()
{
	qDebug() << "Should add conversation with " << ui->searchBar->text();
	on_searchBar_returnPressed();
}

void LinphoneWindow::on_accountOptions_clicked()
{
	QMenu *menu = new QMenu(this);
	QAction *removeAction = menu->addAction("Remove");
	QAction *editAction = menu->addAction("Edit");
	menu->addAction("New Account");

	if( ui->accountCombo->count() == 0){
		removeAction->setEnabled(false);
		editAction->setEnabled(false);
	}
	connect(menu, &QMenu::triggered, this, &LinphoneWindow::accountOptions_Action_Triggered);

	menu->popup(QCursor::pos());
}

bool LinphoneWindow::validateAddress(QLineEdit *field){
	if(field->text() == "") {
		field->setStyleSheet("color: black");
		return true;
	}

	QByteArray arr = field->text().toLatin1();
	LinphoneAddress *addr = linphone_core_interpret_url(core->core(),arr.constData());
	if( addr != NULL) {
		field->setStyleSheet("color: green");
		linphone_address_destroy(addr);
		return true;
	} else {
		field->setStyleSheet("color: red");
		return false;
	}
}

void LinphoneWindow::on_searchBar_textChanged(const QString &arg1)
{
	bool ok = validateAddress( ui->searchBar );
	ui->addConversationBtn->setEnabled(ok);
}

void LinphoneWindow::on_searchBar_returnPressed()
{
	if (validateAddress(ui->searchBar)){
		qDebug() << "Starting conversation with" << ui->searchBar->text();
		auto chatroom = core->addChatRoom(ui->searchBar->text());

		auto peeraddr = linphone_chat_room_get_peer_address(chatroom->getRoom());
		char* peerstring = linphone_address_as_string(peeraddr);
		qDebug() << "Chatroom for" << peerstring;
		ms_free(peerstring);
		ui->searchBar->clear();
		loadChatRooms();
	}
}

void LinphoneWindow::on_accountCombo_currentIndexChanged(int index)
{
	linphone_core_set_default_proxy_index(core->core(), index);
	qDebug() << "Default proxy index set to" << index;
}

void LinphoneWindow::on_itemchatroomlist_currentRowChanged(int currentRow)
{
    if( currentRow == -1 ) return;
    auto chatRooms = core->chatRooms();
	QLChatRoom* model = chatRooms.at(currentRow);
	LinphoneChatRoom* room = model->getRoom();
	qDebug() << "Set chat list to follow chatroom" << room << "with" << model->rowCount() << "messages";
	connect(core, &QLinphoneCore::messageReceived, model, &QLChatRoom::onMessageReceived);
	ui->quickChatList->rootContext()->setContextProperty("myModel", model);

    linphone_chat_room_mark_as_read(room);
}

void LinphoneWindow::on_sendMessage_clicked()
{
    if(ui->messageBox->text().isEmpty())
        return;
	auto chatrooms = core->chatRooms();
	int row = ui->itemchatroomlist->currentIndex().row();
	QLChatRoom* selected = chatrooms.at(row);
	selected->sendMessage(ui->messageBox->text());
    ui->messageBox->clear();
}

void LinphoneWindow::on_messageBox_textChanged(const QString &arg1)
{
	bool text_not_empty   = ! ui->messageBox->text().isEmpty();
	bool chatroomSelected = ui->itemchatroomlist->currentIndex().row() != -1;

	ui->sendMessage->setEnabled(text_not_empty && chatroomSelected);
}
