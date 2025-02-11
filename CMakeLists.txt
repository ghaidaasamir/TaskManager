cmake_minimum_required(VERSION 3.10)
project(TaskManagerApplication)

set(CMAKE_CXX_STANDARD 17)  
find_package(OpenMP REQUIRED)  

add_executable(TaskManager Application.cpp)  

if(OpenMP_CXX_FOUND)
    target_link_libraries(TaskManager PUBLIC OpenMP::OpenMP_CXX) 
endif()
