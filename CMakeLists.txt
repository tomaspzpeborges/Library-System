cmake_minimum_required(VERSION 2.8)

project(library)

set( CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "-fdump-rtl-expand")

include_directories(unity/include) #this says where to look for the include files beyond the locality of the files that have the include statements

add_executable(library main.c interface.c book_management.c user.c) 

add_executable(book_management_tests unit_tests.c book_management.c unity/src/unity.c)#testing is a different executable 

add_executable(user_tests unit_tests2.c book_management.c user.c unity/src/unity.c)#testing is a different executable 


install(TARGETS library RUNTIME DESTINATION bin)
