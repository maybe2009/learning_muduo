//
// Created by admin on 3/9/16.
//

#ifndef OBJ_LOGSTREAM_H
#define OBJ_LOGSTREAM_H

#include "../FixedBuffer/FixedBuffer.h"
namespace ok {
#define MAXINTLENGTH 20
class LogStream {
public:
	LogStream(int buf_size);
	LogStream& operator<<(int);
	LogStream& operator<<(char);
	void show();
private:
	FixedBuffer buffer_;
	FixedBuffer::BYTE intBuf[MAXINTLENGTH + 1];
};

LogStream::LogStream(int buf_size)
	: buffer_(buf_size)
{}

LogStream &LogStream::
operator<<(int v) {
	int num = snprintf(intBuf, MAXINTLENGTH, "%d", v);
	buffer_.write(intBuf, num);
	return *this;
}

LogStream &LogStream::
operator<<(char v) {
	buffer_.write(&v,1);
	return *this;
}

//TODO: remove after test
void LogStream::
show()
{
	buffer_.show();
}

};
#endif //OBJ_LOGSTREAM_H
