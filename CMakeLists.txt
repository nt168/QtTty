cmake_minimum_required(VERSION 3.18)
project(mytty LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(mytty
    mytty.cpp
    Pty.cpp
    Session.cpp
    ShellCommand.cpp
    konsole_wcwidth.cpp
    kprocess.cpp
    kpty.cpp
    kptydevice.cpp
    kptyprocess.cpp
    tools.cpp
)

target_include_directories(mytty PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(mytty
    PRIVATE
        KB_LAYOUT_DIR="/usr/share/mytty"
        COLORSCHEMES_DIR="/usr/share/mytty"
)

if(UNIX)
    target_compile_definitions(mytty
        PRIVATE
            HAVE_POSIX_OPENPT
            HAVE_PTSNAME
            HAVE_GRANTPT
    )
endif()

target_link_libraries(mytty PRIVATE Qt6::Core util)
