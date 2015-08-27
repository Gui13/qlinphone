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
	auto proxies = core->accounts();
	if( proxies.size() > 0){
		for( auto proxy : proxies ){
			// TODO: change the variant to hold a reference to the Proxy
			ui->accountCombo->addItem(linphone_proxy_config_get_identity(proxy), QVariant());
		}
	} else {
		ui->accountCombo->setDisabled(true);
	}
}

LinphoneWindow::~LinphoneWindow()
{
	delete ui;

}

void LinphoneWindow::accountOptions_Action_Triggered(QAction* action ){
	qDebug() << "Action:" << action->text();
	if( action->text() == "New Account"){
		// TODO: display UI to add an account
		AccountPreferences* prefs = new AccountPreferences(this);
		prefs->setModal(true);
		prefs->show();
	} else if( action->text() == "Remove" ) {
		// TODO: get current proxy and remove it
	} else if( action->text() == "Edit" ){
		// TODO: display UI to edit the account
	}
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
