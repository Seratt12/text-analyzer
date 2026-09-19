add_library(app_lib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/responses.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/handlers/analyzeHandlers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/handlers/generalHandlers.cpp
)

target_include_directories(app_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(app_lib PUBLIC cxx_std_20)

target_link_libraries(app_lib
    PRIVATE 
        JsonCpp::JsonCpp
        Drogon::Drogon
        core
)