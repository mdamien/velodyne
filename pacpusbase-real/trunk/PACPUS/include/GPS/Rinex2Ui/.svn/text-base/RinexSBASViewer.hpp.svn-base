#pragma warning( once : 4290 )
#pragma warning( once : 4274 )
#pragma warning( once : 4996 )

#ifndef SBASMESSAGEVIEWER_H
#define SBASMESSAGEVIEWER_H

#include <QtGui/QMainWindow>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Msg_Ui.hpp"
#include "SerialCOM_Protocol_SBAS.hpp"
#include "SerialCOM_Msg_MT1.hpp"
#include "SerialCOM_Msg_MT2to5.hpp"
#include "SerialCOM_Msg_MT6.hpp"
#include "SerialCOM_Msg_MT7.hpp"
#include "SerialCOM_Msg_MT10.hpp"
#include "SerialCOM_Msg_MT18.hpp"
#include "SerialCOM_Msg_MT24.hpp"
#include "SerialCOM_Msg_MT25.hpp"
#include "SerialCOM_Msg_MT26.hpp"

#include "ui_serialCOM_Msg.h"
#include "ui_ublox.h"
#include "uiGnssSatTypeValue.hpp"
#include "uiGpsEphemerisStore.hpp"
#include "uiMT1.hpp"
#include "uiMT2to5.hpp"
#include "uiMT6.hpp"
#include "uiMT7.hpp"
#include "uiMT10.hpp"
#include "uiMT18.hpp"
#include "uiMT24.hpp"
#include "uiMT25.hpp"
#include "uiMT26.hpp"
#include "uiIonoGrid.hpp"
#include "uiIonoCompute.hpp"
#include "uiFastCorrections.hpp"
#include "uiLongTermCorrections.hpp"

#include "GPSTK_Nav.hpp"
#include "GPSTK_Obs.hpp"
#include "basicGPSSolver.hpp"

#include "stdlib.h"
#include <vector>



/*! \class msgContainer
 *	\brief Structure containing pointer toward a SerialCOM_Msg and its GUI
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date august 2008
 *	\bug None
 *	\warning None
 *  
 */

class msgContainer //: public QObject
{
	//Q_OBJECT
public:

	/*!\brief Pointer on a SerialCOM_Msg*/
	SerialCOM_Msg *pScMsg;

	/*!\brief Pointer on a UI form associated with the SerialCOM_Msg object 
	 *  pointed by pScMsg*/
	SerialCOM_Msg_Ui *pScMsgUi;

	/*!\brief Pointer on the item placed in the tree of the
	 * DbtPlySerialComMsgManager displayer. This item contain the name of 
	 *  message pointed by pScMsg*/
	QTreeWidgetItem *pTreeItem;

	/*!\brief Pointer on the widget containing the UI form pointed by
	 * pScMsgUi*/
	QWidget *pStackedWidget;

	/*!\brief Name of the subgroup in order to organize in a hierarchie 
	 * the main tree of the UI*/
	QString subGroup;

	/*!\brief Constructor. Intiialize all the pointer to NULL*/
	msgContainer()
	{
		pScMsg = NULL;
		pScMsgUi = NULL;
		pTreeItem = NULL;
		pStackedWidget = NULL;
		subGroup = QString("");
	};

	/*!\brief Constructor. Copy the input pointer. Others are set to NULL*/
	msgContainer(SerialCOM_Msg *pScMsg, SerialCOM_Msg_Ui *pScMsgUi, QString subGroup = QString(""))
	{
		this->pScMsg=pScMsg;
		this->pScMsgUi=pScMsgUi;
		pTreeItem = NULL;
		pStackedWidget = NULL;
		this->subGroup = subGroup;
	};

	/*!\brief Delete the object pointed by the pScMsg and pScMsgUi pointers*/
	//BUG possible, devrait être dans le destructeur parce que là cette fonction n'est jamais appelée...
	void suppr()
	{
		if (pScMsg!=NULL) delete pScMsg;
		if (pScMsgUi!=NULL) delete pScMsgUi;
	};

};


