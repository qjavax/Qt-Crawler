macro(run_conan)
  # Download automatically, you can also just copy the conan.cmake file
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.0/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
  endif()

  include(${CMAKE_BINARY_DIR}/conan.cmake)
  conan_add_remote(NAME bincrafters
    INDEX 1
    URL https://api.bintray.com/conan/bincrafters/public-conan
    VERIFY_SSL True)

  conan_cmake_run(
    REQUIRES
    ${CONAN_EXTRA_REQUIRES}
    gtest/cci.20210126
    cxxopts/2.2.1
    gumbo-parser/0.10.1
    libcurl/7.80.0
    fmt/8.1.1
    OPTIONS
    ${CONAN_EXTRA_OPTIONS}
    BASIC_SETUP
    CMAKE_TARGETS # individual targets to link to
    BUILD missing)
endmacro()
