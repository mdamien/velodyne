#include "Curve.h"

Curve::Curve()
{
    name_ = "Curve";
    Color_ = 0;
    min_ = 0.0;
    max_ = 0.0;
    minUser_ = min_;
    maxUser_ = max_;
    xLabel_ = "X";
    yLabel_ = "Y";
    zLabel_ = "Z";
}

Curve::Curve(QString name)
{
    name_ = name;
    Color_ = 0;
    min_ = 0.0;
    max_ = 0.0;
    minUser_ = min_;
    maxUser_ = max_;
    xLabel_ = "X";
    yLabel_ = "Y";
    zLabel_ = "Z";
}

void Curve::AddPoint(QVector3D data)
{
    data_.append(data);
}

Curve::~Curve()
{
}

double Curve::getX()
{
    return data_.last().x();
}

double Curve::getY()
{
    return data_.last().y();
}

double Curve::getZ()
{
    return data_.last().z();
}
