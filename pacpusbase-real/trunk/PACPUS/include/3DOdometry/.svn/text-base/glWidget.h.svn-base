#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <iostream>
#include <QApplication>
#include <qwt3d_surfaceplot.h>
#include <vector>
//=============================================================================
//OpenCV Includes
//=============================================================================
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"

#define  PI_ 3.141592653589793

using namespace std;
using namespace Qwt3D;

class glWidget : public QObject, public Qwt3D::SurfacePlot
{
	Q_OBJECT

public:
	glWidget(QWidget *pw);
	glWidget(){};
	~glWidget();

	void plot(void);

public slots:
	void openglMotion(double*);	

private:

	TripleField* cam3dPos_;
  Triple*			 triple_;
	CellField*   cam3dPoly_;
	Cell*        cell_;

	double   motion_[6]; //radians and meters

	CvMat* Vect3x1;
	CvMat* Mat3x3;
	
	CvMat* rot_;
	CvMat* trans_;
	CvMat* curRot_;
	CvMat* curTrans_;
};

#endif 