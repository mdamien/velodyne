// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    January, 2007
/// @version $Id: PosixShMem.h 91 2013-05-19 10:32:48Z gdherbom $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_PACPUS_POSIXSHMEM_H
#define DEF_PACPUS_POSIXSHMEM_H

#include <QSharedMemory>
#include <QSystemSemaphore>

#include <Pacpus/PacpusTools/ShMemBase.h>

/// @todo Documentation
class PosixShMem
        : public ShMemBase
{
public:
    /// @todo Documentation
    PosixShMem(const char * name, int size);
    /// @todo Documentation
    virtual ~PosixShMem();

    /// @todo Documentation
    virtual void *read();
    /// @todo Documentation
    virtual void write(void *data, int size, unsigned long offset = 0);
    /// @todo Documentation
    virtual bool wait(unsigned long timeout = 0);
    /// @todo Documentation
    virtual void lockMemory();
    /// @todo Documentation
    virtual void unlockMemory();

private:
    QSystemSemaphore * event_;
    QSharedMemory * memory_;
};

#endif // DEF_PACPUS_POSIXSHMEM_H
