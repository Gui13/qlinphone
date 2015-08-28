#ifndef QLPROXY_H
#define QLPROXY_H

#include <QObject>

class QLProxy : public QObject
{
	Q_OBJECT
public:
	explicit QLProxy(QObject *parent = 0);

signals:

public slots:
};

#endif // QLPROXY_H
