add_library(filesystemTypes)

target_sources(filesystemTypes
    PRIVATE
        filesystemtypes.cxx

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        filesystemtypes.hxx
)

add_library(filesystemUtils)

target_sources(filesystemUtils
    PRIVATE
        filesystemutils.cxx

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        filesystemutils.hxx
)

target_link_libraries(filesystemUtils
    filesystemTypes
)

add_library(filesystem)

target_sources(filesystem
    PRIVATE
        filesystem.cxx

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        filesystem.hxx
)

target_link_libraries(filesystem
    filesystemTypes
    filesystemUtils
)
