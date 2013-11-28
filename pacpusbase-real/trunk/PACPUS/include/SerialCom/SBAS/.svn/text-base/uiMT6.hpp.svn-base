#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiMT6_H
#define _uiMT6_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_MT6DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_MT6.hpp"

namespace Ui {
//MT2, MT3, MT4, MT5
class uiMT6 : public SerialCOM_Msg_Ui, protected MT6DisplayForm
{
	Q_OBJECT

public: 
	
	void setupUi(QWidget *parent);

	void display(SBAS::structIntegrityInformation data);

public slots:

	void display(SerialCOM_Msg *pMsg);


protected:

	SBAS::structIntegrityInformation data;

	QTableWidgetItem *TWISatMask[51];
	QTableWidgetItem *TWIUDREI[51];
	QTableWidgetItem *TWIUDRE[51];
	QTableWidgetItem *TWISigmaUDRE[51];

};

}// END namespace Ui


#endif