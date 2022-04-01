# main binary
add_executable(qt_crawler_cli
               ${CMAKE_CURRENT_SOURCE_DIR}/../src/version.h
               qt_crawler_cli.cpp
               )

target_link_libraries(qt_crawler_cli PRIVATE
                      qt_crawler::qt_crawler
                      project_options
                      project_warnings
                      CONAN_PKG::cxxopts
                      CONAN_PKG::fmt
                      )