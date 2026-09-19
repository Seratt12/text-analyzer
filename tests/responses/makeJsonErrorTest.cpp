#include <gtest/gtest.h>
#include <json/json.h>
#include <drogon/drogon.h>
#include "app_lib/responses.h"

TEST(ResponsesMakeJsonError, ReturnsNonNull)
{
    const auto response = responses::makeJsonError("something went wrong");
    ASSERT_NE(response, nullptr);
}

TEST(ResponsesMakeJsonError, DefaultStatusCodeIs400)
{
    const auto response = responses::makeJsonError("error");
    EXPECT_EQ(response->getStatusCode(), drogon::k400BadRequest);
}

TEST(ResponsesMakeJsonError, CustomStatusCode)
{
    const auto response = responses::makeJsonError("internal error", drogon::k500InternalServerError);
    EXPECT_EQ(response->getStatusCode(), drogon::k500InternalServerError);
}

TEST(ResponsesMakeJsonError, CustomStatusCode404)
{
    const auto response = responses::makeJsonError("not found", drogon::k404NotFound);
    EXPECT_EQ(response->getStatusCode(), drogon::k404NotFound);
}

TEST(ResponsesMakeJsonError, ContentTypeIsJson)
{
    const auto response = responses::makeJsonError("error");
    EXPECT_EQ(response->contentType(), drogon::CT_APPLICATION_JSON);
}

TEST(ResponsesMakeJsonError, BodyContainsError)
{
    const auto response = responses::makeJsonError("field 'text' is required");

    const std::string body(response->getBody());
    Json::Value parsed;
    Json::Reader reader{ };
    ASSERT_TRUE(reader.parse(body, parsed));
    EXPECT_EQ(parsed["error"].asString(), "field 'text' is required");
}

TEST(ResponsesMakeJsonError, CyrillicError)
{
    const auto response = responses::makeJsonError("поле 'text' обязательно");

    const std::string body(response->getBody());
    Json::Value parsed;
    Json::Reader reader{ };
    ASSERT_TRUE(reader.parse(body, parsed));
    EXPECT_EQ(parsed["error"].asString(), "поле 'text' обязательно");
}

TEST(ResponsesMakeJsonError, EmptyErrorText)
{
    const auto response = responses::makeJsonError("");
    ASSERT_NE(response, nullptr);

    const std::string body(response->getBody());
    Json::Value parsed;
    Json::Reader reader{ };
    ASSERT_TRUE(reader.parse(body, parsed));
    EXPECT_EQ(parsed["error"].asString(), "");
}