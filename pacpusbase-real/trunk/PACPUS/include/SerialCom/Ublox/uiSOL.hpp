#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiSOL_H
#define _uiSOL_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_SOL_DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_NAV_SOL.hpp"

namespace Ui {

class uiSOL : public SerialCOM_Msg_Ui, protected SOL_DisplayForm
{
	Q_OBJECT

public: 

	void setupUi(QWidget *parent);

public slots:

	void display(SerialCOM_Msg *pMsg);

	void display(Ublox::structNAV_SOL data);

protected:

};

}// END namespace Ui


#endif