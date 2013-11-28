#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiFastCorrections_H
#define _uiFastCorrections_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "fastCorrections.hpp"
#include "ui_fastCorrectionsDisplayForm.h"



namespace Ui {
class uiFastCorrections : public QObject, protected fastCorrectionsDisplayForm
{
	Q_OBJECT

public: 

	uiFastCorrections();
	
	void setupUi(QWidget *parent);

public slots:

	void display(SBAS::fastCorrections *Sfcorr);


protected:

	
	short nbRow;
	short startRow;

	QTableWidgetItem tableRows[12];
	QTableWidgetItem tableColumns[50];

};

}// END namespace Ui


#endif