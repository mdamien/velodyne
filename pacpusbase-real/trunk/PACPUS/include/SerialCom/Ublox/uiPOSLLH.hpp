#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiPOSLLH_H
#define _uiPOSLLH_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_POSLLH_DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_NAV_POSLLH.hpp"

namespace Ui {

class uiPOSLLH : public SerialCOM_Msg_Ui, protected POSLLH_DisplayForm
{
	Q_OBJECT

public: 

	void setupUi(QWidget *parent);

public slots:

	void display(SerialCOM_Msg *pMsg);

	void display(Ublox::structNAV_POSLLH data);

protected:

};

}// END namespace Ui


#endif