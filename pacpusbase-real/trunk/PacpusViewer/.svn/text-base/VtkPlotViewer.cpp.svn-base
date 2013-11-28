#include "VtkPlotViewer.h"

VtkPlotViewer::VtkPlotViewer(QString name)
{
    name_ = name;

    axe_ = vtkCubeAxesActor2D::New();
    renderer_ = vtkRenderer::New();
    renderWindow_ = vtkRenderWindow::New();

    curve_ = new VtkCurve;

    this->setWindowTitle(name);
}

VtkPlotViewer::~VtkPlotViewer()
{
}

void VtkPlotViewer::displayData(Curve &curve)
{
    curve_->insertPoints(curve);
    axe_->SetBounds(-250.0, 250.0, 0.0, curve.getY(), 0.0, 0.0);
    this->update();
}

void VtkPlotViewer::initialize()
{
    this->SetRenderWindow(renderWindow_);
    this->GetRenderWindow()->AddRenderer(renderer_);
    renderWindow_->Delete();
    axe_->SetCamera(renderer_->GetActiveCamera());
    axe_->ZAxisVisibilityOff();
    axe_->SetXLabel("X");
    axe_->SetYLabel("Y");
    axe_->SetFlyModeToClosestTriad();
    axe_->SetCornerOffset(0.0);
    axe_->SetBounds(-250.0, 250.0, 0.0, 0.0, 0.0, 0.0);
    axe_->GetProperty()->SetColor(0.0, 0.0, 0.0);

    renderer_->SetBackground(1.0, 1.0, 1.0);
    renderer_->SetActiveCamera(renderer_->GetActiveCamera());
    renderer_->GetActiveCamera()->SetPosition(0.0, 0.0, 250);
    renderer_->GetActiveCamera()->SetDistance(250);
    renderer_->AddActor(axe_);
    renderer_->AddActor(curve_->actor());

    this->resize(800, 300);

    this->show();
}
