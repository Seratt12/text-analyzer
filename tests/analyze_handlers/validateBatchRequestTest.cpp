#include <gtest/gtest.h>
#include "app_lib/handlers/analyzeHandlers.h"

using analyze_handlers::validateBatchRequest;

TEST(ValidateBatchRequest, EmptyObject)
{
    Json::Value body;
    auto err = validateBatchRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "field 'texts' is required");
}

TEST(ValidateBatchRequest, NullValue)
{
    Json::Value body(Json::nullValue);
    auto err = validateBatchRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "field 'texts' is required");
}

TEST(ValidateBatchRequest, TextsNotArray)
{
    Json::Value body;
    body["texts"] = "not an array";
    auto err = validateBatchRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "field 'texts' must be an array");
}

TEST(ValidateBatchRequest, TextsObject)
{
    Json::Value body;
    body["texts"] = Json::Value(Json::objectValue);
    auto err = validateBatchRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "field 'texts' must be an array");
}

TEST(ValidateBatchRequest, TextsEmptyArray)
{
    Json::Value body;
    body["texts"] = Json::Value(Json::arrayValue);
    auto err = validateBatchRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "field 'texts' must not be empty");
}

TEST(ValidateBatchRequest, SingleTextValid)
{
    Json::Value body;
    body["texts"] = Json::Value(Json::arrayValue);
    body["texts"].append("hello");
    auto err = validateBatchRequest(body);
    EXPECT_FALSE(err.has_value());
}

TEST(ValidateBatchRequest, MultipleTextsValid)
{
    Json::Value body;
    body["texts"] = Json::Value(Json::arrayValue);
    body["texts"].append("hello");
    body["texts"].append("world");
    body["texts"].append("Привет");
    auto err = validateBatchRequest(body);
    EXPECT_FALSE(err.has_value());
}

TEST(ValidateBatchRequest, ExactlyMaxSize)
{
    Json::Value body;
    body["texts"] = Json::Value(Json::arrayValue);
    for (size_t i = 0; i < 300; ++i)
    {
        body["texts"].append("text");
    }
    auto err = validateBatchRequest(body);
    EXPECT_FALSE(err.has_value());
}

TEST(ValidateBatchRequest, ExceedsMaxSize)
{
    Json::Value body;
    body["texts"] = Json::Value(Json::arrayValue);
    for (size_t i = 0; i < 301; ++i)
    {
        body["texts"].append("text");
    }
    auto err = validateBatchRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "too many texts (max 300)");
}

TEST(ValidateBatchRequest, ManyElements)
{
    Json::Value body;
    body["texts"] = Json::Value(Json::arrayValue);
    for (size_t i = 0; i < 1000; ++i)
    {
        body["texts"].append("text");
    }
    auto err = validateBatchRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "too many texts (max 300)");
}