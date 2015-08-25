#include "conversationmodel.h"

ConversationModel::ConversationModel(QLinphoneCore *lc): qlc(lc)
{
	rooms = qlc->chatRooms();
	connect(qlc, &QLinphoneCore::chatRoomsUpdated, this, &ConversationModel::onChatRoomUpdate);
}

ConversationModel::~ConversationModel()
{

}

int ConversationModel::rowCount(const QModelIndex &parent) const
{
	return rooms.size();
}

QVariant ConversationModel::data(const QModelIndex &index, int role) const
{
	Q_UNUSED(role);
	return qVariantFromValue( rooms.at(index.row()) );
}

void ConversationModel::onChatRoomUpdate(QList<ChatRoomModel> chatrooms) {

}
