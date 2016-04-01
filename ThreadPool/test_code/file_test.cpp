#include "FileWrite.h"
#include <iostream>
using namespace ok;
int main()
{
    FileWrite obj("./myfile");
    obj.write("Hello Success!\n");
    return 0;
}
