#include "accountpreferences.h"
#include "ui_accountpreferences.h"

AccountPreferences::AccountPreferences(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AccountPreferences)
{
	ui->setupUi(this);
}

AccountPreferences::~AccountPreferences()
{
	delete ui;
}
