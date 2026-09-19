file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
add_executable(axis ${APP_SOURCES})

configure_file(
    ${CMAKE_SOURCE_DIR}/config.json
    ${CMAKE_CURRENT_BINARY_DIR}/config.json
    COPYONLY
)

target_link_libraries(axis
    PRIVATE
        core
        app_lib
        Drogon::Drogon
)