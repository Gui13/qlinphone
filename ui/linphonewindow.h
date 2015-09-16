#ifndef LINPHONEWINDOW_H
#define LINPHONEWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QStandardItemModel>
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

	void loadChatRooms();
public slots:
    void messageReceived(QLChatRoom room, QLMessage message);
private slots:
    void on_addConversationBtn_clicked();

	void on_accountOptions_clicked();
	void accountOptions_Action_Triggered(QAction *action);
	void setupProxyList();

	void prefsAccepted(QObject *);

	void registrationStateChanged(QLProxy cfg, LinphoneRegistrationState state);

	void on_searchBar_textChanged(const QString &arg1);

	void on_searchBar_returnPressed();

	void on_accountCombo_currentIndexChanged(int index);

    void on_itemchatroomlist_currentRowChanged(int currentRow);

    void on_sendMessage_clicked();

    void on_messageBox_textChanged(const QString &arg1);

private:
    Ui::LinphoneWindow *ui;
	QLinphoneCore* core;
	QStandardItemModel *chatRoomsModel;
	void displayProxyPreferences(LinphoneProxyConfig *proxy);
	LinphoneProxyConfig *getCurrentSelectedProxy();
	bool validateAddress(QLineEdit *field);
	QString getProxyColorForState(LinphoneRegistrationState state);
	void setAccountIconColor(int proxy_index, const QString &color);
};

#endif // LINPHONEWINDOW_H
