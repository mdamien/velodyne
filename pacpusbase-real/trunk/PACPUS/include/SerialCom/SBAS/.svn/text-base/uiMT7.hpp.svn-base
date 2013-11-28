#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiMT7_H
#define _uiMT7_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_MT7DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_MT7.hpp"

namespace Ui {
//MT2, MT3, MT4, MT5
class uiMT7 : public SerialCOM_Msg_Ui, protected MT7DisplayForm
{
	Q_OBJECT

public: 
	
	void setupUi(QWidget *parent);

	void display(SBAS::structFastCorrectionDegradationFactor data);

public slots:

	void display(SerialCOM_Msg *pMsg);


protected:

	SBAS::structFastCorrectionDegradationFactor data;

	QTableWidgetItem *TWISatMask[51];
	QTableWidgetItem *TWIai[51];
	QTableWidgetItem *TWIa[51];
	QTableWidgetItem *TWILfcNPA[51];
	QTableWidgetItem *TWILfcPA[51];
	QTableWidgetItem *TWIMaxUpdInterval[51];

};

}// END namespace Ui


#endif