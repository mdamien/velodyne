#ifndef _SerialCOM_Msg_Ui_H
#define _SerialCOM_Msg_Ui_H

#include <QtGui/QWidget>
#include <qobject.h>
#include <typeinfo>
#include "SerialCOM_Msg.hpp"

class SerialCOM_Msg_Ui : public QObject
{
	Q_OBJECT
public: 

	virtual void setupUi(QWidget *parent)=0;

public slots:

	virtual void display(SerialCOM_Msg *pMsg)=0;



};

#endif