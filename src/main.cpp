#include <iostream>
#include <ostream>
#include "yart/tmp.hpp"

int main(int  /*argc*/, char * /*argv*/[])
{
    auto res = tmp::add(1,2);
    std::cout << res << "\n";

    return 0;
}