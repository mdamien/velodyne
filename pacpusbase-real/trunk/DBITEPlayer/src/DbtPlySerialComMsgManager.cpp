#include <QApplication>
#include "DbitePlayer/DbtPlySerialComMsgManager.h"


static ComponentFactory<DbtPlySerialComMsgManager>* factory = new ComponentFactory<DbtPlySerialComMsgManager>("DbtPlySerialComMsgManager");



DbtPlySerialComMsgManager::DbtPlySerialComMsgManager(QString name):DbtPlyFileManager (name)
{
	//ptrser = NULL;
	ptr= ComponentManager::create();//added

	SerialComUi = new Ui::SerialComMsgViewerClass();
	mainWidget = new QWidget();

	ui_ = true;
}


DbtPlySerialComMsgManager::~DbtPlySerialComMsgManager()
{
	mainWidget->close();
	msgMap.clear();
	delete SerialComUi;
	delete mainWidget;
}


void DbtPlySerialComMsgManager::processData(road_time_t t, road_timerange_t tr , void *buf)
{
	if (buf != NULL)
	{
		// look at the dbt index in file manager and get the identifier of dbt structure
		int id = dbt_[dbtIndex_].pfile->h.Type;

		//Search which SerialCOM_Msg is concerned by this id
		itMsgMap = this->msgMap.find(id);

		//Copy the data form the Dbt file to the corresponding object
		if (itMsgMap!= msgMap.end())
			if (itMsgMap->second.pScMsg!=NULL)
				if(itMsgMap->second.pScMsg->fromStructFile(buf))
					//return;
					//display the results in their form
					if(itMsgMap->second.pScMsgUi!=NULL)
						//itMsgMap->second.pScMsgUi->display(itMsgMap->second.pScMsg);
						display(itMsgMap->second.pScMsg);
						//itMsgMap->second.display();

	}//END if (buf != NULL)

}


ComponentBase::COMPONENT_CONFIGURATION DbtPlySerialComMsgManager::configureComponent(XmlComponentConfig config)
{
  DbtPlyFileManager::configureComponent(config);

  //configure the UI, regarding msg added in the msgMap
  //for each message in the msgMap

  return ComponentBase::CONFIGURED_OK;
}

void DbtPlySerialComMsgManager::configureUI()
{
	for(itMsgMap = msgMap.begin(); itMsgMap != msgMap.end(); itMsgMap++)
	{
		if(itMsgMap->second.pScMsgUi != NULL)
		{
			//If there is no subgroup
			if(itMsgMap->second.subGroup.compare("")==0)
				//simply add a branch at the main tree
				itMsgMap->second.pTreeItem = new QTreeWidgetItem(SerialComUi->messageTreeWidget);
			else
			{
				//Find if the subBranch already exist or not
				QList<QTreeWidgetItem *> MainItemList = SerialComUi->messageTreeWidget->findItems(itMsgMap->second.subGroup,Qt::MatchExactly);
				if (MainItemList.count()==1)
				{
					//if exist attach
					itMsgMap->second.pTreeItem = new QTreeWidgetItem(*MainItemList.begin());
				}
				else
				{
					//create an element and attach
					QTreeWidgetItem *newGroup = new QTreeWidgetItem(SerialComUi->messageTreeWidget);
					newGroup->setText(0,itMsgMap->second.subGroup);
					itMsgMap->second.pTreeItem = new QTreeWidgetItem(newGroup);
				}
			}
			itMsgMap->second.pTreeItem->setText(0,QString(itMsgMap->second.pScMsg->getName().c_str()));

			//add a stackedWidget and insert the good form
			itMsgMap->second.pStackedWidget = new QWidget();
			SerialComUi->mainStackedWidget->addWidget(itMsgMap->second.pStackedWidget);
			itMsgMap->second.pScMsgUi->setupUi(itMsgMap->second.pStackedWidget);

			qRegisterMetaType<SerialCOM_Msg*>("SerialCOM_Msg*");
			//connect(&itMsgMap->second,SIGNAL(display(SerialCOM_Msg*)),itMsgMap->second.pScMsgUi,SLOT(display(SerialCOM_Msg*)));
			connect(this,SIGNAL(display(SerialCOM_Msg*)),itMsgMap->second.pScMsgUi,SLOT(display(SerialCOM_Msg*)));
		}
	}
	//connect the slots
	connect(SerialComUi->messageTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(changeMessageDisplay()));
}

void DbtPlySerialComMsgManager::displayUI()
{
	SerialComUi->setupUi(mainWidget);
	configureUI();

	mainWidget->setWindowTitle(componentName);
	mainWidget->show();
}

void DbtPlySerialComMsgManager::changeMessageDisplay()
{
	//Extract the item clicked
	QTreeWidgetItem *pCurrentItem =	SerialComUi->messageTreeWidget->currentItem();

	//Search the corresponding stackedWidget and display it
	for(itMsgMap = msgMap.begin(); itMsgMap != msgMap.end(); itMsgMap++)
	{
		if (itMsgMap->second.pTreeItem == pCurrentItem)
		{
			SerialComUi->mainStackedWidget->setCurrentWidget(itMsgMap->second.pStackedWidget);
			return;
		}
	}
}


bool DbtPlySerialComMsgManager::addMsg(msgContainer msg)
{
	//if a container has a valid pointer on a SerialCOM_iMsg and a SerialCOM_Msg_Ui
	//if ((msg.pScMsg != NULL) && (msg.pScMsgUi!=NULL))
	if (msg.pScMsg != NULL)
	{
		//and the DbtType of the message is defined
		if (msg.pScMsg->getDbtType() == FILE_DBT_UNKNOWN)
			return false;

		//add it to the msgMap if no others message handle the same DbtType
		pair<std::map<int,msgContainer>::iterator,bool> ret;
		ret = msgMap.insert(std::pair<int,msgContainer>(msg.pScMsg->getDbtType(),msg));
		return ret.second;
	}
	else
		return false;
}