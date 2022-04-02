# check if conan installed a test framework
if (NOT TARGET CONAN_PKG::gtest)
	message(FATAL_ERROR "CONAN_PKG::gtest not found!\nPlease run `conan install` with `-e CONAN_RUN_TESTS=True`.")
endif ()

# unit tests
add_executable(qt_crawler_tests
               # List sources here
               UT_Networking_HttpClient.cpp
               UT_QtCrawlerApp.cpp
               )

target_compile_features(qt_crawler_tests PUBLIC cxx_std_17)

target_link_libraries(qt_crawler_tests
                      PRIVATE
                      qt_crawler::qt_crawler
                      CONAN_PKG::gtest
                      )

include(GoogleTest)
gtest_discover_tests(qt_crawler_tests)
