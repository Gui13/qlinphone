#include "qlmessage.h"
#include "linphone/linphonecore.h"
#include <QDateTime>
#include <QColor>

QLMessage::QLMessage(LinphoneChatMessage *msg, QObject *parent) : QObject(parent)
{
	this->msg = linphone_chat_message_ref(msg);
}

QLMessage::QLMessage(const QLMessage &orig)
{
	msg = linphone_chat_message_ref(orig.msg);
}

QLMessage::~QLMessage()
{
	if( msg ){
		linphone_chat_message_unref(msg);
	}
}

void QLMessage::setMsg(LinphoneChatMessage *m)
{
	if( msg ){
		linphone_chat_message_unref(msg);
	}
	msg = linphone_chat_message_ref(m);
}

bool QLMessage::hasBodyURL() const
{
	return linphone_chat_message_get_external_body_url(msg) != NULL;
}

bool QLMessage::isOutgoing() const
{
	return linphone_chat_message_is_outgoing(msg);
}

QString QLMessage::chatMessage() const
{
	QString t;
	const char* text = linphone_chat_message_get_text(msg);
	if( text ) t = text;
	return t;
}

QString QLMessage::state() const
{
	return linphone_chat_message_state_to_string(linphone_chat_message_get_state(msg));
}

QDateTime QLMessage::date() const {
	return QDateTime::fromTime_t(linphone_chat_message_get_time(msg));
}

QColor QLMessage::statusColor() const
{
	switch(linphone_chat_message_get_state(msg)){
	case LinphoneChatMessageStateDelivered: return QColor("green");
	case LinphoneChatMessageStateInProgress: return QColor("orange");
	case LinphoneChatMessageStateNotDelivered: return QColor("red");
	}
	return QColor("grey");
}

unsigned long QLMessage::uid() const
{
	return linphone_chat_message_get_storage_id(msg);
}

QString QLMessage::from() const
{
	const LinphoneAddress* fromAddr = linphone_chat_message_get_from_address(msg);
	char* url = linphone_address_as_string_uri_only(fromAddr);
	QString from = url;
	ms_free(url);
	return from;
}

QString QLMessage::formattedDate() const
{
	return date().toString();
}

