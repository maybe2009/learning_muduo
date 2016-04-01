#include <iostream>

#include <boost/function.hpp>
#include <boost/bind.hpp>

typedef boost::function<void(int, int)> fun;

void process(int a, int b)
{
    std::cout << "HEllo" << a << "&" << b << std::endl;
}

int main()
{

    fun f = boost::bind(process, 3, _1);
    
    f(6,1);

    return 0;
}
