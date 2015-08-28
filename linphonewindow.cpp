#include <QDebug>

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
}

LinphoneWindow::~LinphoneWindow()
{
	delete ui;

}

void LinphoneWindow::setupProxyList() {
	auto proxies = core->accounts();
	if( proxies.size() > 0){
		for( auto proxy : proxies ){
			// TODO: change the variant to hold a reference to the Proxy?
			ui->accountCombo->addItem(linphone_proxy_config_get_identity(proxy), QVariant());
		}
	} else {
		ui->accountCombo->setDisabled(true);
	}
}

void LinphoneWindow::displayProxyPreferences(LinphoneProxyConfig* proxy) {
	AccountPreferences* prefs = new AccountPreferences(core, proxy, this);
	prefs->setModal(true);
	connect(prefs, &AccountPreferences::finished, this, &LinphoneWindow::setupProxyList);
	prefs->show();
}

void LinphoneWindow::prefsFinished(int result) {
	if(result == QDialog::Accepted) {
		setupProxyList();
	}
}

void LinphoneWindow::accountOptions_Action_Triggered(QAction* action ){
	qDebug() << "Action:" << action->text();
	if( action->text() == "New Account"){
		// TODO: display UI to add an account
		displayProxyPreferences(NULL);
	} else if( action->text() == "Remove" ) {
		// TODO: get current proxy and remove it
	} else if( action->text() == "Edit" ){
		// TODO: display UI to edit the account
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
