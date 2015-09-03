#include "qlchatrooms.h"

QLChatRooms::QLChatRooms(QLinphoneCore *lc): qlc(lc)
{
	rooms = qlc->chatRooms();
	connect(qlc, &QLinphoneCore::chatRoomsUpdated, this, &QLChatRooms::onChatRoomUpdate);
}

QLChatRooms::~QLChatRooms()
{

}

int QLChatRooms::rowCount(const QModelIndex &parent) const
{
	return rooms.size();
}

QVariant QLChatRooms::data(const QModelIndex &index, int role) const
{
	Q_UNUSED(role);
	return qVariantFromValue( rooms.at(index.row()) );
}

void QLChatRooms::onChatRoomUpdate(QList<QLChatRoom> chatrooms) {
	// TODO: for performance, we should use "dataChanged()" instead of this
	beginResetModel();
	rooms = chatrooms;
	endResetModel();
}
