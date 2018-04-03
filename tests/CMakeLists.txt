cmake_minimum_required(VERSION 3.0.0)
project(tests)

add_executable(test1 test1.cxx)
target_link_libraries(test1 xlnt)
