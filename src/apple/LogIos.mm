//
//  Log.mm
//  Utils
//
//  Created by Alessandro Saccoia on 9/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Log.h"
#import <Foundation/Foundation.h>  
#include <iostream>
#include <fstream>
#include <chrono>

namespace dinahmoe {

void Log::PlatformInit() {

}


void Log::PlatformWrite(LogLevel nLevel, const char *szFormat, const char *file_, int line_, va_list args) {
  if (!m_logfile.is_open()) {
    // The autorelease pool is needed because this method can be accessed by multiple threads
    // and cocoa creates a pool just for the first thread.
    
    char buf[512];
    sprintf(buf, "\033[1;31m%s\033[0m\n", szFormat);
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSString *format = [NSString stringWithCString:buf encoding:[NSString defaultCStringEncoding]];
    NSLogv(format, args);
    [pool release];
  } else {
    static char buf[512];
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
    vsnprintf(buf, 512, szFormat, args);
    m_logfile << buf << std::endl;
    std::flush(m_logfile);
  }
}

} // Dinahmoe
