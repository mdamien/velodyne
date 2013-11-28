// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @date    March, 2013
/// @version $Id$
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Generic ComponentBase class. This is an abstract class.
///
/// Detailed description.

#ifndef PACPUSAPPLICATION_H
#define PACPUSAPPLICATION_H

#include <QApplication>

namespace pacpus {

class PACPUSLIB_API PacpusApplication
    : public QApplication
{
public:
#ifndef qdoc
    PacpusApplication(int &argc, char **argv, int = ApplicationFlags);
    PacpusApplication(int &argc, char **argv, bool GUIenabled, int = ApplicationFlags);
    PacpusApplication(int &argc, char **argv, Type, int = ApplicationFlags);
#if defined(Q_WS_X11)
    PacpusApplication(Display* dpy, Qt::HANDLE visual = 0, Qt::HANDLE cmap = 0, int = ApplicationFlags);
    PacpusApplication(Display *dpy, int &argc, char **argv, Qt::HANDLE visual = 0, Qt::HANDLE cmap= 0, int = ApplicationFlags);
#endif
#if defined(Q_OS_SYMBIAN)
    PacpusApplication(QApplication::QS60MainApplicationFactory factory, int &argc, char **argv, int = ApplicationFlags);
#endif
#endif

    virtual	~PacpusApplication();

    virtual bool notify(QObject * receiver, QEvent * ev);
};

} //namespace pacpus

#endif // PACPUSAPPLICATION_H
