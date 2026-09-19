#include <gtest/gtest.h>
#include <json/json.h>
#include <sstream>
#include <drogon/drogon.h>
#include "app_lib/handlers/analyzeHandlers.h"

namespace
{

Json::Value parseBody(const std::string& body)
{
    Json::Value parsed;
    Json::CharReaderBuilder builder;
    std::string errors;
    std::istringstream stream{ body };
    EXPECT_TRUE(Json::parseFromStream(builder, stream, &parsed, &errors)) << errors;
    return parsed;
}

drogon::HttpResponsePtr callHandler(
    void (*handler)(const drogon::HttpRequestPtr&,
        std::function<void(const drogon::HttpResponsePtr&)>&&),
    const std::string& jsonBody
)
{
    auto request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::Post);
    request->setContentTypeCode(drogon::CT_APPLICATION_JSON);
    request->setBody(jsonBody);

    drogon::HttpResponsePtr captured;
    handler(request, [&captured](const drogon::HttpResponsePtr& response)
        {
            captured = response;
        });
    return captured;
}

drogon::HttpResponsePtr callHandlerNoBody(
    void (*handler)(const drogon::HttpRequestPtr&,
        std::function<void(const drogon::HttpResponsePtr&)>&&)
)
{
    auto request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::Post);

    drogon::HttpResponsePtr captured;
    handler(request, [&captured](const drogon::HttpResponsePtr& response)
        {
            captured = response;
        });
    return captured;
}

}

//
// handler — POST /analyze
//

TEST(AnalyzeHandler, MissingJsonBody)
{
    const auto response = callHandlerNoBody(&analyze_handlers::handler);
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["error"].asString(), "invalid or missing JSON body");
}

TEST(AnalyzeHandler, MissingTextField)
{
    const auto response = callHandler(&analyze_handlers::handler, "{}");
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["error"].asString(), "field 'text' is required");
}

TEST(AnalyzeHandler, EmptyText)
{
    const auto response = callHandler(&analyze_handlers::handler, R"({"text": ""})");
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["error"].asString(), "text is empty");
}

TEST(AnalyzeHandler, ValidSimpleText)
{
    const auto response = callHandler(&analyze_handlers::handler, R"({"text": "hello world"})");
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);

    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["chars"].asUInt(), 11u);
    EXPECT_EQ(parsed["words"].asUInt(), 2u);
    EXPECT_EQ(parsed["source_text"].asString(), "hello world");
}

TEST(AnalyzeHandler, ValidCyrillicText)
{
    const auto response = callHandler(
        &analyze_handlers::handler,
        R"({"text": "Привет, мир!"})"
    );
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);

    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["chars"].asUInt(), 12u);
    EXPECT_EQ(parsed["words"].asUInt(), 2u);
    EXPECT_EQ(parsed["unique_words"].asUInt(), 2u);
    EXPECT_EQ(parsed["source_text"].asString(), "Привет, мир!");
}

TEST(AnalyzeHandler, TopWordsPresent)
{
    const auto response = callHandler(
        &analyze_handlers::handler,
        R"({"text": "hello hello world"})"
    );
    ASSERT_NE(response, nullptr);
    const auto parsed = parseBody(std::string(response->getBody()));
    ASSERT_TRUE(parsed["top_words"].isArray());
    ASSERT_GE(parsed["top_words"].size(), 1u);
    EXPECT_EQ(parsed["top_words"][0]["word"].asString(), "hello");
    EXPECT_EQ(parsed["top_words"][0]["count"].asUInt(), 2u);
}

// 
// handlerBatch — POST /analyze/batch
// 

TEST(AnalyzeBatchHandler, MissingJsonBody)
{
    const auto response = callHandlerNoBody(&analyze_handlers::handlerBatch);
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["error"].asString(), "invalid or missing JSON body");
}

TEST(AnalyzeBatchHandler, MissingTextsField)
{
    const auto response = callHandler(&analyze_handlers::handlerBatch, "{}");
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["error"].asString(), "field 'texts' is required");
}

TEST(AnalyzeBatchHandler, TextsNotArray)
{
    const auto response = callHandler(
        &analyze_handlers::handlerBatch,
        R"({"texts": "not an array"})"
    );
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["error"].asString(), "field 'texts' must be an array");
}

TEST(AnalyzeBatchHandler, TextsEmpty)
{
    const auto response = callHandler(
        &analyze_handlers::handlerBatch,
        R"({"texts": []})"
    );
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["error"].asString(), "field 'texts' must not be empty");
}

TEST(AnalyzeBatchHandler, SingleText)
{
    const auto response = callHandler(
        &analyze_handlers::handlerBatch,
        R"({"texts": ["hello world"]})"
    );
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);

    const auto parsed = parseBody(std::string(response->getBody()));
    ASSERT_TRUE(parsed.isArray());
    ASSERT_EQ(parsed.size(), 1u);
    EXPECT_EQ(parsed[0]["words"].asUInt(), 2u);
    EXPECT_EQ(parsed[0]["source_text"].asString(), "hello world");
}

TEST(AnalyzeBatchHandler, MultipleTexts)
{
    const auto response = callHandler(
        &analyze_handlers::handlerBatch,
        R"({"texts": ["hello world", "Привет, мир!", "one two three"]})"
    );
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);

    const auto parsed = parseBody(std::string(response->getBody()));
    ASSERT_TRUE(parsed.isArray());
    ASSERT_EQ(parsed.size(), 3u);
    EXPECT_EQ(parsed[0]["words"].asUInt(), 2u);
    EXPECT_EQ(parsed[1]["words"].asUInt(), 2u);
    EXPECT_EQ(parsed[2]["words"].asUInt(), 3u);
}

TEST(AnalyzeBatchHandler, OrderPreserved)
{
    const auto response = callHandler(
        &analyze_handlers::handlerBatch,
        R"({"texts": ["first", "second", "third"]})"
    );
    ASSERT_NE(response, nullptr);
    const auto parsed = parseBody(std::string(response->getBody()));
    ASSERT_EQ(parsed.size(), 3u);
    EXPECT_EQ(parsed[0]["source_text"].asString(), "first");
    EXPECT_EQ(parsed[1]["source_text"].asString(), "second");
    EXPECT_EQ(parsed[2]["source_text"].asString(), "third");
}

TEST(AnalyzeBatchHandler, ElementNotString)
{
    const auto response = callHandler(
        &analyze_handlers::handlerBatch,
        R"({"texts": ["hello", 42, "world"]})"
    );
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["error"].asString(), "all elements of 'texts' must be strings");
}

TEST(AnalyzeBatchHandler, ExactlyMaxSize)
{
    std::string body = R"({"texts": [)";
    for (size_t i = 0; i < 300; ++i)
    {
        if (i > 0) body += ",";
        body += R"("text")";
    }
    body += "]}";

    const auto response = callHandler(&analyze_handlers::handlerBatch, body);
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);

    const auto parsed = parseBody(std::string(response->getBody()));
    ASSERT_TRUE(parsed.isArray());
    EXPECT_EQ(parsed.size(), 300u);
}

TEST(AnalyzeBatchHandler, ExceedsMaxSize)
{
    std::string body = R"({"texts": [)";
    for (size_t i = 0; i < 301; ++i)
    {
        if (i > 0) body += ",";
        body += R"("text")";
    }
    body += "]}";

    const auto response = callHandler(&analyze_handlers::handlerBatch, body);
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed["error"].asString(), "too many texts (max 300)");
}