/*! \class RinexSBASViewer
 *	\brief Little test for playing SerialComMsg with DBytePlayer
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date august 2008
 *	\bug None
 *	\warning None
 */


class RinexSBASViewer : public QMainWindow
{
	Q_OBJECT

public:
	RinexSBASViewer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~RinexSBASViewer();

	GPSTK_Obs *pObs;

	GPSTK_Nav *pNav;

	void processSBAS(std::vector<unsigned char> &SBASbuffer, gpstk::DayTime &SBAStime);

	void processObs(gpstk::gnssSatTypeValue &preparedRAW, gpstk::Vector<double> &curPosSolution, gpstk::RinexObsData &rData);

protected:
	
	Ui::uiIonoGrid *ionoGridForm;
	Ui::uiIonoCompute * ionoComputeForm;
	Ui::uiFastCorrections * fastCorrectionsForm;
	Ui::uiLongTermCorrections * longTermCorrectionsForm;
	Ui::ubloxViewerClass *ubloxUi;
	Ui::uiGnssSatTypeValue *uiGnssStruct;
	Ui::uiGpsEphemerisStore *uiEphStore;	
	QTreeWidgetItem *pIonoGridTreeItem;
	QTreeWidgetItem *pIonoComputeTreeItem;
	QTreeWidgetItem *pFastCorrectionsTreeItem;
	QTreeWidgetItem *pLongTermCorrectionsTreeItem;
	QTreeWidgetItem *pGnssTreeItem;
	QTreeWidgetItem *pEphStoreTreeItem;
	QWidget *pGnssStackedWidget;
	QWidget *pEphStoreStackedWidget;
	QWidget *pIonoGridStackedWidget;
	QWidget *pIonoComputeStackedWidget;
	QWidget *pFastCorrectionsStackedWidget;
	QWidget *pLongTermCorrectionsStackedWidget;

	SBAS::SerialCOM_Protocol_SBAS *pSBASprotocol;
	SBAS::SerialCOM_Msg_MT1 *pMT1;
	SBAS::SerialCOM_Msg_MT2to5 *pMT2, *pMT3, *pMT4, *pMT5;
	SBAS::SerialCOM_Msg_MT6 *pMT6;
	SBAS::SerialCOM_Msg_MT7 *pMT7;
	SBAS::SerialCOM_Msg_MT10 *pMT10;
	SBAS::SerialCOM_Msg_MT18 *pMT18;
	SBAS::SerialCOM_Msg_MT24 *pMT24;
	SBAS::SerialCOM_Msg_MT25 *pMT25;
	SBAS::SerialCOM_Msg_MT26 *pMT26;

	
	gpstk::DayTime start_road_time_t;
	gpstk::DayTime lastRAWtime;

	gpstk::Position lastPos;
	
	bool use120;
	bool use124;
	bool use126;
	bool firstFix;

	int nbEph;

	basicGPSSolver *pBasicGPSSolver;

	gpstk::Vector<double> curSolution;

	/*!\brief Contain the list of messages to handle in the Manager.*/
	/*! The key is the DbtType of the message, and the mapped value is a 
	 *  msgContainer object pointing on a message object and its Ui*/
	std::map<int,msgContainer> msgMap;
  
	/*!\brief iterator on the msgMap*/
	std::map<int,msgContainer>::iterator itMsgMap;

	/*!\brief Main User Interface of the displayer.*/
	/*! Contain a tree for listing the messages and selecting their form, 
	 *  and a satckedwidget*/
	Ui::SerialComMsgViewerClass *SerialComUi;

	/*!\brief Main Widget*/
	QWidget *mainWidget;

	/*!\brief Add a new message to the msgMap.*/
	/* Return 0 if a container as already been added for this DbtType, 1 otherwise*/
	bool addMsg(msgContainer msg);
	
	void configureUI();

protected slots:

	void changeMessageDisplay();

	void changeSBASParameters(int state);
	
	void changeFilterParameters(double value);

signals:

	void displayGnssStruct(gpstk::gnssSatTypeValue gnssData);

	void displayEphStore(const gpstk::GPSEphemerisStore *gnssData);

	void display(SerialCOM_Msg *pMsg);

};


#endif
