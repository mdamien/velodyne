// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @version    $Id: DbiteException.cpp 116 2013-06-25 11:44:25Z kurdejma $

#include <Pacpus/kernel/DbiteException.h>

using namespace pacpus;

DbiteException::DbiteException(const std::string& what)
    : PacpusException(what)
{
}

DbiteException::~DbiteException() throw()
{
}
