cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(subak_info)

add_executable(subak_info
    subak_info.cpp
)

find_package(MAVSDK REQUIRED)

target_link_libraries(subak_info
    MAVSDK::mavsdk
)

if(NOT MSVC)
    add_compile_options(subak_info PRIVATE -Wall -Wextra)
else()
    add_compile_options(subak_info PRIVATE -WX -W2)
endif()
