#include <iostream>
#include "FixedBuffer.h"
#include <boost/ptr_container/ptr_vector.hpp>

using namespace ok;

void show(const void *p, int size)
{
    int i;
    const char *ptr = (char*)p;
    for (i = 0; i < size; ++i, ++ptr) {
        printf("%c ", *ptr);
    }

    printf("\n");
}

int main()
{
    FixedBuffer b(5);
    b.write("Hi", 3);
    std::cout << "Ava: " << b.getAvailable() << " Cap: " << b.getCapacity() << std::endl; 
    show(b.getBufferPtr(), b.getWaterMeter()); 
    
    b.clear();

    b.write("Okay!", 6);
    std::cout << "Ava: " << b.getAvailable() << " Cap: " << b.getCapacity() << std::endl; 
    show(b.getBufferPtr(), b.getWaterMeter()); 
    
    return 0;
}


