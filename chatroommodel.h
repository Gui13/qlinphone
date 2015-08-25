#ifndef CHATROOMMODEL_H
#define CHATROOMMODEL_H

#include <QObject>
#include "linphone/linphonecore.h"

class ChatRoomModel : public QObject
{
	Q_OBJECT
public:
	explicit ChatRoomModel(QObject *parent = 0);
	ChatRoomModel(LinphoneChatRoom* r) : room(r) {}
	ChatRoomModel(const ChatRoomModel& other) : room(other.room) {}

	ChatRoomModel &operator =(const ChatRoomModel& other) {
		room = other.room;
		return *this;
	}

	int historySize() { return linphone_chat_room_get_history_size(room); }

signals:

public slots:

private:
	LinphoneChatRoom* room;
};

#endif // CHATROOMMODEL_H
