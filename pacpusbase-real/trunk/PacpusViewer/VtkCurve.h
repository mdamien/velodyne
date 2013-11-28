#ifndef _VTKCURVE_H_
#define _VTKCURVE_H_

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkVertexGlyphFilter.h>

#include "Curve.h"

class VtkCurve
{
public:
        VtkCurve();
        ~VtkCurve();
        void insertPoints(Curve &curve);
        vtkActor * actor() {return actor_;};

private:
    vtkPoints *points_;
    vtkPolyData *polyData_;
    vtkVertexGlyphFilter *glyphFilter_;
    vtkPolyDataMapper *mapper_;
    vtkActor *actor_;
    int nbPoints_;
};
#endif
