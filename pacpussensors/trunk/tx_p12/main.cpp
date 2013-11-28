/**
@file
Purpose: CLD_Demo

@date created 2009-11-03 16:13
@version $Id: $
@author Julien Moras
*/

#include <boost/shared_ptr.hpp>
#ifndef WIN32
#   include <log4cxx/basicconfigurator.h>
#endif // WIN32
#include <qapplication.h>

#include "kernel/ComponentFactory.h"
#include "kernel/ComponentManager.h"
#include "kernel/Log.h"
#include "ComputingComponent.h"

using namespace pacpus;

// ================================================================================
using ::boost::shared_ptr;

// ================================================================================
DECLARE_STATIC_LOGGER("pacpus.cityvip.VelodynePCLViewer");

#ifdef NDEBUG
static const QString kDefaultXmlConfigFilePath = "XML/VelodynePCLViewer.xml";
#else
static const QString kDefaultXmlConfigFilePath = "XML/VelodynePCLViewer_d.xml";
#endif

// ================================================================================
int main(int argc, char * argv[])
{
#ifndef WIN32
    // configure logging facility
    ::log4cxx::BasicConfigurator::configure();
#   ifdef NDEBUG
    ::log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getInfo());
#   else
    ::log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getDebug());
#   endif
#endif // WIN32

    // ================================================================================
    QApplication app(argc, argv);
    shared_ptr<ComponentManager> mgr(ComponentManager::getInstance(), ComponentManager::destroyer());

    QString configFilePath;
    if (argc > 1) {
        configFilePath = argv[1];
    } else {
        LOG_WARN("no XML config file specified. Using default: " << kDefaultXmlConfigFilePath);
        configFilePath = kDefaultXmlConfigFilePath;
    }
    LOG_INFO("loading file '" << configFilePath << "'");
    mgr->loadComponents(configFilePath);

    // start components
    mgr->start("computingComponent");
    mgr->start("velodyneInterface");

    // save application exit status
    int exitStatus = app.exec();

    // stop all components before exiting app
    mgr->stop();

    // return application exit status
    return exitStatus;
}
