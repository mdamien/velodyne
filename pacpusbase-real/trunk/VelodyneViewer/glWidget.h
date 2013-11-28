#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <cstdio>
#include <iostream>
#include <qmutex.h>
#include <vector>

#include <extlib/qwtplot3d/qwt3d_surfaceplot.h>
#include <extlib/qwtplot3d/qwt3d_enrichment.h>

#include "VelodyneViewerConfig.h"

/// The container of velodyne data (notably beams_)
class VELODYNEVIEWER_API VelodyneImage
{
public:
    VelodyneImage()
    {
    }

    ~VelodyneImage()
    {
    }

    void lock()
    {
        mutex_.lock();
    }

    void unlock()
    {
        mutex_.unlock();
    }

    /// add a beam 
    void addPoint(double* point);

    /// clear data container of the plot
    void clear();

    /// just a 3D point
    Qwt3D::Triple triple_;

    /// The container of the image (3D points)
    Qwt3D::TripleField beams_;

    /// To prevent adding new data when plotting
    QMutex mutex_;

    /// To know if we have to refresh
    bool refresh_;
};

// 
class VelodyneImageEnrichment
    : public Qwt3D::VertexEnrichment
{
public:
    VelodyneImageEnrichment()
    {
        velodyne_ = new VelodyneImage;
        printf("velodyne enrichment created\n");
    }

    ~VelodyneImageEnrichment()
    {
    }

    Qwt3D::Enrichment* clone() const
    {
        return new VelodyneImageEnrichment(*this);
    }

    /// The drawing function reimplemented
    void draw(Qwt3D::Triple const&);

    VelodyneImage * velodyne_;
};

class glWidget
    : public Qwt3D::SurfacePlot
{
    Q_OBJECT

public:
    glWidget(QWidget *pw);

    glWidget()
    {
    }

    ~glWidget();

    VelodyneImage * getVelodyneImage()
    {
        return image_->velodyne_;
    }

    public slots:

    // call this to refresh the plot
    void replot();	

private:
    VelodyneImageEnrichment * image_;

    Qwt3D::TripleField sensorVertex_;
    Qwt3D::CellField sensorEdges_;
};

#endif // GLWIDGET_H
