#ifndef CHATBUBBLELISTDELEGATE_H
#define CHATBUBBLELISTDELEGATE_H

#include <QAbstractItemDelegate>
#include "chatbubble.h"
class ChatBubbleListDelegate : public QAbstractItemDelegate
{
public:
    ChatBubbleListDelegate(QObject *parent = 0);
    ~ChatBubbleListDelegate();

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    ChatBubble *bubble;
};

#endif // CHATBUBBLELISTDELEGATE_H
