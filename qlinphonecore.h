#ifndef QLINPHONECORE_H
#define QLINPHONECORE_H


#include <QObject>
#include "chatroommodel.h"
#include "linphone/linphonecore.h"

class QLinphoneCore : public QObject
{
    Q_OBJECT
public:
    explicit QLinphoneCore(QObject *parent = 0);
    ~QLinphoneCore();

    QList<LinphoneProxyConfig *> accounts() const;
	QList<ChatRoomModel> chatRooms() const;

signals:
	void chatRoomsUpdated(QList<ChatRoomModel> rooms);

public slots:

private:
    LinphoneCore* core;
};

#endif // QLINPHONECORE_H
