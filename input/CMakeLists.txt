add_library(input)

target_sources(input
    PRIVATE
        input.cxx

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        input.hxx
)

target_link_libraries(input
    ${CURSES_LIBRARIES} tinfo
)
