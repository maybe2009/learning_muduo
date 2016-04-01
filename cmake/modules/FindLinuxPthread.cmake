MESSAGE(STATUS "Using FindPthread module to find pthread in Linux")

find_library(
	LIB_LINUX_PTHREAD
	libpthread.so.0
	/lib/x86_64-linux-gnu/
)

if (LIB_LINUX_PTHREAD)
	set(LIB_PTHREAD_FOUND TRUE)
endif (LIB_LINUX_PTHREAD)
