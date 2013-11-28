#ifndef THREADSON_H
#define THREADSON_H


#include "../include/fmod/fmod.h"

// Pour l'utilisation de QT
//#include <qapplication.h>
#include <qobject.h>
#include <qthread.h>
//#include <qwt_plot.H>
//#include <qstring.h> 
//#include <qlineedit.h> 
//#include <qcheckbox.h> 
//#include <qlayout.h> 


class DisplayImpl;

/*** Classe ThreadSON ************************************************************/
/*                                                                               */
/*   Ouverture d'un fichier sonore, reglage de la balance et du volume,          */
/*   lecture du fichier                                                          */
/*                                                                               */
/*********************************************************************************/

class ThreadSON : public QObject, public QThread
{
	Q_OBJECT

public:
	
	ThreadSON(DisplayImpl *parent);
	~ThreadSON();
	virtual void lecture(int volume, int balance);

	// variables de la classe ThreadSON
		int vol; // volume 0: min, 255: max
		int bal; // balance 0: gauche, 128: milieu, 255: droite
		FSOUND_STREAM *sequence[19];
		int duree[19];
		int iChannel;

public slots:
	void activate(bool on); 


protected:
	virtual void run();

private:
	bool CONTINUE;
	DisplayImpl *plt;
};

#endif
