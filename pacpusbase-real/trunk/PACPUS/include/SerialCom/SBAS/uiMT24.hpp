#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiMT24_H
#define _uiMT24_H

#define NB_ROW 6

#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_MT24DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_MT24.hpp"

namespace Ui {
//MT2, MT3, MT4, MT5
class uiMT24 : public SerialCOM_Msg_Ui,  protected MT24DisplayForm
{
	Q_OBJECT 

public: 

	uiMT24();
	
	void setupUi(QWidget *parent);

	void display(SBAS::structMixedFastCorrectionLongTermError data);

public slots:

	void display(SerialCOM_Msg *pMsg);


protected:

	
	short nbRow;
	short startRow;

	SBAS::structMixedFastCorrectionLongTermError data;

	QTableWidgetItem *TWISatMask[NB_ROW];
	QTableWidgetItem *TWIPR[NB_ROW];
	QTableWidgetItem *TWIUDREI[NB_ROW];
	QTableWidgetItem *TWIUDRE[NB_ROW];
	QTableWidgetItem *TWISigmaUDRE[NB_ROW];

};

}// END namespace Ui


#endif