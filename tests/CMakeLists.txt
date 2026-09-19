add_executable(core_tests
    text_statistics/getSymbolsCountTest.cpp
    text_statistics/getWordsCountTest.cpp
    text_statistics/getUniqueWordsCountTest.cpp
    text_statistics/getSentencesCountTest.cpp
    text_statistics/getAverageWordLengthTest.cpp
    text_statistics/getTopWordsTest.cpp
    text_statistics/splitWordsTest.cpp
    analyze_handlers/validateBatchRequestTest.cpp
    analyze_handlers/validateRequestTest.cpp
)

target_link_libraries(core_tests
    PRIVATE
        core
        app_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(core_tests)