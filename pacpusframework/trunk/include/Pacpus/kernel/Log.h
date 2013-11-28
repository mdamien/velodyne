// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @date    March, 2012
/// @version $Id: Log.h 116 2013-06-25 11:44:25Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Logging facility.
///
/// Detailed description.

#ifndef DEF_PACPUS_LOG_H
#define DEF_PACPUS_LOG_H

#include <Pacpus/kernel/PacpusLibConfig.h>

namespace pacpus {

/// Static log facility initializer
///
/// Uses Schwarz counter (nifty counter) idiom to initialize the log before
/// other static objects that could use the log.
static class PACPUSLIB_API LogConfigurator
{
public:
    LogConfigurator();
    ~LogConfigurator();

    static void configureLoggerWithFile(const char * configFilename);
} initializer; // using Schwarz/nifty counter idiom for static initialization

} // namespace pacpus

#ifdef PACPUS_USE_LOG
  #include <log4cxx/logger.h>

  class QString;
  
  #define DECLARE_STATIC_LOGGER(name) \
    static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(name))

  // https://devel.hds.utc.fr/projects/pacpus/ticket/55
  #define LOG_TRACE(message)          do{LOG4CXX_TRACE(logger, message);} while(false)
  #define LOG_DEBUG(message)          do{LOG4CXX_DEBUG(logger, message);} while(false)
  #define LOG_INFO(message)           do{LOG4CXX_INFO(logger, message);} while(false)
  #define LOG_WARN(message)           do{LOG4CXX_WARN(logger, message);} while(false)
  #define LOG_ERROR(message)          do{LOG4CXX_ERROR(logger, message);} while(false)
  #define LOG_FATAL(message)          do{LOG4CXX_FATAL(logger, message);} while(false)

  /// Output stream ::log4cxx::helpers::CharMessageBuffer operator for QString
  PACPUSLIB_API ::log4cxx::helpers::CharMessageBuffer & operator<<(::log4cxx::helpers::CharMessageBuffer & os, const QString & s);
  /// Output stream ::log4cxx::helpers::MessageBuffer operator for QString
  PACPUSLIB_API ::log4cxx::helpers::CharMessageBuffer & operator<<(::log4cxx::helpers::MessageBuffer & os, const QString & s);

#else
  /// Declares a log4cxx logger
  ///
  /// @param name Name of the logger, displayed when logging a message.
  #define DECLARE_STATIC_LOGGER(name)
  /// Logs a message at TRACE level using default logger
  #define LOG_TRACE(message)          do{;} while(false)
  /// Logs a message at DEBUG level using default logger
  #define LOG_DEBUG(message)          do{;} while(false)
  /// Logs a message at INFO level using default logger
  #define LOG_INFO(message)           do{;} while(false)
  /// Logs a message at WARN level using default logger
  #define LOG_WARN(message)           do{;} while(false)
  /// Logs a message at ERROR level using default logger
  #define LOG_ERROR(message)          do{;} while(false)
  /// Logs a message at FATAL level using default logger
  #define LOG_FATAL(message)          do{;} while(false)
#endif // PACPUS_USE_LOG

#endif // DEF_PACPUS_LOG_H
