#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiMT26_H
#define _uiMT26_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_MT26DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_MT26.hpp"

namespace Ui {

class uiMT26 : public SerialCOM_Msg_Ui,  protected MT26DisplayForm
{
	Q_OBJECT 

public: 

	uiMT26();
	
	void setupUi(QWidget *parent);

	void display(SBAS::structIonosphericDelayCorrections data);

public slots:

	void display(SerialCOM_Msg *pMsg);


protected:

	SBAS::structFastCorrections data;

	QTableWidgetItem *TWIIGP[13];
	QTableWidgetItem *TWIVD[13];
	QTableWidgetItem *TWIGIVEI[13];
	QTableWidgetItem *TWIGIVE[13];
	QTableWidgetItem *TWISigmaGIVE[13];

};

}// END namespace Ui


#endif