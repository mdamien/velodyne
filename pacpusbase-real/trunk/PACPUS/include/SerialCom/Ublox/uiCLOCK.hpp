#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiCLOCK_H
#define _uiCLOCK_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_CLOCK_DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_NAV_CLOCK.hpp"

namespace Ui {

class uiCLOCK : public SerialCOM_Msg_Ui, protected CLOCK_DisplayForm
{
	Q_OBJECT

public: 

	void setupUi(QWidget *parent);

public slots:

	void display(SerialCOM_Msg *pMsg);

	void display(Ublox::structNAV_CLOCK data);

protected:

};

}// END namespace Ui


#endif