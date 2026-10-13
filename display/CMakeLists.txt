add_library(displayTypes INTERFACE)
target_include_directories(displayTypes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(displayTypes INTERFACE displaytypes.hxx)

add_library(displayUtils)

target_sources(displayUtils
    PRIVATE
        displayutils.cxx

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        displayutils.hxx
)

add_library(display)

target_sources(display
    PRIVATE
        display.cxx

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        display.hxx
)

target_link_libraries(display
    displayTypes
    displayUtils
    ${CURSES_LIBRARIES} tinfo
)
