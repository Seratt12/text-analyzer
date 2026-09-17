file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
add_executable(axis ${APP_SOURCES})

target_link_libraries(axis
    PRIVATE
        core
        Drogon::Drogon
)