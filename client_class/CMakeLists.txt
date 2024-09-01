cmake_minimum_required(VERSION 3.10)
project(my_program)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED )
set(SOURCES
    main.cpp
    client_class.cpp 
    
)
add_executable(my_program ${SOURCES})

target_include_directories(my_program PRIVATE ${OPENSSL_INCLUDE_DIR})
target_include_directories(my_program PRIVATE ${BOOST_INCLUDE_DIR})

target_link_libraries(my_program PRIVATE ${OPENSSL_LIBRARIES})
target_link_libraries(my_program PRIVATE ${BOOST_LIBRARIES})
