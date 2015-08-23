CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

MESSAGE(STATUS "Configuring dm-log library")

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../dm-cmake)
INCLUDE(SetTargetOptions)
INCLUDE(SetPlatformDefines)

SET_PLATFORM_DEFINES()

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/include/")

FILE(GLOB dm-log_include_files "${CMAKE_CURRENT_SOURCE_DIR}/include/*.*")
SET(dm-log_src "${CMAKE_CURRENT_SOURCE_DIR}/src/Log.cpp")

IF(APPLE)
  IF("${BUILD_FOR}" STREQUAL "osx" )
    SET(dm-log_platform ${CMAKE_CURRENT_SOURCE_DIR}/src/apple/LogMac.mm)
  ELSE("${BUILD_FOR}" STREQUAL "ios" )
    SET(dm-log_platform ${CMAKE_CURRENT_SOURCE_DIR}/src/apple/LogIos.mm)
  ENDIF()
ELSEIF(ANDROID)
  SET(dm-log_platform ${CMAKE_CURRENT_SOURCE_DIR}/src/android/LogAndroid.cpp)
ELSEIF(UNIX)
  SET(dm-log_platform ${CMAKE_CURRENT_SOURCE_DIR}/src/linux/LogLinux.cpp)
ENDIF()

ADD_LIBRARY(dm-log
    ${dm-log_include_files}
    ${dm-log_src}
    ${dm-log_platform})

IF(APPLE)
  SET(DM_LOG_LINK_FLAGS "-framework Foundation" CACHE INTERNAL "dm-log linker flags")
ELSE(APPLE)
  SET(DM_LOG_LINK_FLAGS "" CACHE INTERNAL "dm-log linker flags")
ENDIF(APPLE)

FSET_TARGET_OPTIONS(dm-log "")
