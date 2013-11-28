#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiMT2to5_H
#define _uiMT2to5_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_MT2to5DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_MT2to5.hpp"

namespace Ui {
//MT2, MT3, MT4, MT5
class uiMT2to5 : public SerialCOM_Msg_Ui,  protected MT2to5DisplayForm
{
	Q_OBJECT 

public: 

	uiMT2to5(char MTnumber);
	
	void setupUi(QWidget *parent);

	void display(SBAS::structFastCorrections data);

public slots:

	void display(SerialCOM_Msg *pMsg);


protected:

	
	short nbRow;
	short startRow;

	unsigned char MTnumber;

	SBAS::structFastCorrections data;

	QTableWidgetItem *TWISatMask[13];
	QTableWidgetItem *TWIPR[13];
	QTableWidgetItem *TWIUDREI[13];
	QTableWidgetItem *TWIUDRE[13];
	QTableWidgetItem *TWISigmaUDRE[13];

};

}// END namespace Ui


#endif