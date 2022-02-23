#include <iostream>

extern "C" void jitter_test_file() noexcept
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << '\n';
}

extern "C" auto jitter_test_file_return() -> bool
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << '\n';
    return true;
}

extern "C" void jitter_test_file_args(int number)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << " : " << number << '\n';
}
