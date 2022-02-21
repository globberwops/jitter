cmake_minimum_required(VERSION 3.22.0)

project(
  Jitter
  VERSION 1.0.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX)

option(Jitter_BUILD_TESTING "Build testing" ${PROJECT_IS_TOP_LEVEL})
option(Jitter_BUILD_DOCS "Build documentation" ${PROJECT_IS_TOP_LEVEL})

add_subdirectory(src)

if(Jitter_BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

if(Jitter_BUILD_DOCS)
  add_subdirectory(doc)
endif()

install(DIRECTORY include/ TYPE INCLUDE)
