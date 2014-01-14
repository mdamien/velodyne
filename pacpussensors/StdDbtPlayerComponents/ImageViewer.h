/*********************************************************************
// created:    2006/06/09 - 7:58
// filename:   ImageViewer.h
//
// author:     Gerald Dherbomez
// 
// version:    $Id: ImageViewer.h 1239 2012-11-28 16:30:00Z kurdejma $
//
// purpose:    use this class to display an image
*********************************************************************/

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "StdDbtPlayerComponentsConfig.h"
#include "kernel/road_time.h"

//# include "../../include/VisualMemoryManager/struct.h"

#include <QFrame>

class QMutex;

class STDDBTPLAYERCOMPONENTS_API ImageViewer
        : public QFrame
{
    Q_OBJECT

public:
	ImageViewer();
    ~ImageViewer();

    void setMutex(QMutex * imageMutex);

public Q_SLOTS:
    void display(QImage * image);

protected Q_SLOTS:
    void paintEvent(QPaintEvent * e);

private:
    QPixmap * imageBuffer_;   // the pixmap that will be displayed
    QMutex * imageMutex_;     // the mutex that protects access to the shared image

    road_time_t tic_;
    void tic();
    void toc(char * text);
};

#endif // IMAGEVIEWER_H
