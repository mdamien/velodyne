/*********************************************************************
//  created:    2008/01/14 - 12:45
//  filename:   AlascaViewer3D.h
//
//  author:     Gerald Dherbomez
// 
//  version:    $Id: $
//
//  purpose:    
//
//  todo:       find an automatic method to determine the steps of the axis
//              multiple of ( 1 2 5 ).10^n
//
*********************************************************************/


#ifndef __AlascaViewer3D_H__
#define __AlascaViewer3D_H__



#ifdef WIN32
// to use M_PI
#define _USE_MATH_DEFINES
#endif

#include <math.h>

#include <QDockWidget>
#include <QGLWidget>

#include "kernel/ComponentBase.h"
#include "kernel/road_time.h"

typedef QMap<QString,GLuint> Objects3dList; 


struct Line2d {
  QString name;
  double x1; 
  double y1; 
  double x2;
  double y2;
  QColor color;
};

struct Layer2d {
  QString name;
  double *x;
  double *y;
  int size;
  QColor color;
};

struct Ellipse2d {
  QString name;
  double xc;
  double yc;
  double width;
  double height;
  QColor color;
};

struct Circle2d { 
  QString name;
  double xc;
  double yc;
  double radius;
};

struct Text2d {
  QString name;
  double x;
  double y;
  QString text;
  QColor color;
};




class GLWidget : public QGLWidget
{
  Q_OBJECT

public:
  GLWidget();
  ~GLWidget();

  // The 3 openGL reimplemented methods
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  inline void setXMin(double xMin) {xMin_ = xMin;}
  inline void setXMax(double xMax) {xMax_ = xMax;}
  inline void setYMin(double yMin) {yMin_ = yMin;}
  inline void setYMax(double yMax) {yMax_ = yMax;}

  void displayGrids(bool on);
  void displayAxis(const bool on, const QColor color = Qt::darkRed );

  inline bool exists(QString name) {return objects3dList_.contains(name);}
  GLuint getOpenglId(QString name);
  void removeOpenglId(QString name);

  void draw2dLine(double x1, double y1, double x2, double y2, const QColor color);
  void draw2dEllipse(double xc, double yc, double width, double height, const QColor color);
  void displayText();

  Objects3dList objects3dList_;
  QList<Text2d> texts_;
  void setListLock(QMutex * mutex) {listLock_ = mutex;}

  void keyPressEvent ( QKeyEvent * event );


public slots:
  GLuint display2dLine(QString name, double x1, double y1, double x2, double y2, const QColor color = Qt::white);
  GLuint display2dLayer(QString name, double *x, double *y, int size, const QColor color);
  void display2dCircle(double xc, double yc, double radius){};
  GLuint displayText(QString name, double x, double y, QString text);
  GLuint display2dEllipse(QString name, double xc, double yc, double width, double height, const QColor color= Qt::white);

private:
  // the position of the camera
  double xCam_; 
  double yCam_; 
  double zCam_;

  // the opening angle of the camera
  double camOpening_;

  // the minimum and maximum of the graph axis
  double xMin_;
  double xMax_;
  double yMin_;
  double yMax_;

  QMutex * listLock_;
  

  // for performance computing
  road_time_t tic_;  
  void tic() { tic_ = road_time(); }
  void toc(char * text) { printf("duration = %d %s\n", (int)(road_time() - tic_), text ); }

};



class AlascaViewer3D : public QDockWidget, public ComponentBase
{
  Q_OBJECT

public:
  AlascaViewer3D(QString name); 
  ~AlascaViewer3D(){};

  virtual void stopActivity(); 
  virtual void startActivity(); 
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

  // to add some items to display
  // if item exists, it is updated, item is referencing by name
  void addLayer(Layer2d layer); 
  void addLine(Line2d line);
  void addCircle(Circle2d circle);
  void addEllipse(Ellipse2d ellipse);
  void addText(Text2d text);

  // to remove some items from the display
  void removeLayer(QString name);
  void removeLine(QString name);
  void removeCircle(QString name);
  void removeEllipse(QString name);
  void removeText(QString name);

	// to remove All items of a particular type from the display
	void removeAllEllipses();
	void removeAllTexts();

  inline GLWidget * getQGLWidget() {return glArea_;}

public slots:
  // faire les appels opengl et mesurer le temps
  void refresh();

protected:
  void keyPressEvent ( QKeyEvent * event ) {glArea_->keyPressEvent(event);}

private:
  GLWidget *glArea_;

  QList<Line2d> lines_;
  QList<Ellipse2d> ellipses_;
  QList<Circle2d> circles_;
  QList<Layer2d> layers_;


	QMutex listLock_;

  road_time_t tic_;  
  void tic() { tic_ = road_time(); }
  void toc(char * text) { printf("duration = %d %s\n", (int)(road_time() - tic_), text ); }

};


#endif // __ALASCAVIEWER3D_H__
