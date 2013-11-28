
#define MAX_NB_OBJETS 100
#define MAX_NB_PISTES 100
#define IBEO_DATA_SIZE 12*8648
#define PROPRIO_DATA_SIZE 2*6
#define PI 3.14159265
#define GND_HDS 0x30 
#define GND_IBO 0x03
#define GND 0x33


#include "viewer/AlascaDataModule.h"
#include "viewer/AlascaViewer3D.h"

#include "driver/CanDriverBase.h"
#include "structure/structureCanCarmen.h"
#include "viewer/ImageProjection.h"
#include "matrix.h"
#include "viewer/window.h"
#include "structure/structure_radar.h"

#include "LOVe.h"


class AlascaLOVeComputing : public QObject, public AlascaDataModule
{
  Q_OBJECT

public:
  AlascaLOVeComputing(QString name);
  ~AlascaLOVeComputing();
  void compute(GlobalAlascaData data);
  void setImage(QImage * image);
  void setWheelSpeed(TimestampedStructWheelSpeed speed);
  void setRadar(const DONNEE_RADAR &data_radar) {};

signals:
  void refreshDisplay();

protected:
  virtual void startActivity();
  virtual void stopActivity();
  virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

signals: 
  void displayIm(QImage*);

private:

	ImageProjection imageProjection;

	// A pointer on the 3D viewer component
	AlascaViewer3D * viewer3d_;

	// image 
	QMutex * imageMutex_;
	QMutex * heu32Mutex_;
	QImage * image_;

	//
	lorusl var_lorusl;
	lprusl var_lprusl;
	zrusl var_zone_love;
	donnee_capteur ibeo_data;
	donnee_capteur proprio_data;

	// Declaration of Camera-Alasca calibration parameters
	matrice K;
	matrice R;
	matrice Deltha;

	// Slider Window 
	window tableau_bord;

	// Recognition Threshold
	int recognition_threshold;

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
	

};