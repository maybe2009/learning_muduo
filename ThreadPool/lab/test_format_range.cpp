//
// Created by admin on 3/30/16.
//

#include <iostream>
#include "../ThreadPool/headers/Log/LogStream.h"
#include <stdio.h>
#include <limits.h>

int main()
{
    printf("Size of int %lu\n", sizeof(int));
    printf("Size of unsigned int %lu\n", sizeof(unsigned int));
    printf("Size of long %lu\n", sizeof(long));
    printf("Size of unsigned long %lu\n", sizeof(unsigned long));
    
    printf("LONG_MAX %ld\n", (long)LONG_MAX); 
    printf("LONG_MIN %ld\n", (long)LONG_MIN);

    int i = -2147483648; 

    long l = -9223372036854775808L;
    long ml = 9223372036854775807L;
    unsigned long ul = 18446744073709551615UL;
    
    long long ll = -9223372036854775808LL;
    long long mll =  9223372036854775807LL;

    unsigned long long ull = 18446744073709551615ULL;

	std::cout << "Begin test" << std::endl;

    ok::LogStream log(21);
    
    std::cout << "Range of signed long: " << std::endl; 
    log << ml;
	log.show();
	log.clearBuffer();
    
    log << l;
	log.show();
	log.clearBuffer();

    std::cout << "Range of unsigned long: " << std::endl;
    log << ul;
	log.show();
	log.clearBuffer();

    std::cout << "Range of signed long long: " << std::endl;
    log << mll;
	log.show();
	log.clearBuffer();
    
    log << ll;
	log.show();
	log.clearBuffer();
    
    std::cout << "Range of unsigned long long: " << std::endl;
    log << ull;
	log.show();
	log.clearBuffer();
}
