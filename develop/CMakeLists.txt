cmake_minimum_required (VERSION 3.5)
project (ForradiaWorldLANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

find_package(httplib REQUIRED CONFIG)
find_package(websocketpp REQUIRED CONFIG)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(forradia-world ${SRC_FILES})

target_link_libraries(forradia-world httplib::httplib websocketpp::websocketpp
)

target_include_directories(forradia-world PUBLIC "src" ${httplib_INCLUDE_DIR})

target_precompile_headers(forradia-world
    PRIVATE src/precomp/precomp.hpp
)


