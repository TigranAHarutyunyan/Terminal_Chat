cmake_minimum_required(VERSION 3.10)
project(server)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
set(SOURCES
	server.cpp
	server_class.cpp
	crypt.cpp
)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(crypt.hpp)
add_executable(server ${SOURCES})
target_include_directories(server  PRIVATE ${BOOST_INCLUDE_DIR})
target_link_libraries(server PRIVATE ${BOOST_LIBRARIES})
target_include_directories(server PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(server PRIVATE ${OPENSSL_LIBRARIES})
