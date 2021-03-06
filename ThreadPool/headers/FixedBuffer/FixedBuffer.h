/*
 * This Code is edited by sun wukong @ 2015.12.26 12:50:36 CST 
 * 
 * Just feel free to use this code as you wish.
 * Any bug and ugly code, please notify me, thanks!
 *
 * Github https://githuc.com/maybe2009
 * Gmail  qtdssunwukong@gmail.com
 * 									-Auto Generated By UltiSnips
 */

#ifndef OK_FIXEDBUFFER_INCLUDED
#define OK_FIXEDBUFFER_INCLUDED

#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <string.h>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/noncopyable.hpp>

namespace ok
{
#define KB(n) ((n) * 1024)
#define MB(n) ((n) * 1024 *1024)

	class FixedBuffer : public boost::noncopyable
	{
	public:
		typedef char BYTE;

	public:
		FixedBuffer(size_t size)
			: capacity_(size),
			  available_(size),
			  waterMeter_(0),
			  start_(new BYTE[size]),
			  current_(start_),
			  end_(start_ + size)
		{
		}

		~FixedBuffer()
		{
			delete []start_;
		}

		void dump(size_t fd)
		{
			/*TODO add exception*/
			std::cout << "Dump :" << waterMeter_ << std::endl;
			::write(fd, start_, waterMeter_);
		}

		void write(const void* src, size_t len)
		{
			if (len <= available_)
			{
				memcpy(current_, src, len);
				moveMeters(len);
			}
		}


		/**
		 * @brief Set each byte to 0, reset all the argument like waterMeter_ etc. 
		 */
		void clear()
		{
			memset(start_, 0, capacity_);
			current_ = start_;
			available_ = capacity_;
			waterMeter_ = 0;
		}


		/**
		 * @brief Get the current available size in byte
		 *
		 * @return Current available bytes
		 */
		size_t getAvailable() const
		{
			return available_;
		}


		/**
		 * @brief Get capacity
		 *
		 * @return Capacity 
		 */
		size_t getCapacity() const
		{
			return capacity_;
		}

		/**
		 * @brief Get watermeter indication which represents how many bytes there 
		 *        are in this buffer
		 *
		 * @return Watermeter indication
		 */
		size_t getWaterMeter() const
		{
			return waterMeter_;
		}

		/*TODO: delete show() after debug*/
		void show()
		{
			//TODO:remove printf after test
			printf("Total size %ld Water Meter %ld Avai: %ld\n", capacity_, waterMeter_, available_);
			for (size_t i = 0; i < waterMeter_; ++i)
			{
				printf("P%ld:%c ", i, *(start_ + i));
			}
			printf("\n");
		}

	private:

		/**
		 * @brief When writting to buffer, use this function to adjust 
		 *corresponding indicators like watermeter etc. After this routine,
		 *current_ index will move ahead for len bytes, available_ bytes will
		 *reduce by len, waterMeter_ will rise for len
		 *
		 * @param len Thes number of bytes to be written
		 */
		void moveMeters(size_t len)
		{
			current_ += len;
			available_ -= len;
			waterMeter_ += len;
		}

	private:
		const size_t capacity_;
		size_t available_;
		size_t waterMeter_;
		BYTE* const start_;
		BYTE* current_;
		BYTE* end_;
	};
};

#endif /* ifndef OK_FIXEDBUFFER_INCLUDED */

