#include "qlchatroom.h"

#include <QDateTime>
#include <QDebug>


static void onMessageStateChanged(LinphoneChatMessage *msg, LinphoneChatMessageState state, void *userData)
{
	QLChatRoom *thiz = (QLChatRoom *)userData;
	if (state == LinphoneChatMessageStateInProgress) {
		thiz->appendMsg(msg);
	} else {
		thiz->updateMessage(msg);
	}
}


void QLChatRoom::sendMessage(const QString &msg)
{
	LinphoneChatMessage* chatmsg = linphone_chat_room_create_message(room, msg.toStdString().c_str());
	// will change rowCount(), that's why we get it above
	linphone_chat_room_send_message2(room, chatmsg,onMessageStateChanged, this);
}

void QLChatRoom::appendMsg(LinphoneChatMessage* msg){
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	msgs.append(new QLMessage(msg,this));
	endInsertRows();
}

void QLChatRoom::updateMessage(LinphoneChatMessage* msg){
	int i = 0;
	qDebug() << "Data changed!";
	for(auto m : msgs){
		if( m->uid() == linphone_chat_message_get_storage_id(msg) ){
			m->setMsg(msg);
			qDebug() << "Data changed for idx" << i << "new state" << m->state();
			emit dataChanged(index(i), index(i), QVector<int>(1,StatusRole));
		}
		i++;
	}
}


QVariant QLChatRoom::data(const QModelIndex &index, int role) const
{
    QLMessage* msg = msgs.at(index.row());
	switch(role){
	case Qt::DisplayRole:
        return QVariant::fromValue(msg);
	case Qt::ToolTipRole:
        return QVariant(msg->date().toString());
	case DateRole:
		return msg->formattedDate();
	case MessageRole:
		return msg->chatMessage();
	case StatusRole:
		return msg->statusColor();
	default: return QVariant();
	}
}

QVariant QLChatRoom::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role == Qt::DisplayRole ){
        return "Message text";
    } else {
        return QVariant();
	}
}

QHash<int, QByteArray> QLChatRoom::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles.insert(DateRole, "formattedDate");
	roles.insert(MessageRole, "chatMessage");
	roles.insert(StatusRole, "statusColor");
	return roles;
}

void QLChatRoom::onMessageReceived(QLChatRoom room, QLMessage msg)
{
	if( room.getRoom() != this->room ) return;
	//beginInsertRows(QModelIndex(), rowCount(), rowCount());
	beginResetModel();
	msgs.append(new QLMessage(msg));
	endResetModel();
	//endInsertRows();
}

void QLChatRoom::setRoom(LinphoneChatRoom *r)
{
	beginResetModel();
    room = r;
    msgs.clear();

    // setup new messages
    MSList* newMsgs = linphone_chat_room_get_history(room, 0);
    MSList* iter = newMsgs;

    while( iter ){
        msgs.append(new QLMessage((LinphoneChatMessage*)iter->data, this));
        // no need to ref, they are already ref'd
        iter = iter->next;
    }
	ms_list_free(newMsgs);
	endResetModel();
}
