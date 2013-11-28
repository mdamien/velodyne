#include "VtkCurve.h"

VtkCurve::VtkCurve()
{
    points_ = vtkPoints::New();
    points_->SetNumberOfPoints(500);
    polyData_ = vtkPolyData::New();

    nbPoints_ = 0;

    glyphFilter_ = vtkVertexGlyphFilter::New();
    glyphFilter_->SetInputConnection(polyData_->GetProducerPort());
    glyphFilter_->Update();

    mapper_ =  vtkPolyDataMapper::New();
    mapper_->SetInputConnection(glyphFilter_->GetOutputPort());

    actor_ = vtkActor::New();
    actor_->GetProperty()->SetPointSize(2);
    actor_->GetProperty()->SetColor(1.0, 0.0, 0.0);
    actor_->SetMapper(mapper_);
}

VtkCurve::~VtkCurve()
{
}

void VtkCurve::insertPoints(Curve &curve)
{
    points_->SetPoint(curve.getX() + 250, curve.getX(), curve.getY(), curve.getZ());
    //nbPoints_++;
    //nbPoints_ = nbPoints_%(points_->GetNumberOfPoints());

    polyData_->SetPoints(points_);
    polyData_->Modified();
    polyData_->Update();
}
