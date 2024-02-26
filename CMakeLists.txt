cmake_minimum_required(VERSION 3.10)

project(LoadAndSaveTIFF)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(LoadAndSaveTIFF LoadAndSaveTIFF.cpp)
target_link_libraries(LoadAndSaveTIFF ${ITK_LIBRARIES})
