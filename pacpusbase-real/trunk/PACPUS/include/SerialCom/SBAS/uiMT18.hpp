#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiMT18_H
#define _uiMT18_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_MT18DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_MT18.hpp"


namespace Ui {
class uiMT18 : public SerialCOM_Msg_Ui, protected MT18DisplayForm
{
	Q_OBJECT

public: 

	uiMT18();
	
	void setupUi(QWidget *parent);
	
	void display(SBAS::structIonosphericGridPointMask data);

public slots:

	
	void display(SerialCOM_Msg *pMsg);


protected:

	
	QTableWidgetItem *IGPNumber[201];
	QTableWidgetItem *IGPMask[201];

};

}// END namespace Ui


#endif