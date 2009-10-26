#ifndef __EVENT_H
#define __EVENT_H

#include <QEvent>
#include <QString>

enum BPEventType
{
	BPStatusMsgEvent = QEvent::User,
	AsciiHexLogMsgEvent,
	SpiLogMsgEvent,
	I2CLogMsgEvent,
	OneWireLogMsgEvent
};

class AsciiHexLogMsgEvent : public QEvent
{
public:
	QString msg;
	AsciiHexLogMsgEvent(QString & msg);
};

class AsciiHexStatusMsgEvent : public QEvent
{
public:
	QString msg;
	AsciiHexStatusMsgEvent(QString & msg);
};

class BPStatusMsgEvent : public QEvent
{
public:
	QString msg;
	BPStatusMsgEvent(QString & msg);
};

#endif