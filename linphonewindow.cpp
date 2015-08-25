#include <QDebug>

#include "linphonewindow.h"
#include "ui_linphonewindow.h"

#include "qlinphonecore.h"

LinphoneWindow::LinphoneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LinphoneWindow),
    core(new QLinphoneCore(this))
{
    ui->setupUi(this);
    auto proxies = core->accounts();
    if( proxies.size() > 0){
		for( auto proxy : proxies ){
			//ui->accountCombo->addItem(linphone_proxy_config_get_identity(proxy), QVariant());
		}
    } else {
		ui->accountCombo->setDisabled(true);
    }
}

LinphoneWindow::~LinphoneWindow()
{
    delete ui;

}

void LinphoneWindow::on_addConversationBtn_clicked()
{
    qDebug() << "Should add conversation with " << ui->searchBar->text();
}
