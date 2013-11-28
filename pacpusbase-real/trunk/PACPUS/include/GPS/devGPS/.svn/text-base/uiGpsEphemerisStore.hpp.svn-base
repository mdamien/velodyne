#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiGpsEphemerisStore_H
#define _uiGpsEphemerisStore_H


#include <QtGui/QLineEdit>
#include <QtGui/QTreeView>
#include <QtGui/QTreeWidgetItem>
#include "qstring.h"
#include "SourceID.hpp"
#include "DayTime.hpp"
#include "SatID.hpp"
#include "TypeID.hpp"
#include "GPSEphemerisStore.hpp"
#include "GPSAlmanacStore.hpp"
#include "IonoModelStore.hpp"
#include "ui_gpsEphemerisStoreDisplayForm.h"



namespace Ui {
class uiGpsEphemerisStore : public QObject, protected gpsEphemerisStoreDisplayForm
{
	Q_OBJECT

public: 

	uiGpsEphemerisStore();
	
	void setupUi(QWidget *parent);

public slots:

	void display(const gpstk::GPSEphemerisStore *ephData);


protected:

	/*QTableWidgetItem tableItems[12][50];
	QTableWidgetItem tableRows[12];
	QTableWidgetItem tableColumns[50];*/

};

}// END namespace Ui


#endif