cmake_minimum_required(VERSION 3.0.0)
project(libmath)

add_compile_options(-std=c++14)

set(SRC
    chain.cxx
	column.cxx
)

add_library(math SHARED ${SRC})