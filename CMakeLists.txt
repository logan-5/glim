cmake_minimum_required(VERSION 3.1.0)
project(glim VERSION 0.1.0)

add_subdirectory(lib/cm)

set(PROJECT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CONFIG_HEADER_PATH ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_config.hpp)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config_template.hpp.in
    ${CONFIG_HEADER_PATH}
    )
set(SRC ${SRC} ${CONFIG_HEADER_PATH})

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC ${SRC} 
    ${SRC_DIR}/image.cpp 
    ${SRC_DIR}/fs.cpp 
    ${SRC_DIR}/ray.cpp
    ${SRC_DIR}/sampler.cpp
    ${SRC_DIR}/scene.cpp
    )
set(HEADERS ${HEADERS} 
    ${SRC_DIR}/image.hpp 
    ${SRC_DIR}/fs.hpp 
    ${SRC_DIR}/ray.hpp
    ${SRC_DIR}/sampler.hpp
    ${SRC_DIR}/scene.hpp
    )

add_library(glim "")
target_link_libraries(glim PUBLIC cm)
target_include_directories(glim PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(glim PUBLIC ${SRC_DIR})
target_sources(glim PRIVATE ${SRC})
target_sources(glim PRIVATE ${HEADERS})
set_property(TARGET glim PROPERTY CXX_STANDARD 17)

option(ASAN "ASAN" OFF)
if (ASAN)
    message("-- enabling address sanitizer")
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    else (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        message("address sanitizer not supported for this compiler")
    endif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
else (ASAN)
    message("-- not enabling address sanitizer")
endif (ASAN)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -Werror -pedantic")

add_subdirectory(example)

enable_testing()
add_subdirectory(test)
