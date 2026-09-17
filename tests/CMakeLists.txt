add_executable(core_tests
    text_statistics/getCountSymbolsTest.cpp
    text_statistics/getCountWordsTest.cpp
)

target_link_libraries(core_tests
    PRIVATE
        core
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(core_tests)