CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
project(file-mgr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Curses REQUIRED)

add_subdirectory(filesystem)
add_subdirectory(display)
add_subdirectory(input)
add_subdirectory(eventlistener)

add_executable(file-mgr-app main.cxx)

target_link_libraries(display
    filesystemTypes
)

target_link_libraries(displayUtils
    filesystemTypes
)

target_link_libraries(file-mgr-app
    filesystemTypes
    filesystemUtils
    filesystem
    displayTypes
    displayUtils
    display
    input
    eventlistener
    ${CURSES_LIBRARIES} tinfo
)
