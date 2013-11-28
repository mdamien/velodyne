#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiPOSUTM_H
#define _uiPOSUTM_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_POSUTM_DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_NAV_POSUTM.hpp"

namespace Ui {

class uiPOSUTM : public SerialCOM_Msg_Ui, protected POSUTM_DisplayForm
{
	Q_OBJECT

public: 

	void setupUi(QWidget *parent);

public slots:

	void display(SerialCOM_Msg *pMsg);

	void display(Ublox::structNAV_POSUTM data);

protected:

};

}// END namespace Ui


#endif