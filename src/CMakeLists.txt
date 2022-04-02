
cmake_minimum_required(VERSION 3.9)
project(qt_crawler
        VERSION 0.0.1
        )

# add dependencies
set(QDB_VERSION ${PROJECT_VERSION})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h )

# library definition
add_library(${PROJECT_NAME}
            version.h
            # List sources here
            ${CMAKE_CURRENT_SOURCE_DIR}/Networking/HttpClient.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Networking/CurlAdapter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Parser/GumboParserAdapter.cpp
            )

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME}
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:include>
                           )

target_link_libraries(${PROJECT_NAME}
                      PRIVATE
                      project_options
                      project_warnings
                      CONAN_PKG::gumbo-parser
                      CONAN_PKG::libcurl
                      CONAN_PKG::fmt
                      )

add_library(qt_crawler::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
