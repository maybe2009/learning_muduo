cmake_minimum_required(VERSION 2.8)
project(test_format_range CXX)

#Set my module paths
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

#Support C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Set target directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

#Set variables...
set(HEADER_FOLDER ${PROJECT_SOURCE_DIR}/ThreadPool/headers)
set(HEADER_FixedBuffer ${HEADER_FOLDER}/FixedBuffer/FixedBuffer.h ${HEADER_FOLDER}/FixedBuffer/FixedBufferHandle.h)
set(HEADER_Log ${HEADER_FOLDER}/Log/LogStream.h)
set(HEADER_SYN_Atomic ${HEADER_FOLDER}/Synchronization/AtomicInteger.h)
set(FOLDER_Time ${HEADER_FOLDER}/Time)

#Set all header files
set(ALL_HEADER_FILES ${HEADER_Log} ${HEADER_FixedBuffer})

#Add Thread source file
#Thread
aux_source_directory(${PROJECT_SOURCE_DIR}/ThreadPool/src/Thread SRC_Thread)
#Time
aux_source_directory(${FOLDER_Time} SRC_Time)

#Add test source files
set(SRC_UTILITYS ${SRC_Thread} ${SRC_Time})
set(SRC_test_format_range ${PROJECT_SOURCE_DIR}/lab/test_format_range.cpp)
set(SRC_test_FixedBufferHandle ${PROJECT_SOURCE_DIR}/lab/test_FixedBufferHandle.cpp)
set(SRC_test_Time ${PROJECT_SOURCE_DIR}/lab/test_Time.cpp)

#Add executable
add_executable(test_format_range ${ALL_HEADER_FILES} ${SRC_UTILITYS} ${SRC_test_format_range})
add_executable(test_FixedBufferHandle ${ALL_HEADER_FILES} ${SRC_UTILITYS} ${SRC_test_FixedBufferHandle})
add_executable(test_Time ${SRC_Time} ${SRC_test_Time})

#Use self-edit FindLinuxPthread module
find_package(LinuxPthread REQUIRED)
if (LIB_PTHREAD_FOUND)
	message(STATUS "FindLinuxPthread: pthread  found! " ${LIB_LINUX_PTHREAD})
	target_link_libraries(test_format_range ${LIB_LINUX_PTHREAD})
	target_link_libraries(test_FixedBufferHandle ${LIB_LINUX_PTHREAD})
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


