// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @date    June, 2013
/// @version $Id$
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_PACPUS_PACPUSEXCEPTION_H
#define DEF_PACPUS_PACPUSEXCEPTION_H

#include <Pacpus/kernel/PacpusLibConfig.h>

//#include <boost/exception/exception.hpp>
#include <exception>
#include <string>

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable: 4251)
#endif // _MSC_VER

namespace pacpus {

/// Base class for all exceptions in the framework
class PACPUSLIB_API PacpusException
    : virtual public std::exception
    //, virtual public boost::exception
{
public:
    /// Ctor.
    /// @param what Information about the exception.
    PacpusException(const std::string & what);

    /// Dtor.
    virtual ~PacpusException() throw();

    /// Gets more information about the error.
    ///
    /// @returns Message containing information about the error.
    virtual const char * what() const throw();

protected:
    std::string mWhat;
};

} // namespace pacpus

#ifdef _MSC_VER
#   pragma warning(pop)
#endif // _MSC_VER

#endif // DEF_PACPUS_PACPUSEXCEPTION_H
