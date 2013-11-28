/*********************************************************************
//  created:    2007/11/08 - 16:45
//  filename:   Plot2D.h
//
//  author:     Gerald Dherbomez
// 
//  version:    $Id: $
//
//  purpose:    
*********************************************************************/

#include <QApplication>
#include <QString>
#include <QMap>

#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_plot_curve.h>
#include <Qwt/qwt_plot_item.h>


class Ellipse : public QwtPlotItem
{
public:
  Ellipse() {}
  Ellipse(double width, double heigth, double x, double y) {}
  ~Ellipse() {}

private:
  double width_; 
  double heigth_;
  double x_; 
  double y_;
};


class CurveData 
{
public:
  CurveData(long length)
  {
    x = new double[length]; 
    memset(x,0,length); 
    y = new double[length];  
    memset(y,0,length); 
    maxLen = 0; 
    currentLen = 0;
  }; 
  CurveData(){}; 
  ~CurveData(){}; 
  QwtPlotCurve * curve; 
  double * x; 
  double * y; 
  int maxLen;
  int currentLen;
};


typedef QMap<QString,CurveData> CurveList; 


class Plot2D : public QWidget
{
public:
  Plot2D(); 
  ~Plot2D(); 

//protected:
  QwtPlot * plot; 
  QwtPlotCurve * addCurve(QString name, long length, const QColor color); 
  QwtPlotCurve * addCurve(QString name, long length, const QColor color, int r); 

  bool removeCurve(QString name); 
  bool updateCurve(QString curveName, double * x, double * y, int size); 
  bool updateCurve(QString curveName, double * x, double * y, double * r, int size);

  QwtPlotCurve * getCurve(QString name); 

  double xMin_; 
  double xMax_; 
  double yMin_; 
  double yMax_;  
protected:
  CurveList curveList_;

};
