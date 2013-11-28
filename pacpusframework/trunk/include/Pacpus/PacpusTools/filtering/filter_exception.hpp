// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Firstname Surname <firstname.surname@utc.fr>
/// @date    Month, Year
/// @version $Id: filter_exception.hpp 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef __FILTERING_EXECPTION_HPP__
#define __FILTERING_EXECPTION_HPP__

#include <stdexcept>

namespace filter {

   /*!
    *  \class filter_error
    *  \brief This class describes the filtering exception
    */ 
   class filter_error : public std::logic_error
   {
    public: 
        /*!
         * \brief Construtor 
         */
        filter_error (const std::string& what_arg) : logic_error( what_arg) {}
   };

} // namespace filter

#endif // __FILTERING_EXECPTION_HPP__
