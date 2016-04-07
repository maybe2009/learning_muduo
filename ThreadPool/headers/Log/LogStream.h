#ifndef OBJ_LOGSTREAM_H
#define OBJ_LOGSTREAM_H

#include <iostream>
#include <string>
#include "../FixedBuffer/FixedBuffer.h"

namespace ok {
#define MAX_INTERGE_STRING_LENGTH 20

class LogStream {
public:
	LogStream(size_t buf_size);

	LogStream &operator<<(int);

    LogStream &operator<<(unsigned int);

	LogStream &operator<<(long);
    
    LogStream &operator<<(unsigned long);

	LogStream &operator<<(long long);

	LogStream &operator<<(unsigned long long);

	LogStream &operator<<(float v);

	LogStream &operator<<(double v);

	LogStream &operator<<(char);

	LogStream &operator<<(std::string str);

	//TODO: remove show after test
	void show();

	void clearBuffer();

private:
	void write();

private:
	FixedBuffer buffer_;
	FixedBuffer::BYTE intBuf[MAX_INTERGE_STRING_LENGTH + 1];
	size_t count_;
	int retVal_;
};

LogStream::LogStream(size_t buf_size)
	: buffer_(buf_size) { }

LogStream &LogStream::
operator<<(int v) {
	std::cout << "Int Version Called" << std::endl;
    if (buffer_.getAvailable() >= MAX_INTERGE_STRING_LENGTH + 1) {
		retVal_ = snprintf(intBuf, MAX_INTERGE_STRING_LENGTH + 1, "%d", v);
		if (retVal_ > 0) {
			count_ = static_cast<size_t>(retVal_);
			write();
		}
	}
	return *this;
}

LogStream &LogStream::
operator<<(unsigned int v) {    
	std::cout << "Int Version Called" << std::endl;
    if (buffer_.getAvailable() >= MAX_INTERGE_STRING_LENGTH + 1) {
		retVal_ = snprintf(intBuf, MAX_INTERGE_STRING_LENGTH + 1, "%u", v);
		if (retVal_ > 0) {
			count_ = static_cast<size_t>(retVal_);
			write();
		}
	}
	return *this;
    
}

LogStream &LogStream::
operator<<(long v) {
	if (buffer_.getAvailable() >= MAX_INTERGE_STRING_LENGTH + 1) {
		retVal_ = snprintf(intBuf, MAX_INTERGE_STRING_LENGTH + 1, "%ld", v);
		if (retVal_ > 0) {
			count_ = static_cast<size_t>(retVal_);
			write();
		}

	}
	return *this;
}

LogStream &LogStream::
operator<<(unsigned long v){
	if (buffer_.getAvailable() >= MAX_INTERGE_STRING_LENGTH + 1) {
		retVal_ = snprintf(intBuf, MAX_INTERGE_STRING_LENGTH + 1, "%lu", v);
		if (retVal_ > 0) {
			count_ = static_cast<size_t>(retVal_);
			write();
		}

	}
	return *this;
     
}

LogStream &LogStream::
operator<<(long long v){
	if (buffer_.getAvailable() >= MAX_INTERGE_STRING_LENGTH + 1) {
		retVal_ = snprintf(intBuf, MAX_INTERGE_STRING_LENGTH + 1, "%lld", v);
		if (retVal_ > 0) {
			count_ = static_cast<size_t>(retVal_);
			write();
		}

	}
	return *this;
     
}


LogStream &LogStream::
operator<<(unsigned long long v){
	if (buffer_.getAvailable() >= MAX_INTERGE_STRING_LENGTH + 1) {
		retVal_ = snprintf(intBuf, MAX_INTERGE_STRING_LENGTH + 1, "%llu", v);
		if (retVal_ > 0) {
			count_ = static_cast<size_t>(retVal_);
			write();
		}

	}
	return *this;
     
}

LogStream &LogStream::
operator<<(char v) {
	buffer_.write(&v, 1);
	return *this;
}

LogStream &LogStream::operator<<(std::string str) {
	if (buffer_.getAvailable() >= str.length()) {
		buffer_.write(str.c_str(), str.length());
	}
	return *this;
}

LogStream &LogStream::operator<<(float v) {
	return *this << static_cast<double>(v);
}

LogStream &LogStream::operator<<(double v) {
	if (buffer_.getAvailable() >= MAX_INTERGE_STRING_LENGTH + 1) {
		retVal_ = snprintf(intBuf, MAX_INTERGE_STRING_LENGTH + 1, "%.12g", v);
		if (retVal_ > 0) {
			count_ = static_cast<size_t>(retVal_);
			write();
		}
	}
	return *this;
}

void LogStream::write() {
	buffer_.write(intBuf, count_);
}

void LogStream::clearBuffer() {
	buffer_.clear();
}

//TODO: remove after test
void LogStream::
show() {
	buffer_.show();
}

};//namespace ok
#endif //OBJ_LOGSTREAM_H
