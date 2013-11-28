#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiMT1_H
#define _uiMT1_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_MT1DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_MT1.hpp"

namespace Ui {
//MT2, MT3, MT4, MT5
class uiMT1 : public SerialCOM_Msg_Ui, protected MT1DisplayForm
{
	Q_OBJECT

public: 
	
	void setupUi(QWidget *parent);

	void display(SBAS::structPRNMaskAssignement data);

public slots:

	void display(SerialCOM_Msg *pMsg);


protected:

	SBAS::structPRNMaskAssignement data;

	QTableWidgetItem *TWIGPSSatPRN[37];
	QTableWidgetItem *TWIGPSSatMask[37];
	QTableWidgetItem *TWIGLONASSSatPRN[24];
	QTableWidgetItem *TWIGLONASSSatMask[24];
	QTableWidgetItem *TWIFutGNSSSatPRN[58];
	QTableWidgetItem *TWIFutGNSSSatMask[58];
	QTableWidgetItem *TWIGEOWAASSatPRN[19];
	QTableWidgetItem *TWIGEOWAASSatMask[19];
	QTableWidgetItem *TWIFutAllSatPRN[72];
	QTableWidgetItem *TWIFutAllSatMask[72];

	void initTableWidget(QTableWidget *tW, QTableWidgetItem *TWISatPRN[], QTableWidgetItem *TWISatMask[], int start, int size);
};

}// END namespace Ui


#endif