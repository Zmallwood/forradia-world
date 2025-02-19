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
    PRIVATE
        <iostream>
        <map>
        <memory>
        <filesystem>
        <algorithm>
        <set>
        <vector>
        <functional>
        <string>
        <fstream>
        <thread>
        <csignal>
        <unistd.h>
        <chrono>
        <cstdlib>
        <sstream>
        <format>

        <httplib.h>
        <websocketpp/config/asio_no_tls.hpp>
        <websocketpp/server.hpp>

        src/Common/Get_Singleton.h
        src/Common/Aliases.h
        src/Utils/Time_Utils.h
        src/Utils/String_Utils.h
        src/Utils/Canvas_Utils.h
        src/Utils/Hash.h

        src/Math_Lib/Size.h
        src/Math_Lib/Size_F.h
        src/Math_Lib/Point_F.h
        src/Math_Lib/Color.h
        src/Math_Lib/Colors.h
)


