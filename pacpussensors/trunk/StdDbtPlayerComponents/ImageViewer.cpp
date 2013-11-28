/*********************************************************************
// created:     2006/06/09 - 9:40
// filename:    ImageViewer.cpp
//
// author:      Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
// version:     $Id$
//
// purpose:     Definition of the ImageViewer class
//
// todo :	      - think how to display geometric forms in the viewer (line, 
//              circles, points, etc.)
*********************************************************************/

#define DEFAULT_IMAGE_WIDTH 320
#define DEFAULT_IMAGE_HEIGHT 240
#define DEFAULT_IMAGE_DEPTH 32

#include "ImageViewer.h"

#include <iostream>

#include <QDebug>
#include <QImage>
#include <QMutex>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////
ImageViewer::ImageViewer() : imageBuffer_(NULL)
{
  // setBackgroundMode(Qt::NoBackground); 
  setBackgroundRole(QPalette::Window);
  imageBuffer_ = new QPixmap(DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT); 
  resize(imageBuffer_->size());
}


//////////////////////////////////////////////////////////////////////////
// destructor

//////////////////////////////////////////////////////////////////////////
ImageViewer::~ImageViewer()
{
    delete imageBuffer_; 
}

//////////////////////////////////////////////////////////////////////////
// slot
// connect this to the signal that will send the image
//////////////////////////////////////////////////////////////////////////
void ImageViewer::display(QImage * image)
{ 
  //tic();
  imageMutex_->lock();
  if ( (image == NULL) || (image->isNull()) )
  {
    qDebug() << "ImageViewer: image is no more valid, not displayed"; 
  }
  else
  { 
    if (imageBuffer_->size() != image->size())
      resize(image->size()); 
    *imageBuffer_ = QPixmap::fromImage(*image);  
    update();
  }
  imageMutex_->unlock();
  //toc("imageViewer");

}



//////////////////////////////////////////////////////////////////////////
// slot
// activated when repaint() is called
//////////////////////////////////////////////////////////////////////////
void ImageViewer::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);
    painter.setClipRect(e->rect()); 
    if (imageBuffer_) {
        painter.drawPixmap(0,0,*imageBuffer_);
    }
}

//////////////////////////////////////////////////////////////////////////
void ImageViewer::setMutex(QMutex * imageMutex)
{
    imageMutex_ = imageMutex;
}

void ImageViewer::tic()
{
    tic_ = road_time();
}

void ImageViewer::toc(char * text)
{
    cout << "duration = " << (int)(road_time() - tic_) << " " << text << "\n";
}
