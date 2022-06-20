cmake_minimum_required(VERSION 3.22)
project(at_client_cpp)

set(CMAKE_CXX_STANDARD 14)
set(cpprestsdk_DIR "C:/Users/sting/github/vcpkg/packages/cpprestsdk_x86-windows/share/cpprestsdk")
set(ZLIB_INCLUDE_DIR "C:/Users/sting/github/vcpkg/packages/zlib_x86-windows/include")
set(ZLIB_LIBRARY "C:/Users/sting/github/vcpkg/packages/zlib_x86-windows/lib")
set(unofficial-brotli_DIR "C:/Users/sting/github/vcpkg/packages/brotli_x86-windows/share/unofficial-brotli")


find_package(cpprestsdk CONFIG REQUIRED)
find_package(unofficial-brotli CONFIG REQUIRED)

add_executable(at_client_cpp main.cpp)


target_link_libraries(at_client_cpp PRIVATE cpprestsdk::cpprest)




