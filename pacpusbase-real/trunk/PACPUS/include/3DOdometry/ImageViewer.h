/*********************************************************************
// created:    2006/06/09 - 7:58
// filename:   ImageViewer.h
//
// author:     Gerald Dherbomez
// 
// version:    $Id: ImageViewer.h 686 2008-07-15 13:51:16Z jlaneuri $
//
// purpose:    use this class to display an image
*********************************************************************/

#ifndef _IMAGEVIEWER_H_
#define _IMAGEVIEWER_H_

//# include "../../include/VisualMemoryManager/struct.h"
#include <QFrame>
#include <QMutex>

#include "kernel/road_time.h"

class ImageViewer : public QFrame
{
  Q_OBJECT

public:
	ImageViewer();
       ~ImageViewer();

  void setMutex(QMutex* imageMutex) { imageMutex_ = imageMutex; };

public slots:
  void display(QImage * image);

protected slots:
  void paintEvent(QPaintEvent * e); 

private:
  QPixmap * imageBuffer_;   // the pixmap that will be displayed
  QMutex * imageMutex_;     // the mutex that protects access to the shared image

  road_time_t tic_;  
  void tic() { tic_ = road_time(); }
  void toc(char * text) { printf("duration = %d %s\n", (int)(road_time() - tic_), text ); }

};

#endif /* !_IMAGEVIEWER_H_ */
