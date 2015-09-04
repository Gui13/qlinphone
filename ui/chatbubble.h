#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QWidget>
#include "qlmessage.h"

namespace Ui {
class ChatBubble;
}

class ChatBubble : public QWidget
{
    Q_OBJECT

public:
    ChatBubble(QLMessage* msg, QWidget *parent = 0);
    explicit ChatBubble(QWidget *parent = 0) : QWidget(parent) {}
    ~ChatBubble();

    Q_PROPERTY(QLMessage* msg READ msg WRITE setMsg NOTIFY msgChanged)

    QLMessage* msg() const { return m_msg; }

public slots:

    void setMsg(QLMessage* arg);

signals:

    void msgChanged(QLMessage* arg);

private:
    Ui::ChatBubble *ui;
    QLMessage* m_msg;
};

#endif // CHATBUBBLE_H
