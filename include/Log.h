//
//  Log.h
//  Utils
//
//  Created by Alessandro Saccoia on 9/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Log_hpp_
#define Log_hpp_

#include <cstdio>
#include <cstdarg>
#include <fstream>

#if 1
  #define COUNT_PARMS2(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _, ...) _
  #define COUNT_PARMS(...)\
	COUNT_PARMS2(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

  // ------------ GEEK MODE OFF -> nice stuff follows. - I actually ended up not using it :D -

  // this is how Gcc treats variable argument macro...
  // ISO C99
  #if __GNUC__
  #define dmaf_log(level,...)  do {} while(0)
  #define dmaf_log_int(level,fl,ln,...) do {} while(0)
  #endif
#else
  // this should be a NOP
  #define dmaf_log(level, format, ...) ado { } while ( false )
#endif

#if !defined(NDEBUG)
  #define dm_debug_log(logObject,level, ...) logObject->Write(level,__FILE__,__LINE__,__VA_ARGS__);
  #define dm_dmaf_log_debug(logObject,level, ...) logObject.Write(level,__FILE__,__LINE__,__VA_ARGS__);
  #define dmaf_dsp_log(logObject,level, ...) do {} while(0);
#else
  #define dm_debug_log(logObject,level, ...) do {} while(0)
//  #define dmaf_log_debug(logObject,...) do {} while(0)
  #define dmaf_log_debug_ptr(logObject,...) do {} while(0)
  #define dmaf_dsp_log(logObject,level, ...) do {} while(0)
#endif


namespace dinahmoe {
struct Log
{
public:
  Log();
  enum LogLevel { All=0, Debug, Info, Warning, Error, Fatal, None };
  void SetWriteToFile(const char* filePath);
  void SetWall(bool toggle_) { m_wall = toggle_; }
  void Write(LogLevel nLevel, const char *file_, int line_, const char *szFormat, ...);
  void SetLevel(LogLevel nLevel);
  void PrintFileInfo(bool doPrint_);
  void PrintCurrentTime(bool doPrint_);
  void Deinitialize();
protected:
  void CheckInit();
  void Init();
  void PlatformInit();
private:
  // this is the platform specific method, see the implementation file
  void PlatformWrite(LogLevel nLevel, const char *szFormat, const char *file_, int line_, va_list args);
  static LogLevel  s_defaultLevel;
  bool m_isInitialised;
  LogLevel  m_degubLevel;
  bool m_printFileInfo;
  bool m_printCurrentTime;
  std::ofstream m_logfile;
  bool m_wall;
};


} // Dinahmoe

#endif
