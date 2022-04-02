cmake_minimum_required(VERSION 3.9)

project(qt_crawler CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET (CMAKE_C_COMPILER "/usr/bin/clang" CACHE STRING "C compiler" FORCE)
    SET (CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE)
else()
    SET (CMAKE_C_COMPILER "/usr/bin/gcc" CACHE STRING "C compiler" FORCE)
    SET (CMAKE_CXX_COMPILER "/usr/bin/gcc++" CACHE STRING "C++ compiler" FORCE)
endif()

include(StandardProjectSettings)
include(PreventInSourceBuilds)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Link this 'library' to use the warnings specified in CompilerWarnings
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(CompilerWarnings)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(Sanitizers)
enable_sanitizers(project_options)

# allow for static analysis options
include(StaticAnalyzers)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)

# Set up some extra Conan dependencies based on our needs before loading Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

include(Conan)
run_conan()

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# add binaries
add_subdirectory(bin)

# add project code
add_subdirectory(src)


