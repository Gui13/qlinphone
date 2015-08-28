#include <QDebug>
#include <QMessageBox>

#include "linphonewindow.h"
#include "ui_linphonewindow.h"

#include "qlinphonecore.h"
#include "accountpreferences.h"

LinphoneWindow::LinphoneWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::LinphoneWindow),
	core(new QLinphoneCore(this))
{
	ui->setupUi(this);
	setupProxyList();
	connect(core, &QLinphoneCore::registrationStateChanged, this, &LinphoneWindow::registrationStateChanged);
}

LinphoneWindow::~LinphoneWindow()
{
	delete ui;
}

void LinphoneWindow::setupProxyList() {
	auto proxies = core->accounts();
	ui->accountCombo->clear();
	if( proxies.size() > 0){
		for( auto proxy : proxies ){
			ui->accountCombo->addItem(linphone_proxy_config_get_identity(proxy));
		}
	} else {
		ui->accountCombo->setDisabled(true);
	}
}

void LinphoneWindow::displayProxyPreferences(LinphoneProxyConfig* proxy) {
	AccountPreferences* prefs = new AccountPreferences(core, proxy, this);
	prefs->setModal(true);
	connect(prefs, &AccountPreferences::finished, this, &LinphoneWindow::prefsFinished);
	prefs->show();
}

void LinphoneWindow::prefsFinished(int result) {
	if(result == QDialog::Accepted) {
		setupProxyList();
	}
}

void LinphoneWindow::updateRegstate(LinphoneRegistrationState state ){
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
	// TODO: paint with correct color
	ui->accountStatus->setStyleSheet("background-color:"+color);
}

void LinphoneWindow::registrationStateChanged(QLProxy cfg, LinphoneRegistrationState state)
{
	auto accounts = core->accounts();
	int currentIndex = ui->accountCombo->currentIndex();
	for( int i = 0; i<accounts.size(); i++){
		if( accounts.at(i) == cfg.proxy && i == currentIndex ) {
			// regstate changed for the current account
			updateRegstate(state);
		}
	}
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
			linphone_core_remove_proxy_config(core->core(), getCurrentSelectedProxy());
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
