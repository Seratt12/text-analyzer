#include <gtest/gtest.h>
#include <json/json.h>
#include <drogon/drogon.h>
#include "app_lib/responses.h"

TEST(ResponsesMakeJsonOk, ReturnsNonNull)
{
    Json::Value body;
    body["status"] = "ok";
    const auto response = responses::makeJsonOk(body);
    ASSERT_NE(response, nullptr);
}

TEST(ResponsesMakeJsonOk, StatusIs200)
{
    Json::Value body;
    body["status"] = "ok";
    const auto response = responses::makeJsonOk(body);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);
}

TEST(ResponsesMakeJsonOk, ContentTypeIsJson)
{
    Json::Value body;
    body["status"] = "ok";
    const auto response = responses::makeJsonOk(body);
    EXPECT_EQ(response->contentType(), drogon::CT_APPLICATION_JSON);
}

TEST(ResponsesMakeJsonOk, BodyContainsData)
{
    Json::Value body;
    body["status"] = "ok";
    body["value"] = 42;
    const auto response = responses::makeJsonOk(body);

    const std::string respBody(response->getBody());
    EXPECT_FALSE(respBody.empty());
    Json::Value parsed;
    Json::Reader reader{ };
    ASSERT_TRUE(reader.parse(respBody, parsed));
    EXPECT_EQ(parsed["status"].asString(), "ok");
    EXPECT_EQ(parsed["value"].asInt(), 42);
}

TEST(ResponsesMakeJsonOk, EmptyBody)
{
    Json::Value body;
    const auto response = responses::makeJsonOk(body);
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);
}

TEST(ResponsesMakeJsonOk, CyrillicInBody)
{
    Json::Value body;
    body["text"] = "Привет, мир!";
    const auto response = responses::makeJsonOk(body);

    const std::string bodyResponse(response->getBody());
    Json::Value parsed;
    Json::Reader reader{ };
    ASSERT_TRUE(reader.parse(bodyResponse, parsed));
    EXPECT_EQ(parsed["text"].asString(), "Привет, мир!");
}