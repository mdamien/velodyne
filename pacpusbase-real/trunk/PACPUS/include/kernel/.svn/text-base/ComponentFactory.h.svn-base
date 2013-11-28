/********************************************************************
//  created:    2006/02/14 - 15:39
//  filename:   ComponentFactory.h
//
//  author:     Gerald Dherbomez
//
//  purpose:    Template class ComponentFactory.
//              Use it to interface your components with the application
*********************************************************************/

#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <qstring.h>

#include "ComponentFactoryBase.h"
#include "kernel/Log.h"

template <typename T>
class ComponentFactory
        : public ComponentFactoryBase
{
public:
    ComponentFactory(QString type);
    virtual ~ComponentFactory();

    const QString & getType() const;

protected:
    virtual ComponentBase * instantiateComponent(const QString & name);

private:
    QString mType;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
ComponentFactory<T>::ComponentFactory(QString type)
    : mType(type)
{
#ifdef WIN32
	LOG_DEBUG("constructor<" << mType << ">");
#else // WIN32
    LOG4CXX_DEBUG(::log4cxx::Logger::getLogger("pacpus.core.ComponentFactory"),
                  "constructor<" << mType << ">"
                  );
#endif // WIN32

	addFactory(this, mType);

#ifdef WIN32
	LOG_INFO("created factory for component type '" << mType << "'");
#else // WIN32
    LOG4CXX_INFO(::log4cxx::Logger::getLogger("pacpus.core.ComponentFactory"),
                 "created factory for component type '" << mType << "'"
                 );
#endif // WIN32
}

template<typename T>
ComponentFactory<T>::~ComponentFactory()
{
#ifdef WIN32
	LOG_TRACE("destructor<" << mType << ">");
#else // WIN32
    LOG4CXX_TRACE(::log4cxx::Logger::getLogger("pacpus.core.ComponentFactory"),
                  "destructor<" << mType << ">"
                  );
#endif // WIN32
}

template <typename T>
const QString & ComponentFactory<T>::getType() const
{
    return mType;
}

template<typename T>
ComponentBase * ComponentFactory<T>::instantiateComponent(const QString & name)
{
    T * component = new T(name);
    return component;
}

#endif // COMPONENTFACTORY_H
