#ifndef LOGGER_H_INCLUDE
#define LOGGER_H_INCLUDE

#include <iostream>

#if !defined(LEVEL_DEBUG) && !defined(LEVEL_INFO) && !defined(LEVEL_WARN) && !defined(LEVEL_ERROR)
#define LEVEL_ERROR
#endif

#if defined(LEVEL_DEBUG)
#define LDBUG( args ) INTERNAL_DEBUG(args)
#define LINFO( args ) INTERNAL_INFO(args)
#define LWARN( args ) INTERNAL_WARN(args)
#define LEROR( args ) INTERNAL_ERROR(args)
#endif

#if defined(LEVEL_INFO) && !defined(LEVEL_DEBUG)
#define LDBUG( args ) 
#define LINFO( args ) INTERNAL_INFO(args)
#define LWARN( args ) INTERNAL_WARN(args)
#define LEROR( args ) INTERNAL_ERROR(args)
#endif

#if defined(LEVEL_WARN) && !defined(LEVEL_DEBUG) && !defined(LEVEL_INFO)
#define LDBUG( args ) 
#define LINFO( args ) 
#define LWARN( args )  INTERNAL_WARN(args)
#define LEROR( args ) INTERNAL_ERROR(args)
#endif

#if defined(LEVEL_ERROR) && !defined(LEVEL_DEBUG) && !defined(LEVEL_INFO) && !defined(LEVEL_WARN)
#define LDBUG( args ) 
#define LINFO( args ) 
#define LWARN( args ) 
#define LEROR( args ) INTERNAL_ERROR(args)
#endif

#define INTERNAL_DEBUG( message ) logger::log(logger::flag::debug, message)
#define INTERNAL_INFO( message )  logger::log(logger::flag::info, message)
#define INTERNAL_WARN( message )  logger::log(logger::flag::warn, message)
#define INTERNAL_ERROR( message ) logger::log(logger::flag::error, message)

namespace logger
{
  enum flag : unsigned short
  {
    error = 0,
    warn,
    info,
    debug
  };

  void log(int flag, const std::string& message);

  void set_program_name(const std::string&);
  const std::string& get_program_name();
}

#endif /* LOGGER_H_INCLUDE */