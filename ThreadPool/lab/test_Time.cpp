//
// Created by admin on 4/10/16.
//

#include "../ThreadPool/headers/Time/Time.h"

#include <iostream>

int main ()
{
	Time t;
	std::cout << "UTC time is " << t.getASCTime();
	std::cout << "Local time is " << t.getLocalTime();
	std::cout << "Log Fmt time is " << t.getLogFmtTime();
	return 0;
}