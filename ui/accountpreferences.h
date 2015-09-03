#ifndef ACCOUNTPREFERENCES_H
#define ACCOUNTPREFERENCES_H

#include <QDialog>
#include <QLineEdit>
#include "linphone/linphonecore.h"
#include "qlinphonecore.h"

namespace Ui {
class AccountPreferences;
}

class AccountPreferences : public QDialog
{
	Q_OBJECT

public:
	AccountPreferences(QLinphoneCore *core, LinphoneProxyConfig* config, QWidget *parent = 0);
	~AccountPreferences();

public slots:
	void acceptPressed();

private slots:
	void checkFields();

private:
	Ui::AccountPreferences *ui;
	LinphoneProxyConfig *proxy;
	QLinphoneCore *qlc;
	bool new_proxy;
	void loadProxySettings();
	void applyProxy(LinphoneProxyConfig *cfg);

	// Validation of fields

	bool checkField(QLineEdit* field, bool optional);
};

#endif // ACCOUNTPREFERENCES_H
