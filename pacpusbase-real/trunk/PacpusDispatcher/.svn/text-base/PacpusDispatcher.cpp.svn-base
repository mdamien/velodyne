/*********************************************************************
//  created:    2012/03/01 - 14:06
//  filename:   PacpusDispatcher.cpp
//
//  author:     Pierre Hudelaine
//              Copyright Heudiasyc UMR UTC/CNRS 7253
// 
//  version:    $Id: $
//
//  purpose:    Receive and decode data from PacpusSocket
//
*********************************************************************/

#include "PacpusDispatcher.h"
#include <string>

typedef struct
{
	double lat_borne;
	double lon_borne;
    double lat_entree_virage;
    double lon_entree_virage;
    double lat_point_corde_virage;
    double lon_point_corde_virage;
    double lat_sortie_virage;
    double lon_sortie_virage;
    float  ro;
    float  deltaRo;
}sedvacDataBorne;

#define NB_field_sedvac_data 10

using namespace std;
using namespace pacpus;

static const string kPacpusDispatcherMemoryName = "pacpusDispatcher";

//////////////////////////////////////////////////////////////////////////
// Construct the factory
//////////////////////////////////////////////////////////////////////////
static ComponentFactory <PacpusDispatcher> sFactory("PacpusDispatcher");

//////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////
PacpusDispatcher::PacpusDispatcher(QString name)
    : ComponentBase(name)
{
    ComponentManager * mgr = ComponentManager::getInstance();
    qDebug() << "dll : " << mgr;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////
PacpusDispatcher::~PacpusDispatcher()
{
}



//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to start the component
//////////////////////////////////////////////////////////////////////////
void PacpusDispatcher::startActivity()
{
    std::cout << "PacpusDispatcher startActivity() called !" << std::endl;
   
    if ( pacpusSocket_ ) 
    {
		connect( pacpusSocket_, SIGNAL( newDatagram( QByteArray ) ), this, SLOT( receiveData( QByteArray ) ) );
		connect( pacpusSocket_, SIGNAL( newQString( QString ) ), this, SLOT( receiveData( QString ) ) );
    }
       
	shmem_ = new ShMem(kPacpusDispatcherMemoryName.c_str(), sizeof(sedvacDataBorne));

    THREAD_ALIVE = true;
    start();
}



//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to stop the component
//////////////////////////////////////////////////////////////////////////
void PacpusDispatcher::stopActivity()
{
    std::cout << "PacpusDispatcher stopActivity() called !" << std::endl;

	delete shmem_;
    THREAD_ALIVE = false;
}



//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
void PacpusDispatcher::run()
{
    while ( THREAD_ALIVE )
    {
       
    }
}



//////////////////////////////////////////////////////////////////////////
// Receive and decode the data from PacpusSocket
//////////////////////////////////////////////////////////////////////////
void PacpusDispatcher::receiveData( QByteArray datagram )
{
    QDataStream streamIn( &datagram, QIODevice::ReadOnly );
    QString beginingQString = "", endingQString = "", typeData = "";
    int i = 0;

    streamIn >> beginingQString;   

    if ( beginingQString != NULL )
    {
	while ( beginingQString.at( i ) != 'T' )
	    i++;
	
	i = i + 2;

	while ( beginingQString.at( i ) != '!' )
	    typeData.append( beginingQString.at( i++ ) );
	
	if ( typeData == "wheelSpeed" )
	{
	    TimestampedStructWheelSpeed wheelSpeed;
	  
	    streamIn.readRawData( ( char * )( &wheelSpeed ), sizeof( wheelSpeed ) );
	    streamIn >> endingQString;
	}
	else if ( typeData == "VG700" )
	{
	    VG700dataframe VG700;
	  
	    streamIn.readRawData( ( char * )( &VG700 ), sizeof( VG700dataframe ) );
	    streamIn >> endingQString;
	}
	else if ( typeData == "speed" )
	{
	    TimestampedStructVehicleSpeed odometry;
	    
	    streamIn.readRawData ( ( char * )( &odometry ), sizeof ( TimestampedStructVehicleSpeed ) ); 
	    streamIn >> endingQString;
	}
	else if ( typeData == "steeringWheel" )
	{
	    TimestampedStructSteeringWheel steeringWheel;
	    
	    streamIn.readRawData ( ( char * )( &steeringWheel ), sizeof ( TimestampedStructSteeringWheel ) ); 
	    streamIn >> endingQString;
	}
	else if ( typeData == "cube" )
	{
	    StructureCubeRawData cube;
	    
	    streamIn.readRawData ( ( char * )( &cube ), sizeof ( StructureCubeRawData ) ); 
	    streamIn >> endingQString;	  
	}
	else 
	    qDebug() << typeData << " is an unknonwn type";
    }
}



//////////////////////////////////////////////////////////////////////////
// Receive and decode the data from PacpusSocket
//////////////////////////////////////////////////////////////////////////
void PacpusDispatcher::receiveData( QString string )
{
    int i = 0;

	if ( string.isEmpty() == false )
    {
        QStringList listString = string.split('\\');

        foreach( QString stringData, listString )
		{
            if ( stringData.startsWith( "!f~t!T~speed!d~") )
            {
				qDebug() << "TODO: complete the reception of speed";
			}
            else if ( stringData.startsWith( "!f~t!T~steeringWheel!d~" ) )
            {
				qDebug() << "TODO: complete the reception of steeringWheel";
            }
            else if ( stringData.startsWith( "!f~t!T~sedvac!d~" ) )
            {
				QString sedvacData;
                sedvacDataBorne recu;

                sedvacData = stringData.mid( 16, stringData.size() - 17 );

                QStringList sedvacListString = sedvacData.split(',');

				if ( sedvacListString.size() == NB_field_sedvac_data )
				{
					recu.lat_borne = sedvacListString.at(0).toDouble();
					recu.lon_borne = sedvacListString.at(1).toDouble();

					recu.lat_entree_virage = sedvacListString.at(2).toDouble();
					recu.lon_entree_virage = sedvacListString.at(3).toDouble();

					recu.lat_point_corde_virage = sedvacListString.at(4).toDouble();
					recu.lon_point_corde_virage = sedvacListString.at(5).toDouble();

					recu.lat_sortie_virage = sedvacListString.at(6).toDouble();
					recu.lon_sortie_virage = sedvacListString.at(7).toDouble();

					recu.ro = sedvacListString.at(8).toFloat();
					recu.deltaRo = sedvacListString.at(9).toFloat();

					shmem_->write(&recu, sizeof(recu));
					
					/*
					qDebug() << "Borne           : " << QString::number(recu.lat_borne, 'f', 15)              << ", " << QString::number(recu.lon_borne, 'f', 15);
					qDebug() << "Entree          : " << QString::number(recu.lat_entree_virage, 'f', 15)      << ", " << QString::number(recu.lon_entree_virage, 'f', 15);
					qDebug() << "Point de corede : " << QString::number(recu.lat_point_corde_virage, 'f', 15) << ", " << QString::number(recu.lon_point_corde_virage, 'f', 15);
					qDebug() << "Sortie          : " << QString::number(recu.lat_sortie_virage, 'f', 15)      << ", " << QString::number(recu.lon_sortie_virage, 'f', 15);
					qDebug() << "Ro              : " << recu.ro << ", " << recu.deltaRo;
					//*/
				}
				else
				{
					qDebug() << "Not enough or to much parameters, has to be 8 positions, ro and deltaRo, see documentation for more information";
				}
            }
            else
				qDebug() << "Unknonwn frame";
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to pass the XML parameters to the 
// component 
//////////////////////////////////////////////////////////////////////////
ComponentBase::COMPONENT_CONFIGURATION PacpusDispatcher::configureComponent( XmlComponentConfig config )
{    
    QString pacpusSocket = config.getProperty( "socketComponent" );
    ComponentManager * mgr = ComponentManager::getInstance();
    pacpusSocket_ = dynamic_cast<PacpusSocket *>(mgr->getComponent(pacpusSocket));
    if ( !pacpusSocket_ ) {
	    qWarning() << "Failed to get component " << pacpusSocket;
	    return ComponentBase::NOT_CONFIGURED;
    }
    return ComponentBase::CONFIGURED_OK;
}
