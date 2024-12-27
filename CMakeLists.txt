cmake_minimum_required(VERSION 3.9)
project(logcat VERSION 1.0.1 DESCRIPTION "android logcat")

add_definitions (
    -Os
	-DHAVE_SYS_UIO_H -DHAVE_IOCTL
)

add_definitions('-DLOGGER_LOG_MAIN="log_main"')

include(GNUInstallDirs)
add_library(log SHARED
    ${PROJECT_SOURCE_DIR}/liblog/logprint.c
    ${PROJECT_SOURCE_DIR}/liblog/event_tag_map.c
    ${PROJECT_SOURCE_DIR}/liblog/logd_write.c
)

# List of header files
set(HEADER_FILES
    ${PROJECT_SOURCE_DIR}/include/log/event_tag_map.h
    ${PROJECT_SOURCE_DIR}/include/log/log.h
    ${PROJECT_SOURCE_DIR}/include/log/log_read.h
    ${PROJECT_SOURCE_DIR}/include/log/logprint.h
    ${PROJECT_SOURCE_DIR}/include/log/logger.h
    ${PROJECT_SOURCE_DIR}/include/log/logd.h
)

set_target_properties(log PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADER_FILES}")
# Set runtime path
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# Set pkg-config
configure_file(log.pc.in log.pc @ONLY)
target_include_directories(log PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_include_directories(log PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
set(CMAKE_INSTALL_INCLUDEDIR "/usr/include")

install(TARGETS log
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/log)
install(FILES ${CMAKE_BINARY_DIR}/log.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


add_executable(logcat  ${PROJECT_SOURCE_DIR}/logcat/logcat.cpp)
target_link_libraries(logcat log)
install(TARGETS logcat
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(logwrapper  ${PROJECT_SOURCE_DIR}/logwrapper/logwrapper.c)
target_link_libraries(logwrapper log)
install(TARGETS logwrapper
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

