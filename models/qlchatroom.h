#ifndef QLChatRoom_H
#define QLChatRoom_H

#include <QAbstractListModel>
#include <qlmessage.h>
#include "linphone/linphonecore.h"

class QLChatRoom : public QAbstractListModel
{
	Q_OBJECT
public:
    explicit QLChatRoom(QObject* parent = 0) : QAbstractListModel(parent) {}
    QLChatRoom(LinphoneChatRoom* r, QObject *parent = 0) : QAbstractListModel(parent) { setRoom(r);}
    QLChatRoom(const QLChatRoom& other) { setRoom(other.room);}

    QLChatRoom &operator =(const QLChatRoom& other) { room = other.room; return *this; }
    bool operator==(const QLChatRoom& other) { return room == other.room; }

    int historySize() const   { return linphone_chat_room_get_history_size(room); }
	LinphoneChatRoom *getRoom() const { return room; }

    /* QAbstractListModel pure virtuals */
    int rowCount(const QModelIndex &parent) const { return historySize(); }
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:

public slots:

private:
	LinphoneChatRoom* room;
    QList<QLMessage*> msgs;

    void setRoom(LinphoneChatRoom* r);
};

#endif // QLChatRoom_H
