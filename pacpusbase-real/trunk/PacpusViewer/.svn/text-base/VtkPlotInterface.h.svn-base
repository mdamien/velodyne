#ifndef VTKPLOTINTERFACE_H
#define VTKPLOTINTERFACE_H

#include "kernel/ComponentFactory.h"
#include "kernel/ComponentBase.h"

#include <QVector3D>
#include <QThread>
#include <stdio.h>
#include <iostream>
#include <QStringList>

#include <QList>

class VtkPlotViewer;
class Curve;

// Export macro to use plugin methods of the DLL (for Windows only)
// Don't forget to set the PLUGINLIB_EXPORTS in the CMakeLists.txt of the plugin
// ADD_DEFINITIONS(-DPLUGINLIB_EXPORTS) 
#ifdef WIN32
#ifdef PLUGINLIB_EXPORTS
// make DLL
#define PLUGINLIB_API __declspec(dllexport)
#else
// use DLL
#define PLUGINLIB_API __declspec(dllimport)
#endif
#else
// On other platforms, simply ignore this
#define PLUGINLIB_API
#endif

namespace pacpus {

class PLUGINLIB_API VtkPlotInterface
        : public ComponentBase
{
public:
        VtkPlotInterface(QString name);
        ~VtkPlotInterface();
        virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
        void appendData(QString key, double x, double y);
        void appendData(QString key, double x, double y, double z);
        void appendData(QString key, double *x, double *y, int size);
        void appendData(QString key, double *x, double *y, double *z, int size);
        void resetScaling();
        void updateScale();
        void removeData();
        void showLegend(bool show);
        void showGird(bool show);
        void setStyleText(QString style);
        void setSymmetric(bool symmetry);
        void setXLabel(QString name);
        void setYLabel(QString name);
        void setZLabel(QString name);
        void setType(int type);

protected:
        virtual void startActivity();
        virtual void stopActivity();

private:
        unsigned long updateDelay_;

        QList<VtkPlotViewer*> plotViewer_;
        QStringList nameKey_;
        int plotViewerFound_, curveFound_;
        QVector3D data_;
};

} // namespace pacpus

#endif // VTKPLOTINTERFACE_H
