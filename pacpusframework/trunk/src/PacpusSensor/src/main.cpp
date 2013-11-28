// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @version    $Id: main.cpp 91 2013-05-19 10:32:48Z gdherbom $

#include <QApplication>

#include "ui/pacpusmainwindow.h"
#include <Pacpus/kernel/ComponentManager.h>
#include <Pacpus/kernel/Log.h>
#include <Pacpus/kernel/PacpusApplication.h>

#ifdef WIN32
#   include <windows.h>
#endif

using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.core.Sensor");

static const string kDefaultXmlConfigFilePath = "PACPUS.xml";

int main(int argc, char * argv[])
{
    PacpusApplication app(argc, argv);

    // faire une boucle pour charger tous les plugins
    // il faudrait faire une classe supplementaire integree a PacpusLib  /home/gdherbom/dev/pacpus/pacpusbase/pacpusbin/trunk/
    /*  QPluginLoader loader("libVelodyneHDL64S2.so");
    qDebug() << loader.errorString();
    qDebug() << loader.load();
    qDebug() << loader.errorString();
    QObject * plugin = loader.instance();

    qDebug() << "Loading plugin:" << qobject_cast<PacpusPluginInterface*>(plugin)->name() << "associated to file:" << loader.fileName();
    qDebug() << loader.errorString();
    */
    ComponentManager * mgr = ComponentManager::getInstance();
    LOG_DEBUG("main : " << mgr);

#ifdef WIN32
    timeBeginPeriod(1);
#endif

    string configFilePath;
    if (argc > 1) {
        configFilePath = argv[1];
    } else {
        configFilePath = kDefaultXmlConfigFilePath;
        LOG_WARN("no XML config file specified. Using default: " << configFilePath.c_str());
    }
    LOG_INFO("loading file '" << configFilePath.c_str() << "'");
    mgr->loadComponents(configFilePath.c_str());

    PacpusMainWindow window;
    window.show();

    // save application exit status
    int exitStatus = app.exec();
    // stop all components before exiting app
    mgr->stop();

    mgr->destroy();

#ifdef WIN32
    timeEndPeriod(1);
#endif 

    // return application exit status
    return exitStatus;
}
