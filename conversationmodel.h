#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QAbstractListModel>
#include "qlinphonecore.h"

class ConversationModel : public QAbstractListModel
{
	Q_OBJECT

public:
    ConversationModel(QLinphoneCore* qlc);
    ~ConversationModel();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

private:
    QLinphoneCore* qlc;
	QList<ChatRoomModel> rooms;

private slots:
	void onChatRoomUpdate(QList<ChatRoomModel> chatrooms);
};

Q_DECLARE_METATYPE(ChatRoomModel)

#endif // CONVERSATIONMODEL_H
