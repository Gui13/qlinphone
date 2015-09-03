#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QAbstractListModel>
#include "qlinphonecore.h"

class QLChatRooms : public QAbstractListModel
{
	Q_OBJECT

public:
	QLChatRooms(QLinphoneCore* qlc);
	~QLChatRooms();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

private:
    QLinphoneCore* qlc;
	QList<QLChatRoom> rooms;

private slots:
	void onChatRoomUpdate(QList<QLChatRoom> chatrooms);
};

Q_DECLARE_METATYPE(QLChatRoom)

#endif // CONVERSATIONMODEL_H
