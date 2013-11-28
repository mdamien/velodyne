// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @version    $Id$

#include <Pacpus/kernel/PacpusException.h>

using namespace pacpus;

PacpusException::PacpusException(const std::string & what)
    : mWhat(what)
{
}

PacpusException::~PacpusException() throw()
{
}

const char * PacpusException::what() const throw()
{
    return mWhat.c_str();
}
