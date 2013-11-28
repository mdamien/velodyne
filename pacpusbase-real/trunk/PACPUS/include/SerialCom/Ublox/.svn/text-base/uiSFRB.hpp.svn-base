#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _uiSFRB_H
#define _uiSFRB_H


#include "qstring.h"
#include "ui_SFRB_DisplayForm.h"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Msg_RXM_SFRB.hpp"
#include <QTextEdit>
#include <QScrollBar>

namespace Ui {

class uiSFRB : public SerialCOM_Msg_Ui, protected SFRB_DisplayForm
{
	Q_OBJECT

public: 

	void setupUi(QWidget *parent);

public slots:

	void display(SerialCOM_Msg *pMsg);

	void display(Ublox::structRXM_SFRB data);

protected:

	QString texte;

};

}// END namespace Ui


#endif