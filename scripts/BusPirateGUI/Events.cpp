#include <QEvent>
#include "Events.h"

BPPortStatusMsgEvent::BPPortStatusMsgEvent(QString & msg) : 
	QEvent(static_cast<QEvent::Type>(::BPPortStatusMsgEvent))
{
	this->msg = msg;
}

BPStatusMsgEvent::BPStatusMsgEvent(QString & msg) : 
	QEvent(static_cast<QEvent::Type>(::BPStatusMsgEvent))
{
	this->msg = msg;
}

AsciiHexLogMsgEvent::AsciiHexLogMsgEvent(QString & msg) : 
	QEvent(static_cast<QEvent::Type>(::AsciiHexLogMsgEvent))
{
	this->msg = msg;
}

SpiLogMsgEvent::SpiLogMsgEvent(QString & msg) : 
	QEvent(static_cast<QEvent::Type>(::SpiLogMsgEvent))
{
	this->msg = msg;
}

I2CLogMsgEvent::I2CLogMsgEvent(QString & msg) : 
	QEvent(static_cast<QEvent::Type>(::I2CLogMsgEvent))
{
	this->msg = msg;
}

OneWireLogMsgEvent::OneWireLogMsgEvent(QString & msg) : 
	QEvent(static_cast<QEvent::Type>(::OneWireLogMsgEvent))
{
	this->msg = msg;
}

