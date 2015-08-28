#ifndef QLPROXY_H
#define QLPROXY_H

#include <QObject>
#include "linphone/linphonecore.h"

class QLProxy : public QObject
{
	Q_OBJECT
public:
	QLProxy(LinphoneProxyConfig *cfg, QObject *parent = 0);
	QLProxy(const QLProxy& orig) { proxy = orig.proxy; }
	LinphoneProxyConfig* proxy;

signals:

public slots:
};

#endif // QLPROXY_H
