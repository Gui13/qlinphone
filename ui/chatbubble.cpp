#include "chatbubble.h"
#include "ui_chatbubble.h"

#include <QDateTime>

ChatBubble::ChatBubble(QLMessage *msg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatBubble)
{
    ui->setupUi(this);
    setMsg(msg);
}

ChatBubble::~ChatBubble()
{
    delete ui;
}

void ChatBubble::setMsg(QLMessage *arg)
{
    if (m_msg == arg)
        return;

    m_msg = arg;
    if( m_msg->hasBodyURL() ){
        ui->text->setText("(image)");
    } else {
        ui->text->setText(m_msg->text());
    }

    ui->datelabel->setText(m_msg->date().toString());
    emit msgChanged(arg);
}
