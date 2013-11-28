#ifndef _DBTPLYSERIALCOMMSGMANAGER_H_
#define _DBTPLYSERIALCOMMSGMANAGER_H_

#include "DbitePlayer/DbtPlyFileManager.h"
#include <QApplication>
#include <QObject>
#include <QVector>
#include <QMetaType>

#include "structure/structure_gps.h"
#include "kernel/ComponentManager.h"//moved from .cpp

#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Msg_Ui.hpp"
#include "ui_serialCOM_Msg.h"


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
/*
	void display()
	{
		display(pScMsg);
	};

signals:
	void display(SerialCOM_Msg *pMsg);*/
};


/*! \class DbtPlySerialComMsgManager
 *	\brief Read DByte files whose messages follow the SerialCOM framework
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date august 2008
 *	\bug None
 *	\warning None
 *	
 *  SerialCOM library provides a framework for decoding messages from data streams, 
 *  recording it as DByte files and some other useful functions. The SerialCOM_Msg_Ui 
 *  class adds an abstract class providing a link between SerialCOM_Msg herited classes 
 *  and their Qt4 form associated to data display.\n
 *  DbtPlySerialComMsgManager use the previous functionnalities of the SerialCOM library 
 *  in order to provide an efficient and easy to use data display to DByte files.
 */

class DbtPlySerialComMsgManager : public DbtPlyFileManager
{
	Q_OBJECT

public:

	/*!\brief Constructor. Create the component manager, the mainUI and the mainWidget*/
	DbtPlySerialComMsgManager(QString name);

	/*!\brief Destructor. Clear the msgMap, and destror the mainUI and the mainWidget*/
	~DbtPlySerialComMsgManager();

	/*!\brief virtual function herited from DbtPlyFileManager class. Configure the 
	 * the GUI*/
	/*! According to the messages mapped in the msgMap, their name is added in the 
	 *  and a new widget is added to the stackedwidget on which the dedicated form
	 *  is applied*/
	ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

	virtual void configureUI();


protected:

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
	
	/*!\brief virtual function herited from the DbtPlyFileManager class*/
	void processData(road_time_t t, road_timerange_t tr , void *buf);
  
	/*!\brief virtual function herited from DbtPlyFileManager class. Display the GUI*/
	void displayUI();

	/*!\brief Add a new message to the msgMap.*/
	/* Return 0 if a container as already been added for this DbtType, 1 otherwise*/
	bool addMsg(msgContainer msg);
  
  ComponentManager* ptr; //added

protected slots:

	/*!\brief Function called when a click is observed on the name of a message
	 * in the tree*/
	virtual void changeMessageDisplay();

signals:
	void display(SerialCOM_Msg *pMsg);

};


#endif
