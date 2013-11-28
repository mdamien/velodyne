/********************************************************************
//  created:    2012/03/01 - 14:06
//  filename:   PacpusDataCollector.cpp
//
//  author:     Pierre Hudelaine
//              Copyright Heudiasyc UMR UTC/CNRS 7253
// 
//  version:    $Id: $
//
//  purpose:    Collect and format the Pacpus data to send with PacpusSocket
//
*********************************************************************/

#include "PacpusDataCollector.h"

#include "Pacpus/PacpusTools/ShMem.h"

using namespace pacpus;

//////////////////////////////////////////////////////////////////////////
// Constructs the factory
//////////////////////////////////////////////////////////////////////////

static ComponentFactory<PacpusDataCollector> sFactory("PacpusDataCollector");

//////////////////////////////////////////////////////////////////////////
// Operator overload
//////////////////////////////////////////////////////////////////////////
QDataStream &operator<<(QDataStream &s, const TimestampedWgs84Position &d)
{
    s << d.position.lat << d.position.lon << d.position.altitude << d.position.sigma_lat << d.position.sigma_lon << d.position.sigma_alt << d.position.gps_week << d.position.gps_time << d.position.quality << d.position.nb_sats << (quint64)(d.time);
    return s;
}

QDataStream & operator>> (QDataStream& s, TimestampedWgs84Position& d)
{
    quint64 tmp;
    s >> d.position.lat >> d.position.lon >> d.position.altitude >> d.position.sigma_lat >> d.position.sigma_lon >> d.position.sigma_alt >> d.position.gps_week >> d.position.gps_time >> d.position.quality >> d.position.nb_sats >> tmp;
    d.time = tmp;
    return s;
}

