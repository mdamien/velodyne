#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QGridLayout>
#include <QSplitter>
#include <QLabel>
#include <QApplication>
#include <qwt3d_surfaceplot.h>
#include "glWidget.h"

using namespace std;
using namespace Qwt3D;

class mainWindow : public QWidget
{
	Q_OBJECT

private:
	double motion_[6];

public:
	mainWindow();
	~mainWindow();

	void Window();
	void setMotion(double* t){memcpy(motion_, t, 6*sizeof(double));
												emit motion(motion_);}
	
	glWidget*	glWidget_; 

signals:
	void motion(double*);

};
#endif 