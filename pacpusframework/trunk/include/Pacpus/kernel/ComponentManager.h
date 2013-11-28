// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    January, 2006
/// @version $Id: ComponentManager.h 116 2013-06-25 11:44:25Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Purpose:     This class records the components and manages them
///              This class is a singleton
///              Use the static ComponentManager::create() function
///              to get a pointer on this object.

#ifndef DEF_PACPUS_COMPONENTMANAGER_H
#define DEF_PACPUS_COMPONENTMANAGER_H

#include <Pacpus/kernel/ComponentFactoryBase.h>
#include <Pacpus/kernel/pacpus.h>
#include <Pacpus/kernel/PacpusLibConfig.h>
#include <Pacpus/kernel/PacpusPluginInterface.h>
#include <Pacpus/kernel/XmlConfigFile.h>

#include <cstddef>
#include <QList>
#include <QMap>
#include <QPluginLoader>

namespace pacpus {

class ComponentBase;

/// @todo Documentation
typedef QMap<QString, ComponentBase *> ComponentMap;
/// @todo Documentation
typedef QMap<QString, ComponentFactoryBase *> FactoryMap;

/// Singleton recording the components and managing them.
class ComponentManager
{
    friend class ComponentBase;

    // Allow 2 functions to access to private members of ComponentManager
    friend void ComponentFactoryBase::addFactory(ComponentFactoryBase * addr, const QString & type);
    friend void ComponentFactoryBase::addComponent(const QString & name);

public:
    /// @returns a pointer to the ComponentManager object
    /// @deprecated Use getInstance()
    PACPUS_DEPRECATED_MSG( static PACPUSLIB_API ComponentManager * create(), "use 'getInstance()'" );

    /// Returns an instance of the singleton ComponentManager class.
    /// @returns Pointer to the ComponentManager singleton.
    static PACPUSLIB_API ComponentManager* getInstance();

    /// Destroys the ComponentManager singleton.
    ///
    /// After this call, every pointer to the ComponentManager becomes invalid.
    static PACPUSLIB_API void destroy();

    /// Automatic deleter class.
    struct destroyer {
        /// Invokes ComponentManager::destroy() method if @b mgr pointer is not null.
        void operator()(ComponentManager * mgr) const
        {
            if (!mgr) {
                return;
            }
            mgr->destroy();
        }
    };

    /// Loads the components included in the XML config file.
    /// @param file Name of the XML file.
    /// @returns Number of components loaded by the manager.
    PACPUSLIB_API std::size_t loadComponents(const QString& file);

    /// Starts all the components
    /// @return @b true if all the component has been started, @b false otherwise.
    PACPUSLIB_API bool start();

    /// Starts only the component passed in parameter.
    /// @param component Component to start.
    /// @returns @b true if the component exists and has been started, @b false otherwise.
    PACPUSLIB_API bool start(const QString& component);

    /// Stops all the components
    /// @returns @b true if all the component has been stopped, @b false otherwise.
    PACPUSLIB_API bool stop();

    /// Stops only the component passed in parameter.
    /// @param component Component to stop.
    /// @returns @b true if the component has been stopped, @b false otherwise.
    PACPUSLIB_API bool stop(const QString& component);

    /// Gets a pointer to the component referred by @em name.
    ///
    /// @param name Name of the component.
    /// @returns Pointer to the component if it exists, @b NULL otherwise.
    PACPUSLIB_API ComponentBase* getComponent(const QString& name);

    /// Gets the list of all the names of the component known by the manager.
    /// @returns List of all the component's name.
    PACPUSLIB_API QStringList getAllComponentsName() const;

    /// Loads a new plugin from the file filename (it may be a .so/.dll file)
    /// @param filename Name of the shared object or the dll.
    /// @returns @b true if the plugin has been loaded, @b false otherwise .
    PACPUSLIB_API bool loadPlugin(const QString& filename);

private:
    /// Create a new component of type 'type' and with the name 'name'
    bool createComponent(const QString& type, const QString& name);

    bool registerComponent(ComponentBase* addr, const QString& name);
    bool registerComponentFactory(ComponentFactoryBase * addr, const QString& type);

    bool unRegisterComponent(const QString& name);
    bool unRegisterComponentFactory(const QString& type);

    /// private constructor accessible only via static create() function
    ComponentManager();

    /// private destructor accessible only via static destroy() function
    ~ComponentManager();

private:
    /// The static pointer to this object (ComponentManager is a singleton)
    static ComponentManager * mInstance;

    /// The map of available factories of component
    FactoryMap factoryMap_;

    /// The map of loaded components
    ComponentMap componentMap_;

    /// a pointer on the xml interface
    pacpus::XmlConfigFile * xmlTree_;

    /// a list of QObject in which plugins are embedded
    QObjectList pluginList_;

    /// The object used to load the plugins
    QPluginLoader pluginLoader_;
};

} // namespace pacpus

#endif
