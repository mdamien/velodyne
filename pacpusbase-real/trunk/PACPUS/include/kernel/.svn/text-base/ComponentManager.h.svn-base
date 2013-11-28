/*********************************************************************
// created:     2006/02/07 - 11:20
// filename:    componentManager.h
//
// author:      Gerald Dherbomez
//
// purpose:     This class records the components and manages them
//              This class is a singleton
//              Use the static ComponentManager::create() function
//              to get a pointer on this object.
*********************************************************************/

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <qmap.h>
#include <qlist.h>
#include <qpluginloader.h>

#include "pacpus.h"
#include "ComponentFactoryBase.h"
#include "kernel/PacpusPluginInterface.h"
#include "XmlConfigFile.h"

class ComponentBase;
//class ComponentFactoryBase;

typedef QMap<QString, ComponentBase *> ComponentMap;
typedef QMap<QString, ComponentFactoryBase *> FactoryMap;

class ComponentManager
{
    friend class ComponentBase;

public:
    // Return a pointer to the ComponentManager object
    static PACPUSLIB_API ComponentManager * create();

    // Kill the ComponentManager object
    static PACPUSLIB_API void destroy();

    struct destroyer {
        void operator()(ComponentManager * mgr) const
        {
            if (NULL == mgr) {
                return;
            }
            mgr->destroy();
        }
    };

    // Call this function to load the components included in the XML config file
    // Usually, this is done in the main() !
    ::std::size_t PACPUSLIB_API loadComponents(QString file);

    // Start all the components
    int PACPUSLIB_API start();

    // Start only the component passed in parameter
    int PACPUSLIB_API start(QString component);

    // Stop all the components
    int PACPUSLIB_API stop();

    // Stop only the component passed in parameter
    int PACPUSLIB_API stop(QString component);

    // Get a pointer to the component referred by 'name' parameter
    PACPUSLIB_API ComponentBase* getComponent(QString name);

    // Get the list of all the names of the component known by the manager
    PACPUSLIB_API QStringList getAllComponentsName();

    // Load a new plugin from the file filename (it may be a .so/.dll file)
    bool PACPUSLIB_API loadPlugin(QString filename);

protected:

private:
    // Create a new component of type 'type' and with the name 'name'
    bool createComponent(QString type, QString name);

    bool registerComponent(ComponentBase * addr, QString name);
    bool registerComponentFactory(ComponentFactoryBase * addr, QString type);

    bool unRegisterComponent(QString name);
    bool unRegisterComponentFactory(QString type);

    // Allow 2 functions to access to private members of ComponentManager
    friend void ComponentFactoryBase::addFactory(ComponentFactoryBase * addr, const QString & type);
    friend void ComponentFactoryBase::addComponent(const QString & name);

    // private constructor accessible only via static create() function

    ComponentManager();

    // private destructor accessible only via static destroy() function
    ~ComponentManager();

private:
    // The static pointer to this object (ComponentManager is a singleton)
    static ComponentManager * mInstance;

    // The map of available factories of component
    FactoryMap factoryMap_;

    // The map of loaded components
    ComponentMap componentMap_;

    // a pointer on the xml interface
    XmlConfigFile * xmlTree_;

    // a list of QObject in which plugins are embedded
    QObjectList pluginList_;

    // The object used to load the plugins
    QPluginLoader pluginLoader_;
};

#endif // COMPONENTMANAGER_H
