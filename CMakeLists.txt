cmake_minimum_required(VERSION 3.25)
project(frome)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(frome main.cpp)

target_link_libraries(frome ${OpenCV_LIBS})