add_executable(axis main.cpp)

target_link_libraries(axis
    PRIVATE
    core
    Drogon::Drogon
)