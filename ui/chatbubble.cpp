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

ChatBubble::ChatBubble(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatBubble)
{
    ui->setupUi(this);
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
        ui->textBrowser->setText("(image)");
    } else {
        ui->textBrowser->setText(m_msg->text());
    }

	if( m_msg->isOutgoing() ){
		ui->textBrowser->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
	} else {
		ui->textBrowser->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	}

    ui->datelabel->setText(m_msg->date().toString());
    emit msgChanged(arg);
}
