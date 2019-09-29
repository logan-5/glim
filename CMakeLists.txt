cmake_minimum_required(VERSION 3.0.0)
project(glim VERSION 0.1.0)

enable_testing()
add_subdirectory(test)

add_subdirectory(lib/cm)

add_executable(glim src/main.cpp)
target_link_libraries(glim cm)
set_property(TARGET glim PROPERTY CXX_STANDARD 17)
