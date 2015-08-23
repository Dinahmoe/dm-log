//
//  Log.cpp
//  Utils
//
//  Created by Alessandro Saccoia on 9/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Log.h"
#include <stdlib.h>

namespace dinahmoe {

Log::LogLevel Log::s_defaultLevel = Log::All;

Log::Log() :
  m_degubLevel(Log::s_defaultLevel),
  m_printFileInfo(false),
  m_printCurrentTime(true),
  m_wall(false) {
}

void Log::SetWriteToFile(const char* filePath) {
  m_logfile.open(filePath);
}

void Log::SetLevel(LogLevel nLevel) {
  m_degubLevel = nLevel;
  if (!m_isInitialised) {
    PlatformInit();
    m_isInitialised = true;
  }
}
void Log::PrintFileInfo(bool doPrint_) {
  m_printFileInfo = doPrint_;
}
void Log::PrintCurrentTime(bool doPrint_) {
  m_printCurrentTime = doPrint_;
}

void Log::Write(LogLevel nLevel, const char *file_, int line_, const char *szFormat, ...) {
  CheckInit();
  if (nLevel >= m_degubLevel) {
    va_list args;
    va_start(args, szFormat);
    PlatformWrite(nLevel, szFormat, file_, line_, args);
    va_end(args);
  }
  if (m_wall && nLevel >= Log::Error) {
    exit(1);
  }
}

void Log::CheckInit()
{
  if (!m_isInitialised)
  {
    Init();
  }
}

void Log::Init()
{
  SetLevel(s_defaultLevel);
  PlatformInit();
}

void Log::Deinitialize() {
  if (m_logfile.is_open())
    m_logfile.close();
}


} // Dinahmoe

