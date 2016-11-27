cmake_minimum_required(VERSION 2.6)
list(APPEND CMAKE_MODULE_PATH $ENV{IMAGINEPP_ROOT}/CMake) #For old Imagine++
find_package(Imagine REQUIRED)

project(Exo3009)
add_executable(Exo3009 Exo3009.cpp)
ImagineUseModules(Exo3009 Graphics)
