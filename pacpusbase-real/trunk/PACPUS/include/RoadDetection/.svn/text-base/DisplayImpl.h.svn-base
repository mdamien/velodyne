// DisplayImpl.h: interface for the DisplayImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined __DISPLAYIMPL_H__
#define __DISPLAYIMPL_H__

#include <qapplication.H>
#include <qwt_plot.H>
#include <qstring.h> 
#include <qlineedit.h> 
#include <qcheckbox.h> 
#include <QThread.H>
#include <qlayout.h> 


#include "RoadDetection/sound.h"

#include "kernel/ComponentFactory.h"
#include "kernel/ComponentBase.h"
#include "RoadDetection/constantes.H"
#include "../moc/mainwindow.h"
#include "RoadDetection/pavementdetection.h"

#include "LandmarkFileManager.h"
//nclude "memoire_partagee.H"



class ThreadSON; 

class DisplayImpl : public Display, public QThread, public ComponentBase
{
	Q_OBJECT

public:
	
    //LandmarkFileManager *land ;
	~DisplayImpl(){};

	DisplayImpl( const char *name = 0); 
	// Tache de lecture en memoire partagee
	void run(); 


	// les fonctions suivantes sont nécessaires pour l'héritage de ComponentBase
	// elles sont lancées dans l'ordre suivant par le ComponentManager : 
	// - le constructeur de la classe 
	// - configureComponent 
	// - startActivity
	// -stopActivity seulement à la fermeture du programme

	void configureComponent (XmlComponentConfig config); 
	void startActivity(); 
	void stopActivity(); 
	
private:
		
	double x_telem[PLOT_SIZE], y_telem[PLOT_SIZE], z_telem[PLOT_SIZE], dx[PLOT_SIZE],dy[PLOT_SIZE],dz[PLOT_SIZE],dyn1[PLOT_SIZE];
	double y_detect_d, y_detect_g, z_detect_d, z_detect_g; 
	double axex[181], axey[181];
	int m,k,modulo;
	int indconfg;
	int indconfd;
	bool detectiond,detectiond_old,detectiong,detectiong_old;
	double hautd,hautg ,xmin,xmax,ymin,ymax;
	int angle;
	double xtel[PLOT_SIZE],ytel[PLOT_SIZE],ztel[PLOT_SIZE];
	long curv3, curv4 ;
	bool CONTINUE;
	//double *tabx;
	//double *taby;
	
	ThreadSON *son;
	QwtSymbol *symbold,*symbolg ; 

	QString aff; 

public slots:
	void activate(bool ON); 


	void set_bd(double *x,double *y,double *z,int k);
	void set_bg(double *x ,double *y ,double *z,int m);
	void set_indconfg(int indconfg);
	void set_indconfd(int indcond);
	void set_high (double hautd, double hautg);
	void set_detection(bool *detectiond,bool *detectiond_old,bool *detectiong,bool *detectiong_old );

	void Replot(double *dyn,double *y,double *z,double  y_detect_gauche,double y_detect_droit,double z_detect_gauche,double z_detect_droit);
	


};

#endif 
