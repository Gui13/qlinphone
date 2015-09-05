#ifndef QLMESSAGE_H
#define QLMESSAGE_H

#include <QObject>
#include "linphone/linphonecore.h"

class QLMessage : public QObject
{
	Q_OBJECT
public:
	QLMessage(LinphoneChatMessage *msg, QObject *parent = 0);
	QLMessage(const QLMessage& orig);
	~QLMessage();

    bool hasBodyURL() const;
	bool isOutgoing() const;

	QString text() const;
	QString state() const;
	QString from() const;

    QDateTime date() const;
public slots:

private:
	LinphoneChatMessage* msg;
};

Q_DECLARE_METATYPE(QLMessage*)

#endif // QLMESSAGE_H
