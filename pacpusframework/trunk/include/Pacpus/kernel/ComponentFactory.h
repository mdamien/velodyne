// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    February, 2006
/// @version $Id: ComponentFactory.h 117 2013-06-25 11:50:46Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Purpose:    Template class ComponentFactory.
///             Use it to interface your components with the application.

#ifndef DEF_PACPUS_COMPONENTFACTORY_H
#define DEF_PACPUS_COMPONENTFACTORY_H

#include <cassert>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <Pacpus/kernel/ComponentFactoryBase.h>

#include <QString>

/// @def REGISTER_COMPONENT(className, factoryName)
/// Registers a component to the factory.
///
/// @param className     Name of the class, without the quotes.
/// @param factoryName   Name of the class in the factory.
/// @example
/// ~~~
///     REGISTER_COMPONENT("DummyComponent", DummyComponent);
/// ~~~
/// @see pacpus::ComponentFactory
#define REGISTER_COMPONENT(className, factoryName) \
    static pacpus::ComponentFactory<className> sFactory(factoryName)

namespace pacpus {

/// Use it to interface your components with the application.
///
/// @tparam T   Component class
/// @see #REGISTER_COMPONENT(className, factoryName)
template <typename T>
class ComponentFactory
    : public ComponentFactoryBase
{
    BOOST_STATIC_ASSERT_MSG((boost::is_base_of<ComponentBase, T>::value), "T must inherit from ComponentBase");

public:
    /// Ctor of ComponentFactory, initialize the factory of the components of type @em T.
    /// @param type Name of the type of the components.
    ComponentFactory(const QString & type);

    /// Dtor of ComponentFactory.
    virtual ~ComponentFactory();

    /// Gets the name of the type of the components.
    /// @returns Name of the type of the components.
    const QString & getType() const;

protected:
    virtual ComponentBase * instantiateComponent(const QString& name);

private:
    QString mType;
};

template <typename T>
ComponentFactory<T>::ComponentFactory(const QString& type)
    : mType(type)
{
    assert(!type.isEmpty());
    addFactory(this, mType);
}

template<typename T>
ComponentFactory<T>::~ComponentFactory()
{
}

template <typename T>
const QString& ComponentFactory<T>::getType() const
{
    return mType;
}

template<typename T>
ComponentBase * ComponentFactory<T>::instantiateComponent(const QString & name)
{
    return new T(name);
}

} // namespace pacpus

#endif // DEF_PACPUS_COMPONENTFACTORY_H
