#include "qlmessage.h"
#include "linphone/linphonecore.h"
#include "QDateTime"

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

bool QLMessage::hasBodyURL() const
{
    return linphone_chat_message_get_external_body_url(msg) != NULL;
}

QString QLMessage::text() const
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

QString QLMessage::from() const
{
	const LinphoneAddress* fromAddr = linphone_chat_message_get_from_address(msg);
	char* url = linphone_address_as_string_uri_only(fromAddr);
	QString from = url;
	ms_free(url);
	return from;
}

