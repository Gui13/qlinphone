#include "accountpreferences.h"
#include "ui_accountpreferences.h"
#include <QTimer>
#include <QDebug>
#include <QPushButton>

AccountPreferences::AccountPreferences(QLinphoneCore *core, LinphoneProxyConfig* cfg, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AccountPreferences)
{
	qlc = core;
	proxy = cfg;
	new_proxy = (proxy == NULL);
	ui->setupUi(this);
	if( !new_proxy ){
		loadProxySettings();
	}
	setAttribute(Qt::WA_DeleteOnClose);
	ui->identity->setFocus();
	connect(ui->buttonBox,&QDialogButtonBox::accepted, this, &AccountPreferences::accepted);
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &AccountPreferences::checkFields);
	timer->start(1000);
}

void AccountPreferences::loadProxySettings() {
	ui->server->setText( linphone_proxy_config_get_server_addr(proxy) );
	ui->identity->setText(linphone_proxy_config_get_identity(proxy));
	ui->registrationPeriod->setValue(linphone_proxy_config_get_expires(proxy));
	QString transport = linphone_proxy_config_get_transport(proxy);
	ui->transport->setCurrentText(transport.toUpper());
	ui->route->setText(linphone_proxy_config_get_route(proxy));
	ui->enableRegistration->setChecked(linphone_proxy_config_register_enabled(proxy));
	ui->publishPresence->setChecked(linphone_proxy_config_publish_enabled(proxy));
	ui->enableAVPF->setChecked(linphone_proxy_config_avpf_enabled(proxy));
}

void AccountPreferences::applyProxy( LinphoneProxyConfig *cfg ) {
	linphone_proxy_config_edit(cfg);
	linphone_proxy_config_set_server_addr(cfg, ui->server->text().toStdString().c_str());
	linphone_proxy_config_set_identity(cfg,ui->identity->text().toStdString().c_str());
	linphone_proxy_config_set_expires(cfg,ui->registrationPeriod->value());

	if( ui->route->text() != "") linphone_proxy_config_set_route(cfg, ui->route->text().toStdString().c_str());

	linphone_proxy_config_enable_register(cfg, ui->enableRegistration->isChecked());
	linphone_proxy_config_enable_publish(cfg, ui->publishPresence->isChecked());
	linphone_proxy_config_enable_avpf(cfg, ui->enableAVPF->isChecked());

	linphone_proxy_config_done(cfg);
}

void AccountPreferences::accepted() {
	if(new_proxy) proxy = qlc->createNewProxy();

	applyProxy(proxy);

	if(new_proxy) qlc->addProxy(proxy);
}

void AccountPreferences::checkFields() {
	qDebug() << "Check fields";
	bool ok = checkField(ui->server, false);
	ok &= checkField(ui->identity, false);
	ok &= checkField(ui->route, true);
	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ok);
}

bool AccountPreferences::checkField(QLineEdit* field, bool optional) {
	if(optional && field->text() == "") {
		field->setStyleSheet("color: green");
		return true;
	}

	const char* fieldText = field->text().toStdString().c_str();
	LinphoneAddress *addr = linphone_address_new(fieldText);
	if( addr != NULL) {
		qDebug() << "Addr for" << field->text() << "is" << addr;
		field->setStyleSheet("color: green");
		linphone_address_destroy(addr);
		return true;
	} else {
		field->setStyleSheet("color: red");
		return false;
	}

}

AccountPreferences::~AccountPreferences()
{
	delete ui;
}
