
#define MAX_NB_OBJETS 100
#define MAX_NB_PISTES 100
#define IBEO_DATA_SIZE 12*8648
#define PROPRIO_DATA_SIZE 2*6
#define PI 3.14159265
#define GND_HDS 0x30 
#define GND_IBO 0x03
#define GND 0x33

//Local Headers
#include "AlascaDataModule.h"
#include "AlascaViewer3D.h"
#include "inifile.h"
//Architecture headers
#include "structure/structureCanCarmen.h"
#include "pacpusTools/ShMem.h"
#include "kernel/road_time.h"
//LoVe project headers 
#include "LOVe.h"


class AlascaLOVeComputing : public QObject, public AlascaDataModule
{
  Q_OBJECT

public:
  AlascaLOVeComputing(QString name);
  ~AlascaLOVeComputing();
  void compute(GlobalAlascaData data);
  //Empty functions
  void setImage(QImage * image) {};
  void setWheelSpeed(TimestampedStructWheelSpeed speed) {};
  void setRadar(const DONNEE_RADAR &data_radar) {};

protected:
  virtual void startActivity();
  virtual void stopActivity();
  virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

signals:
  void refreshDisplay();   //flush the bird view window

private:

	// A pointer on the 3D viewer component
	AlascaViewer3D * viewer3d_;

	QMutex * heu32Mutex_; // dll protection for local synchronization (useful only if different function calls the dll)

	lorusl var_lorusl;
	lprusl var_lprusl;
	zrusl var_zone_love;
	donnee_capteur ibeo_data;
	donnee_capteur proprio_data;

	char numeroCapteur;

	HMODULE hDLL_HEU24A, hDLL_HEU32A;

	typedef void (__cdecl *DLL_Function_1)();
	typedef void (__cdecl *DLL_Function_11)(char * );
	typedef void (__cdecl *DLL_Function_2)(donnee_capteur* , zrusl* );
	typedef void (__cdecl *DLL_Function_3)(lorusl* );
	typedef void (__cdecl *DLL_Function_4)(lorusl* , lorusl* , lorusl* , lorusl* , donnee_capteur* );
	typedef void (__cdecl *DLL_Function_5)(lprusl* );

	DLL_Function_11 start_HEU24A;
	DLL_Function_1 stop_HEU24A;
	DLL_Function_1 calculer_HEU24A;
	DLL_Function_2 lire_HEU24A;
	DLL_Function_3 ecrire_HEU24A;

	DLL_Function_11 start_HEU32A;
	DLL_Function_1 stop_HEU32A;
	DLL_Function_1 calculer_HEU32A;
	DLL_Function_4 lire_HEU32A;
	DLL_Function_5 ecrire_HEU32A;

	//Love -> lidarObject conversion for shmem data sharing 
	//(reason: love structure it's so complicated for data exchange by using shmem, this is not optimal but necessary)
	CIniFile			ConfFile_;

	bool				offset_;
	ShMem*				tobeRead_;
	ShMem*				lidarObjectBuffer_;
	
	int					MAX_LIDAR_OBJECTS;
	lidarObjectList*	scanedObjects_;

	void broadcastObjects(lorusl*, zrusl*, lidarObjectList*, ScanAlascaData*); 
	void broadcastTracks(lprusl*, zrusl*, lidarObjectList*, ScanAlascaData*); 
	//even if inputs are variables of the class I ask for their pointers
	//for changing Love variable names

};