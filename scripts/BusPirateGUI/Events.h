#ifndef __EVENT_H
#define __EVENT_H

#include <QEvent>
#include <QString>

enum BPEventType
{
	BPStatusMsgEvent = QEvent::User,
	BPPortStatusMsgEvent,
	AsciiHexLogMsgEvent,
	SpiLogMsgEvent,
	I2CLogMsgEvent,
	OneWireLogMsgEvent,
};

class AsciiHexLogMsgEvent : public QEvent
{
public:
	QString msg;
	AsciiHexLogMsgEvent(QString & msg);
};

class SpiLogMsgEvent : public QEvent
{
public:
	QString msg;
	SpiLogMsgEvent(QString & msg);
};

class I2CLogMsgEvent : public QEvent
{
public:
	QString msg;
	I2CLogMsgEvent(QString & msg);
};

class OneWireLogMsgEvent : public QEvent
{
public:
	QString msg;
	OneWireLogMsgEvent(QString & msg);
};

class BPStatusMsgEvent : public QEvent
{
public:
	QString msg;
	BPStatusMsgEvent(QString & msg);
};

class BPPortStatusMsgEvent : public QEvent
{
public:
	QString msg;
	BPPortStatusMsgEvent(QString & msg);
};

#endif

