cmake_minimum_required(VERSION 2.8)
project(obj CXX)

#Set my module paths
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
#Support C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#Add ThreadPool dir
aux_source_directory(${PROJECT_SOURCE_DIR}/ThreadPool/src/Thread SRC_THREAD)
set(SOURCE_FILES main.cpp ${SRC_THREAD} ThreadPool/headers/Log/LogStream.h)

add_executable(obj ${SOURCE_FILES})
#Use self-edit FindLinuxPthread module
find_package(LinuxPthread REQUIRED)
if (LIB_PTHREAD_FOUND)
	message(STATUS "FindLinuxPthread: pthread  found! " ${LIB_LINUX_PTHREAD})
	target_link_libraries(obj ${LIB_LINUX_PTHREAD})
else()
	message(FATAL_ERROR "FindLinuxPthread: pthread not found!")
endif ()

#Use FindThread module
#find_package(Threads REQUIRED )
#if(CMAKE_USE_PTHREADS_INIT)
#    target_link_libraries(obj ${CMAKE_THREAD_LIBS_INIT})
#    message(STATUS "pthread found!")
#else()
#    message(SEND_ERROR "pthread not found!")
#endif(CMAKE_USE_PTHREADS_INIT)


