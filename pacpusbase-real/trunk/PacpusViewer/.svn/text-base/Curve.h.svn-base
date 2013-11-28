#ifndef _CURVE_H_
#define _CURVE_H_

#include <QString>
#include <QVector>
#include <QVector3D>
#include <QRgb>

class Curve
{
public:
    Curve();
    Curve(QString name);
    ~Curve();
    void AddPoint(QVector3D data);
    QString name() {return name_;};
    double getX();
    double getY();
    double getZ();

private:
    QString name_;
    QVector<QVector3D> data_;
    QRgb Color_;
    double min_;
    double max_;
    double minUser_;
    double maxUser_;
    QString xLabel_;
    QString yLabel_;
    QString zLabel_;
};
#endif
