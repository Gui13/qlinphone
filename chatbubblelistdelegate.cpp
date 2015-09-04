#include "chatbubblelistdelegate.h"

#include <qpainter.h>
#include <QDebug>
#include "chatbubble.h"

ChatBubbleListDelegate::ChatBubbleListDelegate(QObject* parent) : QAbstractItemDelegate(parent)
{

}

ChatBubbleListDelegate::~ChatBubbleListDelegate()
{

}

void ChatBubbleListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant v = index.data();
    QLMessage* msg = v.value<QLMessage*>();
    ChatBubble *bubble = new ChatBubble(msg);
    //bubble.setGeometry(QRect(QPoint(0,0),option.rect.size()));
    bubble->setGeometry(QRect(QPoint(0,0),option.rect.size()));
    painter->save();
    painter->translate(option.rect.topLeft());
    qDebug() << "Geometry for msg" << msg->text() << "is" << bubble->geometry() << "with options" << option;
    bubble->render(painter);
    delete bubble;
    painter->restore();
}

QSize ChatBubbleListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    ChatBubble bubble(index.data().value<QLMessage*>());
    qDebug() << "Size for msg is" << bubble.sizeHint();
    return bubble.sizeHint();
}
