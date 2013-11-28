/*********************************************************************
//  created:    2010/04/21
//  filename:   VelodyneViewer.cpp
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    
//
*********************************************************************/

#include <cmath>
#include <iostream>
#include <qendian.h>
#include <qdebug.h>
#include <string>

#include "VelodyneViewer.h"
#include "kernel/ComponentFactory.h"

#ifndef M_PI
#   define M_PI 3.1415
#endif // M_PI

namespace pacpus {

using Qwt3D::RGBA;

// Construct the factory
static ComponentFactory<VelodyneViewer> sFactory("VelodyneViewer");

template<typename T>
T Deg2Rad(const T & deg)
{
    return deg * M_PI / 180;
}

template<typename T>
T Rad2Deg(const T & rad)
{
    return rad * 180 / M_PI;
}

//////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////
VelodyneViewer::VelodyneViewer(QString name)
    : ComponentBase(name)
{   
	shMem_ = NULL;
	
  glWidget_ = new glWidget(&window_);
  window_.show();	
	connect(this, SIGNAL(display()), glWidget_, SLOT(replot()));
	//glWidget_->setTitle("Widget Title");
	//glWidget_->setTitlePosition(0.95,0.5);
  //	glWidget_->setFloorStyle(FLOORISO);
	glWidget_->setBackgroundColor(RGBA(1.0, 1.0, 1.0));       //background color 
	glWidget_->coordinates()->setAxesColor(RGBA(0, 1.0, 0));	//bounding box color
	glWidget_->setMeshColor(RGBA(1.0,0.0,0.0));								//line color
	glWidget_->makeCurrent();
	glWidget_->updateData();
	glWidget_->updateGL();
}





//////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////
VelodyneViewer::~VelodyneViewer()
{

}




//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to start the component
//////////////////////////////////////////////////////////////////////////
void VelodyneViewer::startActivity()
{
  shMem_ = new ShMem("VELODYNE", sizeof(VelodynePolarData) );
  if (!shMem_)
    qFatal("Failed to create Veldoyne shared memory");
  start();
}



//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to stop the component
//////////////////////////////////////////////////////////////////////////
void VelodyneViewer::stopActivity()
{
  running_ = false;
  if (!wait(2000)) // wait termination during 2 seconds
  {
    qDebug("thread blocking, terminate it !!");
    terminate();
  }

	if (shMem_ != NULL)
	{
		delete shMem_;
		shMem_ = NULL; 
	}
}

//////////////////////////////////////////////////////////////////////////
/// Called by the ComponentManager to pass the XML parameters to the 
/// component 
ComponentBase::COMPONENT_CONFIGURATION VelodyneViewer::configureComponent(XmlComponentConfig config)
{
  return ComponentBase::CONFIGURED_OK;
}

//////////////////////////////////////////////////////////////////////////
/// TODO: main loop
void VelodyneViewer::run()
{
    running_ = true;

    // 5 facteurs de corrections
    //double rotCor[64];
    //double vertCor[64];
    //double distCor[64];
    //double hOffsetCor[64];
    //double vOffsetCor[64];

    double d; // distance recu par le velodyne
    //   double d; // distance corrigee = dist + deltaD_xml
    double dxy; // distance XY
    double alpha; // angle azimuth
    //   double phi; // angle azimuth corrige az - rotcor_xml
    double beta; // angle elevation 

    double pt[3];
    pt[0] = 0;
    pt[1] = 0; 
    pt[2] = 0; 
    printf("on entre dans la boucle \n");
    while (running_) { 
        /*
        pt[0] = 1.5; // x
        pt[1] = 3.5; // y
        pt[2] = 2.2; // z 
        // on affiche 
        glWidget_->addPoint(pt);

        pt[0] = 14.5; // x
        pt[1] = 6.5; // y
        pt[2] = 8.0; // z 
        // on affiche 
        glWidget_->addPoint(pt);

        emit display();
        */

        shMem_->wait();
        shMem_->lockMemory();
        void *ptr = shMem_->read();
        memcpy(&velodyneData_, ptr, sizeof(velodyneData_) );
        shMem_->unlockMemory();
        printf(".%d",velodyneData_.range);
        fflush(stdout);
        // first clear the plot before refreshing
        glWidget_->getVelodyneImage()->clear();
        printf(".\n");
        for (int i = 0 ; i < velodyneData_.range ; ++i) {
            alpha = ((velodyneData_.polarData[i].angle) / 100.0 ) * 3.1415  / 180.0;
            //      alpha = (qFromBigEndian(velodyneData_.polarData[i].angle));
            //      alpha = velodyneData_.polarData[i].angle;
            //  qDebug() << i << velodyneData_.polarData[i].block << alpha << velodyneData_.range;
            if (velodyneData_.polarData[i].block == 0xEEFF) {
                //printf(" bloc du haut");
                beta = Deg2Rad(2);
            } else if (velodyneData_.polarData[i].block == 0xDDFF) {
                //printf(" bloc du bas");
                beta = Deg2Rad(2 - (26.8/63)*32);
            } else {
                printf("Invalid data\n");
                continue;
            }
            // boucle pour les 32 impacts  
            for (int j = 0 ; j < 32 ; ++j) {
                d = (velodyneData_.polarData[i].rawPoints[j].distance)/500.0; // increments de 2mm => /500 pour avoir des m         
                dxy = d * cos(beta);
                pt[0] = dxy * sin (alpha); // x
                pt[1] = dxy * cos (alpha); // y
                pt[2] = d * sin (beta); // z 
                // on affiche 
                glWidget_->getVelodyneImage()->addPoint(pt);
                // on met a jour beta 
                beta += Deg2Rad(26.8/63); // 26.8 degrees FOV vertical, 64 impacts donc 63 increments d'angle
            }

        }
        printf("-");
        fflush(stdout);  
        Q_EMIT display();
    }
    qDebug() << "fin du thread";  
}

} // namespace pacpus
