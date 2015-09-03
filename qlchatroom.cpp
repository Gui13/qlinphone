#include "qlchatroom.h"

#include <QDateTime>
QVariant QLChatRoom::data(const QModelIndex &index, int role) const
{
    auto msg = msgs.at(index.row());
    if (role == Qt::DisplayRole ){

        const char* text = linphone_chat_message_get_text(msg);
        const char* bodyUrl = linphone_chat_message_get_external_body_url(msg);
        if( bodyUrl ){
            return QVariant("[Image]");
        } else if (text){
            return QVariant(text);
        } else {
            return QString("Unknown message %1").arg(index.row());
        }

    } else if( role == Qt::ToolTipRole ){
        auto time = linphone_chat_message_get_time(msg);
        QDateTime date = QDateTime::fromTime_t(time);
        return QVariant(date);
    } else {
        return QVariant();
    }
}

void QLChatRoom::setRoom(LinphoneChatRoom *r)
{
    room = r;
    // clean old messages
    foreach (auto msg, msgs) {
        linphone_chat_message_unref(msg);
    }
    msgs.clear();

    // setup new messages
    MSList* newMsgs = linphone_chat_room_get_history(room, 0);
    MSList* iter = newMsgs;

    while( iter ){
        msgs.append((LinphoneChatMessage*)iter->data);
        // no need to ref, they are already ref'd
        iter = iter->next;
    }
}
