// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Firstname Surname <firstname.surname@utc.fr>
/// @date    Month, Year
/// @version $Id: PacpusPluginInterface.h 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_PACPUS_PLUGININTERFACE_H
#define DEF_PACPUS_PLUGININTERFACE_H

#include <QObject>

/** PacpusPluginInterface
 * @brief Base class of a Pacpus plugin.
 */
class PacpusPluginInterface
{
public:
  /** Dtor of PacpusPluginInterface. */
  virtual ~PacpusPluginInterface(){} 
  
  /** Name of the plugin. */
  virtual QString name() = 0;
};

Q_DECLARE_INTERFACE(PacpusPluginInterface, "pacpus.ComponentBaseInterface/1.0")

#endif // DEF_PACPUS_PLUGININTERFACE_H
