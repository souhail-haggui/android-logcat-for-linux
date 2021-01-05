cmake_minimum_required(VERSION 2.8)
project (logcat)

add_definitions (
    -Os
	-DHAVE_SYS_UIO_H -DHAVE_IOCTL
)

add_definitions('-DLOGGER_LOG_MAIN="log_main"')
add_definitions('-DLOGGER_LOG_RADIO="log_radio"')
add_definitions('-DLOGGER_LOG_EVENTS="log_events"')
add_definitions('-DLOGGER_LOG_SYSTEM="log_system"')

include_directories (${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/liblog/*.c")
add_library(log STATIC ${SOURCES})

#static link
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(test  ${PROJECT_SOURCE_DIR}/liblog/test.c)
target_link_libraries(test log)

add_executable(logcat  ${PROJECT_SOURCE_DIR}/logcat/logcat.cpp)
target_link_libraries(logcat log)

add_executable(logwrapper  ${PROJECT_SOURCE_DIR}/logwrapper/logwrapper.c)
target_link_libraries(logwrapper log)
