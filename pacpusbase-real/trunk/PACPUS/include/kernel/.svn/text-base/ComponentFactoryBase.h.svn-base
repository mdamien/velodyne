/********************************************************************
//  created:    2006/02/14 - 16:08
//  filename:   ComponentFactoryBase.h
//
//  author:     Gerald Dherbomez
//
//  purpose:    The ComponentFactoryBase class is used to provide an 
//              abstract class to the template ComponentFactory
*********************************************************************/

#ifndef COMPONENTFACTORYBASE_H
#define COMPONENTFACTORYBASE_H

#include "pacpus.h"

class ComponentManager;
class ComponentBase;
class QString;

class PACPUSLIB_API ComponentFactoryBase
{
    friend class ComponentManager;

public:
    ComponentFactoryBase();
    virtual ~ComponentFactoryBase();

protected:
    virtual ComponentBase * instantiateComponent(const QString & name) = 0;
    void addFactory(ComponentFactoryBase * addr, const QString & type);
    void addComponent(const QString & name);

private:
    ComponentManager * mgr_;
};

#endif // COMPONENTFACTORYBASE_H
