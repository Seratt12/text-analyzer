#include <gtest/gtest.h>
#include "app_lib/handlers/analyzeHandlers.h"

using analyze_handlers::validateRequest;

TEST(ValidateRequest, EmptyObject)
{
    Json::Value body;
    auto err = validateRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "field 'text' is required");
}

TEST(ValidateRequest, NullValue)
{
    Json::Value body(Json::nullValue);
    auto err = validateRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "field 'text' is required");
}

TEST(ValidateRequest, TextEmpty)
{
    Json::Value body;
    body["text"] = "";
    auto err = validateRequest(body);
    ASSERT_TRUE(err.has_value());
    EXPECT_EQ(*err, "text is empty");
}

TEST(ValidateRequest, TextValid)
{
    Json::Value body;
    body["text"] = "hello world";
    auto err = validateRequest(body);
    EXPECT_FALSE(err.has_value());
}

TEST(ValidateRequest, TextCyrillic)
{
    Json::Value body;
    body["text"] = "Привет, мир!";
    auto err = validateRequest(body);
    EXPECT_FALSE(err.has_value());
}