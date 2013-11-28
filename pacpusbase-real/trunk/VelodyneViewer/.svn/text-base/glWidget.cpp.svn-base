#include "glWidget.h"

#include <cmath>
#include <qdebug.h>

#include "kernel/road_time.h"

using Qwt3D::BOX;
using Qwt3D::Cell;
using Qwt3D::Triple;
using Qwt3D::TripleField;
using Qwt3D::X1;
using Qwt3D::Y1;
using Qwt3D::Z1;

// mesures de temps : 10 msec pour afficher la trame opengl du velodyne 
// et 50 msec au total avec tout ce que fait qwtplot3D 

void VelodyneImage::addPoint(double * point)
{
  mutex_.lock();

  triple_.x = point[0];
  triple_.y = point[1];
  triple_.z =  point[2];
  beams_.push_back(triple_);

  mutex_.unlock();
}

void VelodyneImage::clear()
{  
  mutex_.lock(); 
  beams_.clear();
  refresh_ = true;
  mutex_.unlock();
}

void VelodyneImageEnrichment::draw(Qwt3D::Triple const&)
{
  velodyne_->lock(); 

  if (velodyne_->refresh_)  
  {
    velodyne_->refresh_ = false;
    printf("\n\ndraw\n\n");
  
    glBegin(GL_POINTS);
    glColor3d(1,0,0);
  
    TripleField::iterator it; 
    for (it = velodyne_->beams_.begin() ; it != velodyne_->beams_.end() ; it++)
    {
      glVertex3d(it->x, it->y, it->z);  
      //printf("draw 2\n");  
    }
    glEnd();    
  }
  
  velodyne_->unlock();
}

glWidget::glWidget(QWidget *pw)
    : SurfacePlot(pw)
{

  for (unsigned i=0; i!=coordinates()->axes.size(); ++i)
	{
		coordinates()->axes[i].setMajors(7);
		coordinates()->axes[i].setMinors(4);
	}

	coordinates()->axes[X1].setLabelString("x-axis");
	coordinates()->axes[Y1].setLabelString("Y-axis");
	coordinates()->axes[Z1].setLabelString("Z-axis");
	
	setCoordinateStyle(BOX);
  setOrtho(true);
	
  setRotation(30,0,15);
	setScale(1,1,1);
	setShift(0.15,0,0);
	setZoom(0.9);

	resize(pw->width(),pw->height());

  // we create the representation of the sensor, simply a square
  Triple triple;
  
  triple.x = 100;
  triple.y = 100;
  triple.z = 0;
  sensorVertex_.push_back(triple);

  triple.x = 100;
  triple.y = -100;
  triple.z = 0;
  sensorVertex_.push_back(triple);

  triple.x = -100;
  triple.y = -100;
  triple.z = 0;
  sensorVertex_.push_back(triple);

  triple.x = -100;
  triple.y = 100;
  triple.z = 0;
  sensorVertex_.push_back(triple);

  Cell cell;
  cell.push_back(0);
  cell.push_back(1);
  cell.push_back(2);
  cell.push_back(3);
  sensorEdges_.push_back(cell);
  
  loadFromData(sensorVertex_, sensorEdges_);

	// We assign the velodyne image to the plot
  image_ = (VelodyneImageEnrichment*)setPlotStyle(VelodyneImageEnrichment());
}

glWidget::~glWidget()
{
}

void glWidget::replot()
{
  road_time_t t1 = road_time();

  resize(parentWidget()->width(),parentWidget()->height());
  
  updateData();
  updateGL();

	road_time_t t2 = road_time();
	printf("temps = %d\n", (int) (t2-t1) );
}
