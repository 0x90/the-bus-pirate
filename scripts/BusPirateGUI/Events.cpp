#include <QEvent>
#include "Events.h"
AsciiHexLogMsgEvent::AsciiHexLogMsgEvent(QString & msg) : 
	QEvent(static_cast<QEvent::Type>(::AsciiHexLogMsgEvent))
{
	this->msg = msg;
}

BPStatusMsgEvent::BPStatusMsgEvent(QString & msg) : 
	QEvent(static_cast<QEvent::Type>(::BPStatusMsgEvent))
{
	this->msg = msg;
}

