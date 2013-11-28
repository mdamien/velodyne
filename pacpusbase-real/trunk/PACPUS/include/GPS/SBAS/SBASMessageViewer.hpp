#ifndef SBASMESSAGEVIEWER_H
#define SBASMESSAGEVIEWER_H

#include <QtGui/QMainWindow>
#include "ui_SBASMessageViewer.h"
#include "uiMT1.hpp"
#include "uiMT2to5.hpp"
#include "uiMT6.hpp"
#include "uiMT7.hpp"
#include "uiMT18.hpp"
#include "uiMT24.hpp"
#include "uiMT25.hpp"
#include "uiMT26.hpp"
#include "SerialCOM_Protocol_SBAS.hpp"
#include "SerialCOM_Msg_MT1.hpp"
#include "SerialCOM_Msg_MT2to5.hpp"
#include "SerialCOM_Msg_MT6.hpp"
#include "SerialCOM_Msg_MT7.hpp"
#include "SerialCOM_Msg_MT18.hpp"
#include "SerialCOM_Msg_MT24.hpp"
#include "SerialCOM_Msg_MT25.hpp"
#include "SerialCOM_Msg_MT26.hpp"

class SBASMessageViewer : public QMainWindow
{
	Q_OBJECT

public:
	SBASMessageViewer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SBASMessageViewer();

private slots:

	void decodeMsg();
	void changeMessageDisplay();


private:
	Ui::SBASMessageViewerClass ui;

	Ui::uiMT1 *pMT1Form;
	Ui::uiMT2to5 *pMT2Form;
	Ui::uiMT2to5 *pMT3Form;
	Ui::uiMT2to5 *pMT4Form;
	Ui::uiMT2to5 *pMT5Form;
	Ui::uiMT6 *pMT6Form;
	Ui::uiMT7 *pMT7Form;
	Ui::uiMT18 *pMT18Form;
	Ui::uiMT24 *pMT24Form;
	Ui::uiMT25 *pMT25Form;
	Ui::uiMT26 *pMT26Form;

	SBAS::SerialCOM_Protocol_SBAS *pSBASProtocol;

	SBAS::SerialCOM_Msg_MT1 *pMT1Msg;
	SBAS::SerialCOM_Msg_MT2to5 *pMT2to5Msg;
	SBAS::SerialCOM_Msg_MT6 *pMT6Msg;
	SBAS::SerialCOM_Msg_MT7 *pMT7Msg;
	SBAS::SerialCOM_Msg_MT18 *pMT18Msg;
	SBAS::SerialCOM_Msg_MT24 *pMT24Msg;
	SBAS::SerialCOM_Msg_MT25 *pMT25Msg;
	SBAS::SerialCOM_Msg_MT26 *pMT26Msg;

	QAction *decodeAct;

	unsigned char decodedDataBlock[32];

	void setUiMT();
	void createActions();
};

#endif // SBASMESSAGEVIEWER_H
