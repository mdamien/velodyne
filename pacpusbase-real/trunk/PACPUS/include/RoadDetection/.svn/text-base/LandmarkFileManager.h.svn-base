// LandmarkFileManager.h: interface for the LandmarkFileManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined __LANDMARKFILEMANAGER_H__
#define __LANDMARKFILEMANAGER_H__

#include "pacpustools/matrice.h"
#include "kernel/pacpus.h"
#include "RoadDetection/sound.h"

#include "kernel/ComponentFactory.h"
#include "kernel/ComponentBase.h"
//#include "memoire_partagee.H"
#include "RoadDetection/constantes.H"
#include "../moc/mainwindow.h"
#include "RoadDetection/PavementDetection.h"
#include <windows.h>
#include "kernel\road_time.h"
#include <qsocket.h>
#include <qApplication.h>
#include <QThread.H>
#include <qlayout.h>
#include <iostream>
#include <fstream>
#include <qdir.h> 
#include <math.h>
//#include <qFtp.h>

using namespace std;


class LandmarkFileManager : public QObject, public QThread ,public ComponentBase
{
	 Q_OBJECT
public:
  
  LandmarkFileManager(const char *name = 0); 
		
		~LandmarkFileManager(){};
    void run();
    //--------------------------------------------------------
    void configureComponent (XmlComponentConfig config); 
    void startActivity(); 
    void stopActivity(); 
    
    //----------------------------------------------------------
    
    

    // Remarque : on a 8 bords de voie pour chaque route : 
    // - repertoire E2W et W2E avec ID_N et ID_S et dans fichier 2 bords Droit et gauche
    // Est-ce nécessaire ? 
    
    // retourne true si le répertoire a été correctement créé. 
    bool createDir(s_MatchedPosition myMatchedPosition);
    
    void EnregistrerFichierMatlab(s_MatchedPosition myMatchedPosition ,float xk,float yk,float xm,float ym);
    
private :
		TELEMETER_DATA *donnee; 
    s_MatchedPosition	myMatchedPosition_;
    double x_telem[PLOT_SIZE], y_telem[PLOT_SIZE], z_telem[PLOT_SIZE],dyn[PLOT_SIZE];
    double y_detect_droit, y_detect_gauche, x_detect_droit, x_detect_gauche,z_detect_droit, z_detect_gauche; 
    char *filesID;
    int m,k,wait_val;
    int indconfg;
    int indconfd;
    bool detectiond,detectiond_old,detectiong,detectiong_old;
    double hautd,hautg,xmin,xmax,ymin,ymax;;
    double *tabx;
    double *taby;
    QDir*	dir_;
    
    double x[PLOT_SIZE],y[PLOT_SIZE],z[PLOT_SIZE];
    
    HANDLE signal_disp;
    HANDLE MPreceived;
    HANDLE Data_telem;
    HANDLE event_position[2];
    HANDLE sh_memory;
    LPVOID clientShMemory_;
    
    PavementDetection pav_;
    
    bool CONTINUE;
    
    
signals:
    void set_bd(double *x,double *y,double *z,int k);
    void set_bg(double *x ,double *y ,double *z,int m);
    void set_indconfg(int indconfg);
    void set_indconfd(int indconfd);
    void set_high (double hautd, double hautg);
    void set_detection(bool *detectiond,bool *detectiond_old,bool *detectiong,bool *detectiong_old  );
    
    void Replot(double *dyn,double *y,double *z,double  y_detect_gauche,double y_detect_droit,double z_detect_gauche,double z_detect_droit);
    
    //-----------------------
    
    
};

#endif 
