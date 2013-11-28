#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiIonoCompute_H
#define _uiIonoCompute_H

#define NBIGP 201*7

#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ionoCorrections.hpp"
#include "ui_ionoPointInformationDisplay.h"
#include "ui_ionoComputeDisplayForm.h"
#include "GPSTK_Nav.hpp"
#include "GPSTK_Obs.hpp"



namespace Ui {

class ionoPPInfo : public QObject,  protected ionoPPInformationDisplay
{
	Q_OBJECT

public:

	ionoPPInfo(int x, int y, QWidget *page);

	void display(int lat, int longi, double sigmaGIVE, double vertDelay, double eps);

};



class uiIonoCompute : public QObject,  protected ionoComputeDisplayForm
{
	Q_OBJECT

public:

	uiIonoCompute(GPSTK_Nav *curNavData, GPSTK_Obs *curObsData);

	void setupUi(QWidget *parent);

public slots:

	void display();

protected:

	GPSTK_Nav *curNavData;
	GPSTK_Obs *curObsData;

	typedef struct
	{
		ionoPPInfo* ul;
		ionoPPInfo* ur;
		ionoPPInfo* dl;
		ionoPPInfo* dr;
	} structSquarePPInfo;

	typedef struct
	{
		ionoPPInfo* igp1;
		ionoPPInfo* igp2;
		ionoPPInfo* igp3;
	} structTrianglePPInfo;

	structSquarePPInfo squarePPInfo;
	structTrianglePPInfo type1TrPPInfo, type2TrPPInfo, type3TrPPInfo, type4TrPPInfo;





};

}// END namespace Ui


#endif