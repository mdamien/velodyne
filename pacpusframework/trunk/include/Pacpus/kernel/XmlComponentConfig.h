// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    January, 2006
/// @version $Id: XmlComponentConfig.h 116 2013-06-25 11:44:25Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Purpose:    This class manages a XML node corresponding to a PACPUS component.

#ifndef DEF_PACPUS_XMLCOMPONENTCONFIG_H
#define DEF_PACPUS_XMLCOMPONENTCONFIG_H

#include <Pacpus/kernel/PacpusLibConfig.h>

#include <QDomElement>

namespace pacpus {
    
class XmlConfigFile;

/// XmlComponentConfig
/// @brief Defines the XML structure of a component.
class PACPUSLIB_API XmlComponentConfig
{
    friend class ComponentManager;

public:
    /// Ctor of XmlComponentConfig.
    /// @param name Name of the ComponentFactory, by convention equal to class name.
    explicit XmlComponentConfig(const QString & name = QString::null);

    /// Dtor of XmlComponentConfig.
    ~XmlComponentConfig();

    /// Adds the property @em name to the XML and set its value to @em 0 if it does not exist.
    /// @param name Name of the property.
    void addProperty(const QString& name);

    /// Deletes property @em name from the XML.
    /// 
    /// @returns @b true if the property existed and was removed, @b false if the property did not exist or could not be removed.
    int delProperty(const QString& name);

    /// Gets the value of a property.
    /// @param name Name of the property.
    /// @param defaultValue Value returned if the property does not exist.
    /// @return Value of the property, @em defaultValue otherwise.
    QString getProperty(const QString& name, const QString& defaultValue = QString::null) const;

    /// Gets the value of a property as a boolean.
    /// @param name Name of the property.
    /// @param defaultValue Value returned if the property does not exist.
    /// @returns Value of the property, @em defaultValue otherwise.
    bool getBoolProperty(const QString& name, bool defaultValue = false) const;

    /// Get the value of a property as an integer.
    /// @param name Name of the property.
    /// @param defaultValue Value returned if the property does not exist.
    /// @return Value of the property, @em defaultValue otherwise.
    int getIntProperty(const QString& name, int defaultValue = 0) const;

    /// Get the value of a property as a double.
    /// @param name Name of the property.
    /// @param defaultValue Value returned if the property does not exist.
    /// @return Value of the property, @em defaultValue otherwise.
    double getDoubleProperty(const QString& name, double defaultValue = 0.0) const;

    /// Set the value of a property.
    /// @param name Name of the property.
    /// @param value Value to set.
    void setProperty(const QString& name, const QString& value);

    /// Check if a property exists.
    /// @param name Name of the property.
    /// @return True if the property exists, false otherwise.
    bool hasProperty(const QString& name) const;

private:
    // Returns the local QDomElement.
    QDomElement qDomElement() const;

    // Copy internally the node in the internal QDomElement. 
    void localCopy(const QDomElement& elementToCopy);

    QString const getComponentName() const;
    QString const getComponentType() const;

private:
    QDomElement component_;
    XmlConfigFile * parentDocument_;
};

} // namespace pacpus

#endif // DEF_PACPUS_XMLCOMPONENTCONFIG_H
