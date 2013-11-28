// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @version    $Id: ComponentFactoryBase.cpp 91 2013-05-19 10:32:48Z gdherbom $

#include <Pacpus/kernel/ComponentFactoryBase.h>
#include <Pacpus/kernel/ComponentBase.h>
#include <Pacpus/kernel/ComponentManager.h>
#include <Pacpus/kernel/Log.h>

#include <cassert>
#include <QString>

using namespace pacpus;

DECLARE_STATIC_LOGGER("pacpus.core.ComponentFactoryBase");

ComponentFactoryBase::ComponentFactoryBase()
    : mgr_(NULL)
{
    LOG_TRACE("constructor");
    // get the adress of the ComponentManager instance
    mgr_ = ComponentManager::getInstance();
}

ComponentFactoryBase::~ComponentFactoryBase()
{
    LOG_TRACE("destructor");
}

void ComponentFactoryBase::addFactory(ComponentFactoryBase* addr, const QString& type)
{
    LOG_DEBUG("addFactory(type="<< type << ")");

    assert(mgr_);
    if (!mgr_->registerComponentFactory(addr, type)) {
        /*
        // FIXME: delete in a secure manner (no double delete)
        delete addr;
        addr = NULL;
        */
    }
}

void ComponentFactoryBase::addComponent(const QString& name)
{
    LOG_DEBUG("addComponent(" << name << ")");

    // FIXME: instantiated component is never deleted!
    // who should do it? ComponentManager?
    ComponentBase * addr = instantiateComponent(name);
    assert(mgr_);
    if (!mgr_->registerComponent(addr, name)) {
        delete addr;
        addr = NULL;
    }
}
