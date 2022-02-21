#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "jitter/jitter.hpp"

TEST_CASE("Jitter")
{
    auto jitter = jitter::Jitter{};
    auto result = jitter.Compile("test/jitter_test_file.cpp");
    CHECK(result);
}
