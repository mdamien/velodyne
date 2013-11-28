#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiIonoGrid_H
#define _uiIonoGrid_H

#define NBIGP 201*7

#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ionoCorrections.hpp"
#include "ui_ionoGridDisplayForm.h"

#define ILATMAX_ 35
#define ILONGMAX_ 32

namespace Ui {

class uiIonoGrid : public QObject,  protected ionoGridDisplayForm
{
	Q_OBJECT

public:

	uiIonoGrid(SBAS::ionoCorrections *ionoCorClass);

	void setupUi(QWidget *parent);

public slots:

	void display();

protected:


	short nbRow;
	short startRow;

	SBAS::ionoCorrections *ionoCorClass;

	QTableWidgetItem *TWIBand[NBIGP];
	QTableWidgetItem *TWIIGP[NBIGP];
	QTableWidgetItem *TWIVD[NBIGP];
	QTableWidgetItem *TWIGIVE[NBIGP];
	QTableWidgetItem *TWISigmaGIVE[NBIGP];
	QTableWidgetItem *TWIPosition[NBIGP];
	QTableWidgetItem *TWIMonitored[NBIGP];
	QTableWidgetItem *TWITor[NBIGP];


	QTableWidgetItem *TWILatLongMask[ILATMAX_][ILONGMAX_];

};

}// END namespace Ui


#endif