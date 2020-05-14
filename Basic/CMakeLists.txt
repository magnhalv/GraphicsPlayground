cmake_minimum_required(VERSION 3.0.0)
project(Basic VERSION 0.1.0)

include(CTest)
enable_testing()


add_executable(Basic main.cpp ../lib/glad.c)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Basic glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

