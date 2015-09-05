#include "chatbubblelistdelegate.h"

#include <qpainter.h>
#include <QDebug>
#include "chatbubble.h"

ChatBubbleListDelegate::ChatBubbleListDelegate(QObject* parent) : QAbstractItemDelegate(parent)
{
    bubble = new ChatBubble();
}

ChatBubbleListDelegate::~ChatBubbleListDelegate()
{
    delete bubble;
}

void ChatBubbleListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant v = index.data();
    QLMessage* msg = v.value<QLMessage*>();

    bubble->setMsg(msg);
    bubble->setGeometry(QRect(QPoint(0,0),option.rect.size()));

    painter->save();
    painter->translate(option.rect.topLeft());
    bubble->render(painter);
    painter->restore();
}

QSize ChatBubbleListDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &index) const
{
    ChatBubble* bubble = new ChatBubble();
    bubble->setMsg(index.data().value<QLMessage*>());
    qDebug() << "sizehint" << bubble->sizeHint();
    return bubble->sizeHint();
}
