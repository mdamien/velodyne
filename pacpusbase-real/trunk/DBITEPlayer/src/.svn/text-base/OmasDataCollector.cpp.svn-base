#include "DbitePlayer/OmasDataCollector.h" 
#include <math.h>


// Construction de la fabrique de composant DbtPlyEngine 
static ComponentFactory<OmasDataCollector>* factory  =  new ComponentFactory<OmasDataCollector>("OmasDataCollector");  



// constructor 
OmasDataCollector::OmasDataCollector(QString name) : ComponentBase(name), schoolPosition_(3)
{ 
	
} 


// destructor 
OmasDataCollector::~OmasDataCollector() 
{ 

} 



ComponentBase::COMPONENT_CONFIGURATION  OmasDataCollector::configureComponent(XmlComponentConfig config)
{
	if (!(server_ = (OmasUdpServer*)ComponentManager::create()->getComponent(param.getProperty("omasUdpServer")) ) )
		qWarning() << "Failed to get Udp server " << ComponentManager::create()->getComponent(param.getProperty("omasUdpServer"));

	schoolPosition_[0] = param.getProperty("school_X").toDouble();
	schoolPosition_[1] = param.getProperty("school_Y").toDouble();
	schoolPosition_[2] = param.getProperty("school_Z").toDouble();

	return ComponentBase::CONFIGURED_OK; 
}


void OmasDataCollector::startActivity() 
{
#if WIN32
	gpsShMem_ = new ShMem("GPS", sizeof(donnees_gps));
	char name[40];
	sprintf(name, "CARMEN_CAN_%d", CARMEN_CAN_ODOMETRY);
  canSpeedShMem_ = new ShMem(name, sizeof(TimestampedStructVehicleSpeed));
	alascaShMem_ = new ShMem("alasca", sizeof(ScanAlascaData)); 
#endif

	start();

}

void OmasDataCollector::stopActivity() 
{ 
	THREAD_ALIVE = false;

	if (!wait(2000))
	{
		terminate();
		qDebug() << componentName << " - thread is blocking, it has been terminated\n";
	}
#if WIN32
	delete gpsShMem_;
#endif

}


void OmasDataCollector::run()
{
	road_time_t time = road_time();
	THREAD_ALIVE = true;
	
	while (THREAD_ALIVE)
	{
		if(gpsShMem_->wait(1500))
		{
			memcpy(&gpsData_, gpsShMem_->read(), sizeof(donnees_gps));
			memcpy(&canOdometryFrame_, canSpeedShMem_->read(), sizeof(TimestampedStructVehicleSpeed));
			memcpy(&alascaData_, alascaShMem_->read(), sizeof(ScanAlascaData));

			compute();

			int deltaTime = road_time() - time ;
			if (deltaTime > 500000)
			{
				// build the frame and send it
				QString frame;
				frame = "= :VU " + QString::number(vehicleSpeed_) + " :DAP " + QString::number(distanceToDoor_) + " :TAP " + QString::number(timeToDoor_);
				server_->sendDatagrams(frame);
				frame = "= :DV " + QString::number(vulnerablesDensity_) + " :DMV " + QString::number(distanceToVulnerables_) + " :TAV " + QString::number(timeToVulnerables_);
				server_->sendDatagrams(frame);
 				time += deltaTime;
			}
			
		}
	}
}



// Manage the school approach
// Compute the distance between the school door and the vehicle
void OmasDataCollector::compute()
{
	vehicleSpeed_ = canOdometryFrame_.d.vehicleSpeed/3.6;
	distanceToDoor_ = sqrt((gpsData_.x - schoolPosition_[0])*(gpsData_.x - schoolPosition_[0]) + (gpsData_.y - schoolPosition_[1])*(gpsData_.y - schoolPosition_[1]) );
	timeToDoor_ = distanceToDoor_ / vehicleSpeed_;

	distanceToVulnerables_ = 200.0; // max range of sensor
	if (vehicleSpeed_ > 0)
		timeToVulnerables_ = distanceToVulnerables_/vehicleSpeed_;
		else timeToVulnerables_ = 60;
	
	// compute the presence of obstacles in front of the vehicle in the range between 2s and 5s  
	for (int i = 0 ; i < alascaData_.nbPoint ; ++i)
	{
		if ( (alascaData_.point[i].y < -100) || ( alascaData_.point[i].y > 100 ) || (alascaData_.point[i].layerNumber<3) )
			continue; // out of range
		else 
		{
			if (alascaData_.point[i].x < 60)
				continue;
			float tmp = ((float)alascaData_.point[i].x)/100.0;
			distanceToVulnerables_ = (distanceToVulnerables_ < tmp ? distanceToVulnerables_:tmp );
			if (vehicleSpeed_ > 0)
				timeToVulnerables_ = distanceToVulnerables_/vehicleSpeed_;

			if (timeToVulnerables_ < 2)
				vulnerablesDensity_ = 3;
			else if (timeToVulnerables_ < 3)
				vulnerablesDensity_ = 2;
			else if (timeToVulnerables_ < 5)
				vulnerablesDensity_ = 1; 
			else vulnerablesDensity_ = 0;
		}
	}
}