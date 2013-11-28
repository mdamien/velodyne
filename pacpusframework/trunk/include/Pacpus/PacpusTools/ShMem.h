// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    January, 2007
/// @version $Id: ShMem.h 91 2013-05-19 10:32:48Z gdherbom $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_PACPUS_SHMEM_H
#define DEF_PACPUS_SHMEM_H

#ifdef WIN32
#   include "Win32ShMem.h"
/// Defines shared memory as a Windows shared memory
#   define ShMemType Win32ShMem
#else
#   include "PosixShMem.h"
/// Defines shared memory as a POSIX shared memory
#   define ShMemType PosixShMem
#endif

namespace pacpus {

/// Shared memory class.
///
/// Inherits from Win32ShMem on Windows system and from PosixShMem on Unix-like systems.
class ShMem
    : public ShMemType
{
public:
    /// Ctor of shared memory class.
    ///
    /// Creates a shared memory of size @b size and named @b name.
    /// If a shared memory with the name @b name already exists, than
    /// it will return object pointing to the same memory.
    /// If this existing memory space has a size smaller than @b size,
    /// a warning will be issued.
    ///
    /// @param name Name of the created shared memory space.
    /// @param size Size of the created shared memory space in [bytes].
    ShMem(const char * name, int size)
        : ShMemType(name, size)
    {
    }

    /// Dtor of shared memory class.
    ///
    /// Does nothing.
    ~ShMem()
    {
    }

protected:
private:
};

} // namespace pacpus

#endif // DEF_PACPUS_SHMEM_H
