#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiMT25_H
#define _uiMT25_H

#define NB_ROW 6

#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_MT25DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_MT25.hpp"

namespace Ui {
//MT2, MT3, MT4, MT5
class uiMT25 : public SerialCOM_Msg_Ui,  protected MT25DisplayForm
{
	Q_OBJECT 

public: 

	uiMT25();
	
	void setupUi(QWidget *parent);

	void display(SBAS::structLongTermSatelliteErrorCorrections data);

public slots:


	void display(SerialCOM_Msg *pMsg);


protected:

	
	short nbRow;
	short startRow;


};

}// END namespace Ui


#endif