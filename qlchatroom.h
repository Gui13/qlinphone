#ifndef QLChatRoom_H
#define QLChatRoom_H

#include <QObject>
#include "linphone/linphonecore.h"

class QLChatRoom : public QObject
{
	Q_OBJECT
public:
	explicit QLChatRoom(QObject *parent = 0);
	QLChatRoom(LinphoneChatRoom* r) : room(r) {}
	QLChatRoom(const QLChatRoom& other) : room(other.room) {}

	QLChatRoom &operator =(const QLChatRoom& other) {
		room = other.room;
		return *this;
	}

	int historySize() { return linphone_chat_room_get_history_size(room); }

signals:

public slots:

private:
	LinphoneChatRoom* room;
};

#endif // QLChatRoom_H
