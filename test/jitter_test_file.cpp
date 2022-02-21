#include <iostream>

extern "C" auto jitter_test_file() -> bool
{
    std::cout << __FILE__ << " : " << __PRETTY_FUNCTION__ << '\n';
    return true;
}
