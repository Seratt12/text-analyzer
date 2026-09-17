add_library(core STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(core PUBLIC cxx_std_20)