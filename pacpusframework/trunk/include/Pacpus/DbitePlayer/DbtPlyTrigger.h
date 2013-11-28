// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    April, 2007
/// @version $Id: DbtPlyTrigger.h 91 2013-05-19 10:32:48Z gdherbom $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief DbitePlayer trigger.
///
/// Detailed description.

#ifndef DEF_PACPUS_DBTPLYTRIGGER_H
#define DEF_PACPUS_DBTPLYTRIGGER_H

#include <QThread>

#include <Pacpus/DbitePlayer/DbitePlayerConfig.h>
#include <Pacpus/DbitePlayer/DbtPlyEngine.h>
#include <Pacpus/kernel/ComponentBase.h>
#include <Pacpus/kernel/ComponentFactory.h>

#ifdef WIN32
#   include <windows.h>
#   include <mmsystem.h>
#endif

namespace pacpus {

class DbtPlyEngine;

class DBITE_PLAYER_API DbtPlyTrigger
        : public QThread
        , public ComponentBase
{    
    Q_OBJECT

public:
    /// @todo Documentation
    DbtPlyTrigger(QString name);
    /// @todo Documentation
    virtual ~DbtPlyTrigger();

    /// @todo Documentation
    virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

    /// @todo Documentation
    virtual void run();

Q_SIGNALS:
    /// @todo Documentation
    void triggerSig();

protected:
    /// @todo Documentation
    virtual void startActivity();
    /// @todo Documentation
    virtual void stopActivity();

private:
    DbtPlyEngine * mEngine;
};

} // namespace pacpus

#endif // DEF_PACPUS_DBTPLYTRIGGER_H
