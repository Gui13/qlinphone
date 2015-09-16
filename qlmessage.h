#ifndef QLMESSAGE_H
#define QLMESSAGE_H

#include <QObject>
#include <QColor>
#include "linphone/linphonecore.h"

class QLMessage : public QObject
{
	Q_OBJECT
public:
	QLMessage(LinphoneChatMessage *msg, QObject *parent = 0);
	QLMessage(const QLMessage& orig);
	~QLMessage();

	Q_PROPERTY(QString chatMessage READ chatMessage)
	Q_PROPERTY(QString formattedDate READ formattedDate)
	Q_PROPERTY(QString from READ from)
	Q_PROPERTY(QString state READ state)
	Q_PROPERTY(bool hasBodyURL READ hasBodyURL)
	Q_PROPERTY(bool isOutgoing READ isOutgoing)
	Q_PROPERTY(QColor statusColor READ statusColor)

	bool hasBodyURL() const;
	bool isOutgoing() const;

	QString chatMessage() const;
	QString state() const;
	QString from() const;
	QString formattedDate() const;

	QDateTime date() const;
	QColor statusColor() const;

public slots:

private:
	LinphoneChatMessage* msg;
};

Q_DECLARE_METATYPE(QLMessage*)

#endif // QLMESSAGE_H
