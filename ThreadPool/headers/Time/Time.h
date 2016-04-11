//
// Created by admin on 4/10/16.
//

#ifndef TEST_FORMAT_RANGE_TIME_H
#define TEST_FORMAT_RANGE_TIME_H

#include <sys/time.h>
#include <string>

#define MAX_LOGTIME_LENGTH 24

class Time final{
public:
	Time();

	char* getASCTime();

	char * getLocalTime();

	std::string getLogFmtTime();

private:
	void getTime();

	void getGMTTime();

private:
	time_t time_;
	struct tm* gmtTime_;
	char logTimeBuf_[MAX_LOGTIME_LENGTH];
	std::string logTimeStr_;
};


#endif //TEST_FORMAT_RANGE_TIME_H
