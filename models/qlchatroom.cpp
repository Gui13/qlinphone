#include "qlchatroom.h"

#include <QDateTime>
QVariant QLChatRoom::data(const QModelIndex &index, int role) const
{
    QLMessage* msg = msgs.at(index.row());
    if (role == Qt::DisplayRole ){
        return QVariant::fromValue(msg);
    } else if( role == Qt::ToolTipRole ){
        return QVariant(msg->date().toString());
    } else {
        return QVariant();
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

void QLChatRoom::setRoom(LinphoneChatRoom *r)
{
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
}