//////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////
PacpusDataCollector::PacpusDataCollector(QString name)
    : ComponentBase(name)
{
    ComponentManager * mgr = ComponentManager::getInstance();
    qDebug() << "dll : " << mgr;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////
PacpusDataCollector::~PacpusDataCollector()
{
}



//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to start the component
//////////////////////////////////////////////////////////////////////////
void PacpusDataCollector::startActivity()
{
    std::cout << "PacpusDataCollector startActivity() called !" << std::endl;
    
    if ( odometryActive_ )
    {
		char shmemName[40];
		sprintf( shmemName, "CARMEN_CAN_%d",CARMEN_CAN_ODOMETRY );
		odometryData_ = new InterfaceDataCollector<TimestampedStructVehicleSpeed>( shmemName );
    }
    
    if ( steeringWheelActive_ )
    {
		char shmemName[40];
		sprintf( shmemName, "CARMEN_CAN_%d",CARMEN_CAN_STEERINGWHEEL );
		steeringWheelData_ = new InterfaceDataCollector<TimestampedStructSteeringWheel>( shmemName );
    }
    
    if ( VG700Active_ )
    {
		char shmemName[40];
		sprintf( shmemName, "CROSSBOW_%d", CROSSBOW_VG700 );
		VG700Data_ = new InterfaceDataCollector<VG700dataframe>( shmemName );
    }
    
    if ( wheelSpeedActive_ )
    {
		char shmemName[40];
		sprintf( shmemName, "CARMEN_CAN_%d", CARMEN_CAN_WHEELSPEED );
		wheelSpeedData_ = new InterfaceDataCollector<TimestampedStructWheelSpeed>( shmemName );
    }
    
    if ( cubeActive_ )
    {
		char shmemName[40];
		sprintf( shmemName, "DYNA_%d", DYNA_CUBE_RAWDATA );
		cubeData_ = new InterfaceDataCollector<StructureCubeRawData>( shmemName );
    }
    
    // TODO : 
    //if (yourDataActive_)
    //{
    //  char shmemName[40];
    //  sprintf(shmemName,"CARMEN_CAN_%d",CARMEN_CAN_YOURDATA);
    //  yourDataData_ = new InterfaceDataCollector<YourDataType>(shmemName);
    //}
    
    THREAD_ALIVE = true;
    start();
}



//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to stop the component
//////////////////////////////////////////////////////////////////////////
void PacpusDataCollector::stopActivity()
{
    std::cout << "PacpusDataCollector stopActivity() called !" << std::endl;

    THREAD_ALIVE = false;
}



//////////////////////////////////////////////////////////////////////////
// Start to collect the data from the car
//////////////////////////////////////////////////////////////////////////
void PacpusDataCollector::run()
{
    QString convert, msg;
    QBuffer buffer;
     
    // read listened shared memories
    while ( THREAD_ALIVE )
    {
        // ***************** NOTE
        // Pour utiliser le code sous Windows, remplacer ce qui suit par WaitForMultipleObjects
        // Pour linux trouver une solution qui permet d'avoir le même comportement que WaitForMultipleObjects 
        // Limitation : le code actuel enverra les données sur le réseau à la fréquence du capteur le plus lent
        // *****************
        
//NOTE : La solution sur Windows est la suivante (code à adapter et à recompiler)        
//         //////////////////creat the handle /////////////////
// 	HANDLE evtList[4];
// 	evtList[0] = shMem_[CARMEN_CAN_WHEELSPEED]->getEventIdentifier();
// 	evtList[1] = shMem_[CARMEN_CAN_STEERINGWHEEL]->getEventIdentifier();
// 	evtList[2] = shMem_[CROSSBOW_VG700]->getEventIdentifier();
// 	evtList[3] = shMem_[DYNA_CUBE_RAWDATA]->getEventIdentifier();
// 
// 
// 	while (THREAD_ALIVE)
// 	{
// 		//wait the incoming of new data
// 		int result = WaitForMultipleObjects(4,evtList,false, 1000);
// 		switch (result)
// 		{
// 		case 0:
// 			memcpy(&wheelspeed_,shMem_[CARMEN_CAN_WHEELSPEED]->read(),sizeof(TimestampedStructWheelSpeed));
// 			break;
// 
// 		case 1:
// 			memcpy(&steeringWheel_,shMem_[CARMEN_CAN_STEERINGWHEEL]->read(),sizeof(TimestampedStructSteeringWheel));
// 			break;
// 
// 		case 2:
// 			memcpy(&VG700data_,shMem_[CROSSBOW_VG700]->read(),sizeof(VG700dataframe));
// 			break;
// 		case 3:
// 			memcpy(&cube_,shMem_[DYNA_CUBE_RAWDATA]->read(),sizeof(StructureCubeRawData));
// 			break;
// 
// 			/*case 4:
// 			memcpy(&roadyn_,shMem_[DYNA_ROADYN]->read(),sizeof(StructureRoadynamics));
// 			break;*/
// 
// 		case WAIT_TIMEOUT:
// 			//printf("/s - timeout, no data\n");
// 			break;
// 
// 		case WAIT_FAILED:
// 			//printf("%s -wait failed, no data\n");
// 			break;
// 
// 		default:
// 			THREAD_ALIVE = false;
// 			break;
// 		}
        
		// Get and format the odometry data
		if ( odometryActive_ )
		{	  
			TimestampedStructVehicleSpeed odometry_ = odometryData_->readData();
			msg += buildOrAddMsg( "t", "speed", convert.setNum( odometry_.time ), convert.setNum( odometry_.d.vehicleSpeed ) );
	    
			buildAndSendBinMsg( "speed", convert.setNum( odometry_.time ), ( char * )( &odometry_ ), sizeof( TimestampedStructVehicleSpeed ) ); 
		}
	
		// Get and format the steeringWheel data
		if ( steeringWheelActive_ )
		{	  
			TimestampedStructSteeringWheel steeringWheel_ = steeringWheelData_->readData();
			msg += buildOrAddMsg( "t", "steeringWheel", convert.setNum( steeringWheel_.time ), convert.setNum( steeringWheel_.d.angle ) );
	    
			buildAndSendBinMsg( "steeringWheel", convert.setNum( steeringWheel_.time), ( char * )( &steeringWheel_ ), sizeof( TimestampedStructSteeringWheel ) );	    
		}
	
		if ( VG700Active_ )
		{
			VG700dataframe VG700_ = VG700Data_->readData();	    
			buildAndSendBinMsg( "VG700", convert.setNum( VG700_.message_time ), ( char * )( &VG700_ ), sizeof( VG700dataframe ) );
		}
	
		if ( wheelSpeedActive_ )
		{	    	    
			TimestampedStructWheelSpeed wheelSpeed_ = wheelSpeedData_->readData();
			buildAndSendBinMsg( "wheelSpeed", convert.setNum( wheelSpeed_.time), ( char * )( &wheelSpeed_ ), sizeof( TimestampedStructWheelSpeed ) );
		}	
	
		if ( cubeActive_ )
		{
			StructureCubeRawData cube_ = cubeData_->readData();
			buildAndSendBinMsg( "cube", convert.setNum( cube_.time), ( char * )( &cube_ ), sizeof( StructureCubeRawData ) );
		}

		//*/
	
		// TODO : 
		// Get and format the YourData data
		//if ( YourDataActive_ ) 
		//{
		//  TypeOfYourData YourData_ = YourDataData_.readData();
		//  msg_ = buildOrAddMsg( "YourData", convert.setNum ( YourData.d. ), convert.setNum ( YourData_.time ), msg_ );
		//}

		sendMsg( msg );	
		msg = beginingMsg_;
    }
}



//////////////////////////////////////////////////////////////////////////
// Construct the message before sending
//////////////////////////////////////////////////////////////////////////
QString PacpusDataCollector::buildOrAddMsg( QString f, QString T, QString t, QString d, QString c )
{
    QString msg;
    
    if ( f == "b" )
		msg = headerMsgBin_;
    else
		msg = headerMsgText_;
    
		msg +=  T + charDelimitorPacpus_ + "t" + charEqual_ + t + charDelimitorPacpus_ + "d" + charEqual_ ;
    
    if ( !d.isNull() )
		msg += d + charDelimitorPacpus_;
    
    if ( !c.isNull() )
		msg += "c" + charEqual_ + c + charDelimitorPacpus_;
    
    return msg;  
}



//////////////////////////////////////////////////////////////////////////
// Construct and send the message in binary type
//////////////////////////////////////////////////////////////////////////
void PacpusDataCollector::buildAndSendBinMsg( QString T, QString t, char * dataToSend, int sizeOfDataToSend )
{
    QBuffer buffer;
    QDataStream streamOut( &buffer );
    buffer.open( QIODevice::WriteOnly );
    
    streamOut << buildOrAddMsg( "b", T, t );
    streamOut.writeRawData( dataToSend, sizeOfDataToSend );
    streamOut << charDelimitorPacpus_;
    
    pacpusSocket_->sendDatagrams( buffer.buffer() );	    
    buffer.close();	    
}
    


//////////////////////////////////////////////////////////////////////////
// Send the message with PacpusSocket
//////////////////////////////////////////////////////////////////////////
void PacpusDataCollector::sendMsg( QString msg )
{
    if ( msg != NULL )
    {
		msg += charDelimitor_;
		pacpusSocket_->sendDatagrams( msg );
    }
}



//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to pass the XML parameters to the 
// component 
//////////////////////////////////////////////////////////////////////////
ComponentBase::COMPONENT_CONFIGURATION PacpusDataCollector::configureComponent( XmlComponentConfig config )
{    
    QString pacpusSocket = config.getProperty( "socketComponent" );
    ComponentManager * mgr = ComponentManager::getInstance();
    pacpusSocket_ = dynamic_cast<PacpusSocket *>(mgr->getComponent(pacpusSocket));
    if ( !pacpusSocket_ ) {
	    qWarning() << "Failed to get component " << pacpusSocket;
	    return ComponentBase::NOT_CONFIGURED;
    }
    
    if ( config.getProperty( "char_equal" ) == NULL ) 
		charEqual_ = "~";
    else
		charEqual_ = config.getProperty( "char_equal" );
    
    if ( config.getProperty( "char_delim" ) == NULL ) 
		charDelimitor_ = "\\";
    else
		charDelimitor_ = config.getProperty( "char_delim" );
      
    if ( config.getProperty( "char_delimPacpus" ) == NULL ) 
		charDelimitorPacpus_ = "!";
    else
		charDelimitorPacpus_ = config.getProperty( "char_delimPacpus" );
   
    steeringWheelActive_ = false; 
    if ( config.getProperty( "steeringWheel" ) == "true" || config.getProperty( "steeringWheel" ) == "True" )
		steeringWheelActive_ = true;
  
    odometryActive_ = false;
    if ( config.getProperty( "odometry" ) == "true" || config.getProperty( "odometry" ) == "True" )
		odometryActive_ = true;
    
    VG700Active_ = false;
    if ( config.getProperty( "VG700" ) == "true" || config.getProperty( "VG700" ) == "True" )
		VG700Active_ = true;
    
    wheelSpeedActive_ = false;
    if ( config.getProperty( "wheelSpeed" ) == "true" || config.getProperty( "wheelSpeed" ) == "True" )
		wheelSpeedActive_ = true;
    
    cubeActive_ = false;
    if ( config.getProperty( "cube" ) == "true" || config.getProperty( "cube" ) == "True" )
		cubeActive_ = true;
    
    //TODO : 
    //yourDataActive_ = false;
    //if (config.getProperty("yourData") == "true" || config.getProperty("yourData") == "True")
    //	yourDataActive_ = true;
	
    if ( odometryActive_ == false && steeringWheelActive_ == false && wheelSpeedActive_ == false && VG700Active_ == false && cubeActive_ == false /*TODO : && yourDataActive_ == false*/ )  
		qFatal( "No actived collector\nProgram will stop" );
    
    if ( config.getProperty( "beginingMsg" ) == NULL ) 
		beginingMsg_ = "";
    else
		beginingMsg_ = config.getProperty( "beginingMsg" );
    
    headerMsgBin_ = charDelimitor_ + charDelimitorPacpus_ + "f" + charEqual_ + "b" + charDelimitorPacpus_ +  "T" + charEqual_;
    headerMsgText_ = charDelimitor_ + charDelimitorPacpus_ + "f" + charEqual_ + "t" + charDelimitorPacpus_ +  "T" + charEqual_  ;
    
    return ComponentBase::CONFIGURED_OK;
}
