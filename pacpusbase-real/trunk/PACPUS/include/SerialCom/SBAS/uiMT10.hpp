#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiMT10_H
#define _uiMT10_H


#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "qstring.h"
#include "ui_MT10DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_MT10.hpp"

namespace Ui {

class uiMT10 : public SerialCOM_Msg_Ui, protected MT10DisplayForm
{
	Q_OBJECT

public: 

	void setupUi(QWidget *parent);

public slots:

	void display(SerialCOM_Msg *pMsg);

	void display(SBAS::structDegradationParameters data);

protected:

};

}// END namespace Ui


#endif