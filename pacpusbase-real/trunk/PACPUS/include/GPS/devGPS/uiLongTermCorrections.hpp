#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiLongTermCorrections_H
#define _uiLongTermCorrections_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "SBASCorrectedEphemerisRange.hpp"
#include "ui_LongTermCorrectionsDisplayForm.h"



namespace Ui {
class uiLongTermCorrections : public QObject, protected LongTermCorrectionsDisplayForm
{
	Q_OBJECT

public: 

	uiLongTermCorrections();
	
	void setupUi(QWidget *parent);

public slots:

	void display(SBAS::SBASCorrectedEphemerisRange* pSBASCorrEphRange);


protected:

	
	short nbRow;
	short startRow;

	QTableWidgetItem tableRows[12];
	QTableWidgetItem tableColumns[50];

};

}// END namespace Ui


#endif