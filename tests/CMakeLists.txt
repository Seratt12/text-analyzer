add_executable(core_tests
    text_statistics/getSymbolsCountTest.cpp
    text_statistics/getWordsCountTest.cpp
    text_statistics/getUniqueWordsCount.cpp
)

target_link_libraries(core_tests
    PRIVATE
        core
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(core_tests)