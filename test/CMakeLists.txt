include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG 7b9885133108ae301ddd16e2651320f54cafeba7 # v2.4.8
)

set(DOCTEST_NO_INSTALL
    ON
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(doctest)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)

add_executable(JitterTest jitter_test.cpp)

target_compile_features(JitterTest PRIVATE cxx_std_17)

target_link_libraries(JitterTest PRIVATE doctest::doctest Jitter::Jitter)

doctest_discover_tests(JitterTest)
