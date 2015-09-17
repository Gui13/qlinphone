#ifndef QLChatRoom_H
#define QLChatRoom_H

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <qlmessage.h>
#include "linphone/linphonecore.h"

class QLChatRoom : public QAbstractListModel
{
	Q_OBJECT
	enum QLMessageRole {
		MessageRole = Qt::UserRole + 1,
		DateRole,
		StatusRole
	 };
public:
	explicit QLChatRoom(QObject* parent = 0) : QAbstractListModel(parent), room(0) {}
	QLChatRoom(LinphoneChatRoom* r, QObject *parent = 0) : QAbstractListModel(parent) { setRoom(r);}
    QLChatRoom(const QLChatRoom& other) { setRoom(other.room);}

    QLChatRoom &operator =(const QLChatRoom& other) { room = other.room; return *this; }
    bool operator==(const QLChatRoom& other) { return room == other.room; }

	int realHistorySize() const   { return room?linphone_chat_room_get_history_size(room):0; }
	LinphoneChatRoom *getRoom() const { return room; }

	void sendMessage(const QString& msg);

    /* QAbstractListModel pure virtuals */
	int rowCount(const QModelIndex &parent = QModelIndex()) const { return msgs.size(); }
    QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	void appendMsg(LinphoneChatMessage *msg);
	void updateMessage(LinphoneChatMessage *msg);
protected:
	QHash<int, QByteArray> roleNames() const;

signals:

public slots:
	void onMessageReceived(QLChatRoom room, QLMessage msg);

private:
	LinphoneChatRoom* room;
    QList<QLMessage*> msgs;

    void setRoom(LinphoneChatRoom* r);
};

#endif // QLChatRoom_H
