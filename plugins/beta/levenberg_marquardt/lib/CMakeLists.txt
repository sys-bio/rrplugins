CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(lmfit)

set(target lmfit) 

set(sources 
lmmin.c
)

add_library(${target}-static STATIC 
${sources}
)

