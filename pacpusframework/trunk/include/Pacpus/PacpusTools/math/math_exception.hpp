// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Firstname Surname <firstname.surname@utc.fr>
/// @date    Month, Year
/// @version $Id: math_exception.hpp 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef PACPUS_MATH_EXCEPTION_HPP
#define PACPUS_MATH_EXCEPTION_HPP

namespace math {

/*!
* \class math_error
* \brief This class describes the math exception
*/
class math_error
    : public std::logic_error
{
  public:
    /*!
     * \brief Constructor
     * \param  what_arg : a string describing the math problem
     */
    math_error (const std::string& what_arg) : logic_error( what_arg) {}
 };

} // namespace math

#endif // PACPUS_MATH_EXCEPTION_HPP
