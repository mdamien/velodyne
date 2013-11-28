

#include "kernel/ComponentBase.h" 
#include "kernel/ComponentFactory.h" 

#include <QThread>
#include <QVector>
#include "PacpusTools/ShMem.h"
#include "structure/structureCanCarmen.h"
#include "structure/structure_telemetre.h"

#include "OmasUdpServer.h"
 
class OmasDataCollector : public QThread, public ComponentBase 
{ 
  Q_OBJECT 
 
public: 
  // Constructor 
  OmasDataCollector(QString name); 
 
  // Destructor 
  ~OmasDataCollector(); 

	// Main loop
	void run();
 
protected: 
  virtual void startActivity();
  virtual void stopActivity();
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

	void compute();

	// Data coming from PACPUS
	donnees_gps gpsData_;
	ShMem *gpsShMem_;
	TimestampedStructVehicleSpeed canOdometryFrame_;
	ShMem *canSpeedShMem_;
	ScanAlascaData alascaData_;
	ShMem *alascaShMem_;

	// Communication objects with OMAS
	OmasUdpServer * server_;

	// the position (X Y Z in meters) of the school door 
	QVector<double> schoolPosition_;

	// School door metrics
	float distanceToDoor_; // DAP in m
	float vehicleSpeed_;   // VU in m/s
	float timeToDoor_;     // TAP in s
	
	// vulnerables metrics
	int vulnerablesDensity_; // 0:noting(TAV>5s), 1:weak(3<TAV<5s), 2:high (2<TAV<3s), 3:very high (TAV<2s)
	float distanceToVulnerables_; // DMV in m (minimal distance)
	float timeToVulnerables_; // TAV in s
	
	// context metrics
	bool areaEntrance_; // ARZ - key word 
};
