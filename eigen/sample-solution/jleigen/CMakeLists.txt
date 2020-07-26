project(JlEigen)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

find_package(JlCxx)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_library(jleigen SHARED jleigen.cpp)

target_link_libraries(jleigen JlCxx::cxxwrap_julia JlCxx::cxxwrap_julia_stl Eigen3::Eigen)

install(TARGETS jleigen
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)