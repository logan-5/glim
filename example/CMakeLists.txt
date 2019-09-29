add_executable(example main.cpp)
target_link_libraries(example glim)
set_property(TARGET example PROPERTY CXX_STANDARD 17)