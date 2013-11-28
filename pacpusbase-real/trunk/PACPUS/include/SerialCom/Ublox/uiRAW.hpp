#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiRAW_H
#define _uiRAW_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include <QMetaType>
#include "qstring.h"
#include "ui_RAW_DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_RXM_RAW.hpp"


namespace Ui {

class uiRAW : public SerialCOM_Msg_Ui, protected RAW_DisplayForm
{
	Q_OBJECT

public: 

	//uiRAW();

	void setupUi(QWidget *parent);

public slots:

	void display(SerialCOM_Msg *pMsg);

	void display(Ublox::structRXM_RAW data);

protected:

	QTableWidgetItem *TWISV[12];
	QTableWidgetItem *TWIQI[12];
	QTableWidgetItem *TWISNR[12];
	QTableWidgetItem *TWICP[12];
	QTableWidgetItem *TWIPR[12];
	QTableWidgetItem *TWIDOP[12];

	void initTableWidget(QTableWidget *tW, QTableWidgetItem *TWISatPRN[], QTableWidgetItem *TWISatMask[], int start, int size);

};

}// END namespace Ui


#endif