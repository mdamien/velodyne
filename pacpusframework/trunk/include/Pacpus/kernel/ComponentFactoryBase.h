// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    February, 2006
/// @version $Id: ComponentFactoryBase.h 116 2013-06-25 11:44:25Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Purpose:    The ComponentFactoryBase class is used to provide an 
///             abstract class to the template ComponentFactory

#ifndef DEF_PACPUS_COMPONENTFACTORYBASE_H
#define DEF_PACPUS_COMPONENTFACTORYBASE_H

#include <Pacpus/kernel/PacpusLibConfig.h>

class QString;

namespace pacpus {

class ComponentManager;
class ComponentBase;

/// ComponentFactoryBase
/// @brief Provide an abstract class to the template ComponentFactory.
class PACPUSLIB_API ComponentFactoryBase
{
    friend class ComponentManager;

public:
    /// Ctor of ComponentFactoryBase.
    ComponentFactoryBase();
    /// Dtor of ComponentFactoryBase.
    virtual ~ComponentFactoryBase();

protected:
    /// Creates a new component having @em name as component name.
    /// Caller becomes the owner of its lifetime
    ///
    /// @param name Name of the instantiated component.
    /// @returns Pointer on the newly created component.
    virtual ComponentBase * instantiateComponent(const QString& name) = 0;
    
    /// Registers a new factory.
    ///
    /// @param addr Address of the factory.
    /// @param type Name of the type created by the factory.
    void addFactory(ComponentFactoryBase* addr, const QString& type);
    
    /// Adds a new component.
    ///
    /// @param name Name of the new component.
    void addComponent(const QString& name);

private:
    ComponentManager* mgr_;
};

} // namespace pacpus

#endif