cmake_minimum_required(VERSION 3.10)
project(ModulatorSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(simulation main.cpp ${SRC_FILES})

if(OpenMP_CXX_FOUND)
    target_link_libraries(simulation PUBLIC OpenMP::OpenMP_CXX)
endif()