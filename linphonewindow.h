#ifndef LINPHONEWINDOW_H
#define LINPHONEWINDOW_H

#include <QMainWindow>
#include "linphone/linphonecore.h"
#include "qlinphonecore.h"

namespace Ui {
class LinphoneWindow;
}

class LinphoneWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LinphoneWindow(QWidget *parent = 0);
    ~LinphoneWindow();

private slots:
    void on_addConversationBtn_clicked();

	void on_accountOptions_clicked();
	void accountOptions_Action_Triggered(QAction *action);

private:
    Ui::LinphoneWindow *ui;
    QLinphoneCore* core;
};

#endif // LINPHONEWINDOW_H
