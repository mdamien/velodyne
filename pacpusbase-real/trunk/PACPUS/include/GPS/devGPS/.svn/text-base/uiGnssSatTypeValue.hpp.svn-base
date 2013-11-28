#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiGnssSatTypeValue_H
#define _uiGnssSatTypeValue_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "DataStructures.hpp"
#include "ui_gnssSatTypeValueDisplayForm.h"


//typedef  std::map<int, gpstk::TypeID> columnTypeMap;
//typedef  std::map<int, gpstk::TypeID> rowSatMap;
//typedef  std::map<gpstk::TypeID , QTableWidgetItem> typeWidgetItemMap;
//typedef  std::map<gpstk::SatID, QTableWidgetItem> satWidgetItemMap;
//typedef  std::map<gpstk::SatID, typeWidgetItemMap> satTypeWidgetItemMap;

namespace Ui {
class uiGnssSatTypeValue : public QObject, protected gnssSatTypeValueDisplayForm
{
	Q_OBJECT

public: 

	uiGnssSatTypeValue();
	
	void setupUi(QWidget *parent);

public slots:

	void display(gpstk::gnssSatTypeValue gnssData);


protected:

	
	short nbRow;
	short startRow;

	//gnssSatTypeValue : gnssData<sourceEpochHeader, satTypeValueMap>
	//satTypeValueMap std::map<SatID, typeValueMap>
	//typeValueMap	std::map<TypeID, double>

	//satTypeWidgetItemMap  tableItems;
	/*QTableWidgetItem tableItems[12][50];
	QTableWidgetItem tableRows[12];
	QTableWidgetItem tableColumns[50];*/

};

}// END namespace Ui


#endif