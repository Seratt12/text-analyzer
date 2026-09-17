add_library(core STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/textStatistics.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(core PRIVATE Boost::locale)

target_compile_features(core PUBLIC cxx_std_20)