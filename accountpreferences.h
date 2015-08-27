#ifndef ACCOUNTPREFERENCES_H
#define ACCOUNTPREFERENCES_H

#include <QDialog>

namespace Ui {
class AccountPreferences;
}

class AccountPreferences : public QDialog
{
	Q_OBJECT

public:
	explicit AccountPreferences(QWidget *parent = 0);
	~AccountPreferences();

private:
	Ui::AccountPreferences *ui;
};

#endif // ACCOUNTPREFERENCES_H
