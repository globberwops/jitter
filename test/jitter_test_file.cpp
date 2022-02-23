#include <iostream>

extern "C" auto jitter_test_file() -> bool
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    std::cout << __FILE__ << " : " << __PRETTY_FUNCTION__ << '\n';
    return true;
}
