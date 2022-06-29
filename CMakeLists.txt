cmake_minimum_required(VERSION 3.22)
project(AP_17)

set(CMAKE_CXX_STANDARD 14)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML2/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS system graphics REQUIRED)

add_executable(AP_17 main.cpp)
include_directories(C:/SFML2/include)
target_link_libraries(AP_17 sfml-graphics sfml-system)