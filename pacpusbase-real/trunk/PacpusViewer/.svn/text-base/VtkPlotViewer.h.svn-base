#ifndef _VTKPLOTVIEWER_H_
#define _VTKPLOTVIEWER_H_

#include <QString>
#include <QVector>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkCubeAxesActor2D.h>
#include <QVTKWidget.h>

#include "VtkCurve.h"

class VtkPlotViewer
        : public QVTKWidget
{
public:
        VtkPlotViewer(QString name);
	~VtkPlotViewer();
        void displayData(Curve &curve);
        void initialize();
        QString name()
        {
            return name_;
        }
        int curveSize()
        {
            return curves_.size();
        }
        Curve * curve( int index )
        {
            return &(curves_[index]);
        }
        void addCurve(Curve curve)
        {
            curves_.append(curve);
        }

private:
        QString name_;

        vtkCubeAxesActor2D *axe_;
        vtkRenderer *renderer_;
        vtkRenderWindow *renderWindow_;

        VtkCurve *curve_;

        QString XLabel_, YLabel_;
        double Bounds_[6], Color_[3];
        QList<Curve> curves_;
};

#endif
