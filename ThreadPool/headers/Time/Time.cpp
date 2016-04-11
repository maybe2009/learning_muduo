//
// Created by admin on 4/10/16.
//

#include <sys/time.h>
#include <ctime>
#include "Time.h"

Time::Time()
{
	logTimeStr_.reserve(MAX_LOGTIME_LENGTH);
}

void Time::getTime() {
	::time(&time_);
}

void Time::getGMTTime() {
	gmtTime_ = ::gmtime(&time_);
}

char *Time::getASCTime() {
	getTime();
	getGMTTime();
	return ::asctime(gmtTime_);
}

char * Time::getLocalTime() {
	getTime();
	return ::ctime(&time_);
}

std::string Time::getLogFmtTime() {
	getTime();
	getGMTTime();
	strftime(logTimeBuf_, MAX_LOGTIME_LENGTH, "%F %T %Z", gmtTime_);
	logTimeBuf_[MAX_LOGTIME_LENGTH - 1] = '\n';
	logTimeStr_.replace(0, MAX_LOGTIME_LENGTH, logTimeBuf_);

	return logTimeStr_;
}














