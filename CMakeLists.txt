cmake_minimum_required(VERSION 3.18)
project(mytty LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(mytty
    mytty.c
    nssh.c
    Pty.c
    Session.c
    ShellCommand.c
    konsole_wcwidth.c
    kprocess.c
    kpty.c
    kptydevice.c
    kptyprocess.c
    tools.c
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

target_link_libraries(mytty PRIVATE util)
