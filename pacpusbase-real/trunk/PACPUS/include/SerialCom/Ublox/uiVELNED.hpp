#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiVELNED_H
#define _uiVELNED_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_VELNED_DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_NAV_VELNED.hpp"

namespace Ui {

class uiVELNED : public SerialCOM_Msg_Ui, protected VELNED_DisplayForm
{
	Q_OBJECT

public: 

	void setupUi(QWidget *parent);

public slots:

	void display(SerialCOM_Msg *pMsg);

	void display(Ublox::structNAV_VELNED data);

protected:

};

}// END namespace Ui


#endif