cmake_minimum_required(VERSION 3.8)
project(test_package CXX)

find_package(Platform.Collections REQUIRED CONFIG)

add_executable(${PROJECT_NAME} test_package.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Platform.Collections::Platform.Collections)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)