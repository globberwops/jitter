add_library(Jitter)
add_library(Jitter::Jitter ALIAS Jitter)

target_sources(Jitter PRIVATE jitter.cpp)

target_link_libraries(Jitter PUBLIC ${CMAKE_DL_LIBS})

target_include_directories(
  Jitter PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

target_compile_features(Jitter PRIVATE cxx_std_17)

install(TARGETS Jitter EXPORT JitterTargets)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  JitterConfigVersion.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY SameMajorVersion)

install(
  EXPORT JitterTargets
  DESTINATION lib/cmake/Jitter
  FILE JitterConfig.cmake
  NAMESPACE Jitter::)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/JitterConfigVersion.cmake
        DESTINATION lib/cmake/Jitter)
