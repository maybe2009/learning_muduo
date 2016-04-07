cmake_minimum_required(VERSION 2.8)
project(obj CXX)

#Set my module paths
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

#Support C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Set target directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#Add ThreadPool source directory
aux_source_directory(${PROJECT_SOURCE_DIR}/ThreadPool/src/Thread DIR_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/ThreadPool/headers DIR_HEADER)

set(SOURCE_FILES ${DIR_SRC} ./lab/test_FixedBufferHandle.cpp )
set(HEADER_FILES ${PROJECT_SOURCE_DIR}/ThreadPool/headers/)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ThreadPool/headers/)

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


