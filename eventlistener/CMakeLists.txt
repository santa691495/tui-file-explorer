add_library(eventlistener)

target_sources(eventlistener
    PRIVATE
        eventlistener.cxx

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        eventlistener.hxx
)
