//
//  LogLinux.cpp
//  Utils
//
//  Created by Alessandro Saccoia on 30/3/2013.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Log.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdio>

namespace dinahmoe {

void Log::PlatformInit() {

}

void Log::PlatformWrite(const char *szFormat, const char *file_, int line_, va_list args) {
  if (m_logfile.is_open()) {
    if (m_printCurrentTime) {
      auto now = std::chrono::system_clock::now();
      auto duration = now.time_since_epoch();
      auto hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
      auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
      auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
      auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
      m_logfile << hours % 24 << ":" << minutes % 60 << ":" << seconds % 60 << ":" << millis % 1000 << " ";
    }
    if (m_printFileInfo)
      m_logfile << "(" << file_ << ":" << line_ << ")" << std::endl;
    static char buf[512];
	#ifdef DM_PLATFORM_CYGWIN
    m_logfile << szFormat << " bug with cygwin" << std::endl;
	#else
    vsnprintf(buf, 512, szFormat, args);
    m_logfile << buf << std::endl;
	#endif
    std::flush(m_logfile);
  } else {
    static char buf[512];
	#ifdef DM_PLATFORM_CYGWIN
    std::cout << szFormat << " bug with cygwin" << std::endl;
	#else
    vsnprintf(buf, 512, szFormat, args);
    std::cout << buf << std::endl;
	#endif
  }
}


}
