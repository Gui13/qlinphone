#include "qlproxy.h"

QLProxy::QLProxy(LinphoneProxyConfig *cfg, QObject *parent) : QObject(parent), proxy(cfg)
{

}

