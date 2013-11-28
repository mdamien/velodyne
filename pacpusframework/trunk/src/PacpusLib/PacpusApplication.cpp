// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @date    March, 2013
/// @version $Id$
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.

#include <Pacpus/kernel/Log.h>
#include <Pacpus/kernel/PacpusApplication.h>
#include <Pacpus/kernel/PacpusException.h>

using namespace pacpus;

DECLARE_STATIC_LOGGER("pacpus.core.PacpusApplication");

PacpusApplication::PacpusApplication(int & argc, char ** argv
#ifndef Q_QDOC
                                   , int _internal
#endif
                                   )
    : QApplication(argc, argv, _internal)
{
}

PacpusApplication::PacpusApplication(int & argc, char ** argv, bool GUIenabled
#ifndef Q_QDOC
                                   , int _internal
#endif
                                   )
    : QApplication(argc, argv, GUIenabled, _internal)
{
}

PacpusApplication::PacpusApplication(int & argc, char ** argv, Type type
#ifndef Q_QDOC
                                   , int _internal
#endif
                                   )
    : QApplication(argc, argv, type, _internal)
{
}

#if defined(Q_WS_X11)
PacpusApplication::PacpusApplication(Display * display, Qt::HANDLE visual, Qt::HANDLE colormap
#ifndef Q_QDOC
                                   , int _internal
#endif
                                   )
    : QApplication(display, visual, colormap, _internal)
{
}

PacpusApplication::PacpusApplication(Display * display, int & argc, char ** argv, Qt::HANDLE visual , Qt::HANDLE colormap
#ifndef Q_QDOC
                                   , int _internal
#endif
                                   )
    : QApplication(display, argc, argv, visual, colormap, _internal)
{
}
#endif

#if defined(Q_OS_SYMBIAN)
PacpusApplication::PacpusApplication(QApplication::QS60MainApplicationFactory factory, int & argc, char ** argv
#ifndef Q_QDOC
                                   , int _internal
#endif
                                   )
    : QApplication(factory, argc, argv, _internal)
{
}
#endif

PacpusApplication::~PacpusApplication()
{
}

bool PacpusApplication::notify(QObject * receiver, QEvent * ev)
{
    try {
        return QApplication::notify(receiver, ev);
    } catch(PacpusException & e) {
        LOG_ERROR("PacpusException thrown:" << e.what());
    } catch(std::exception & e) {
        LOG_ERROR("std::exception thrown:" << e.what());
    }
    return false;
}
