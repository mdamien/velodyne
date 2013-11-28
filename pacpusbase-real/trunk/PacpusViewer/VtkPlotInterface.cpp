#include "VtkPlotInterface.h"

#include "kernel/Log.h"
#include "VtkPlotViewer.h"
#include "Curve.h"

namespace pacpus {

DECLARE_STATIC_LOGGER("pacpus.base.VtkPlotInterface");

static ComponentFactory<VtkPlotInterface> sFactory("VtkPlotInterface");

VtkPlotInterface::VtkPlotInterface(QString name)
    : ComponentBase(name)
{
    LOG_TRACE("constructor(" << name.toStdString() << ")");

	data_.setX(1.0);
    data_.setY(2.2);
    data_.setZ(3.3);

    LOG_DEBUG("[" << data_.x() << "," << data_.y() << "," << data_.z() << "]");

    plotViewerFound_ = 0;
    curveFound_ = 0;
    plotViewer_.append(new VtkPlotViewer("AVD_Fy"));
    plotViewer_.last()->initialize();
	
	plotViewer_.append(new VtkPlotViewer("AVD_Fx"));
    plotViewer_.last()->initialize();
	
	plotViewer_.append(new VtkPlotViewer("AVG_Fy"));
    plotViewer_.last()->initialize();
    
    plotViewer_.append(new VtkPlotViewer("AVG_Fx"));
    plotViewer_.last()->initialize();

	plotViewer_.append(new VtkPlotViewer("AVD_Fz"));
    plotViewer_.last()->initialize();

    	plotViewer_.append(new VtkPlotViewer("AVG_Fz"));
    plotViewer_.last()->initialize();

}

VtkPlotInterface::~VtkPlotInterface()
{
}

/// This function is called when the module must be configured
/// Data comes from a xml file open by dbiteplayer or sensor at startup
/// Default values are used if parameters isn't found in the xml file
/// @param config XML configuration component
/// @returns ComponentBase::CONFIGURED_FAILED if the parameter is found, but contains incorrect data; ComponentBase::CONFIGURED_OK otherwise
ComponentBase::COMPONENT_CONFIGURATION VtkPlotInterface::configureComponent(XmlComponentConfig config)
{
    bool error = false;

    QString parameter = config.getProperty("updateDelay");

    bool convOK;
    if (!parameter.isNull() && !parameter.isEmpty()) {
        updateDelay_ = parameter.toULong(&convOK);
    }
    if (!convOK) {
        LOG_WARN("cannot convert parameter 'updateDelay' to `unsigned long`");
        error = true;
    } else {
        LOG_WARN("path of velodyne correction file must be defined")
        error = true;
    }

    // FIXME: no error handling
    error = false;

	parameter = config.getProperty("XBoundsMin");
        /*Bounds_[0] = parameter.toDouble(&convOK);
	parameter = config.getProperty("XBoundsMax");
        Bounds_[1] = parameter.toDouble(&convOK);
	parameter = config.getProperty("YBoundsMin");
        Bounds_[2] = parameter.toDouble(&convOK);
	parameter = config.getProperty("YBoundsMax");
        Bounds_[3] = parameter.toDouble(&convOK);
	parameter = config.getProperty("ZBoundsMin");
        Bounds_[4] = parameter.toDouble(&convOK);
	parameter = config.getProperty("ZBoundsMax");
        Bounds_[5] = parameter.toDouble(&convOK);

        XLabel_ = config.getProperty("XLabel");
        YLabel_ = config.getProperty("YLabel");

	parameter = config.getProperty("RColor");
        Color_[0] = parameter.toDouble(&convOK);
	parameter = config.getProperty("GColor");
        Color_[1] = parameter.toDouble(&convOK);
	parameter = config.getProperty("BColor");
        Color_[2] = parameter.toDouble(&convOK);
*/
    if (error) {
        return ComponentBase::CONFIGURED_FAILED;
    } else {
        return ComponentBase::CONFIGURED_OK;
    }
}

void VtkPlotInterface::startActivity()
{
}

void VtkPlotInterface::stopActivity()
{
}

void VtkPlotInterface::appendData(QString key, double x, double y)
{
    appendData(key, x, y, 0.0);
}

void VtkPlotInterface::appendData(QString key, double *x, double *y, int size)
{
}

void VtkPlotInterface::appendData(QString key, double x, double y, double z)
{
    data_.setX(x);
    data_.setY(y);
    data_.setZ(z);

    LOG_DEBUG("[" << data_.x() << "," << data_.y() << "," << data_.z() << "]");

    plotViewerFound_ = -1;
    curveFound_ = -1;
    int i = 0, j = 0;

    nameKey_ = key.split("|");

    for (i; i < plotViewer_.size(); i++)
    {
        if (plotViewer_[i]->name() == nameKey_[0])
        {
            plotViewerFound_ = i;
            for (j; j < plotViewer_[i]->curveSize(); ++j)
            {
                if (plotViewer_[i]->curve(j)->name() == nameKey_[1])
                 {
                     curveFound_ = j;
                     plotViewer_[i]->curve(j)->AddPoint(data_);
                     plotViewer_[i]->displayData(*(plotViewer_[i]->curve(j)));
                 }
            }
        }
    }

    if (plotViewerFound_ != -1 && curveFound_ == -1)
    {
        plotViewer_[plotViewerFound_]->addCurve(Curve(nameKey_[1]));
        plotViewer_[plotViewerFound_]->curve(j)->AddPoint(data_);
        plotViewer_[plotViewerFound_]->displayData(*(plotViewer_[plotViewerFound_]->curve(j)));
    }

    if (plotViewerFound_ == -1)
    {
        // BUGGE, il est impossible de créer des fenêtres dans cette fonction car pas appelée dans le tread GUI
        plotViewer_.append(new VtkPlotViewer(nameKey_[0]));
        printf("coucou");
        plotViewer_.last()->initialize();
        plotViewer_.last()->addCurve(Curve(nameKey_[1]));
        plotViewer_.last()->curve(0)->AddPoint(data_);
        plotViewer_.last()->displayData(*(plotViewer_.last()->curve(0)));
     }
}

void VtkPlotInterface::appendData(QString key, double *x, double *y, double *z, int size)
{
}

void VtkPlotInterface::resetScaling()
{
}

void VtkPlotInterface::updateScale()
{
}

void VtkPlotInterface::removeData()
{
}

void VtkPlotInterface::showLegend(bool show)
{
}

void VtkPlotInterface::showGird(bool show)
{
}

void VtkPlotInterface::setStyleText(QString style)
{
}

void VtkPlotInterface::setSymmetric(bool symmetry)
{
}

void VtkPlotInterface::setXLabel(QString name)
{
}

void VtkPlotInterface::setYLabel(QString name)
{
}

void VtkPlotInterface::setZLabel(QString name)
{
}

void VtkPlotInterface::setType(int type)
{
}

} // namespace pacpus
