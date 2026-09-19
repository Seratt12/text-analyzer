#include <gtest/gtest.h>
#include <json/json.h>
#include <sstream>
#include <drogon/drogon.h>
#include "app_lib/handlers/generalHandlers.h"

//
// Вспомогательная функция для парсинга тела ответа
//

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
        std::function<void(const drogon::HttpResponsePtr&)>&&)
)
{
    auto request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::Get);

    drogon::HttpResponsePtr captured;
    handler(request, [&captured](const drogon::HttpResponsePtr& response)
        {
            captured = response;
        });
    return captured;
}

}

// 
// generalHandler
// 

TEST(GeneralHandler, ReturnsNonNullResponse)
{
    const auto response = callHandler(&general_handlers::generalHandler);
    ASSERT_NE(response, nullptr);
}

TEST(GeneralHandler, StatusIs200)
{
    const auto response = callHandler(&general_handlers::generalHandler);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);
}

TEST(GeneralHandler, ContentTypeIsJson)
{
    const auto response = callHandler(&general_handlers::generalHandler);
    EXPECT_EQ(response->contentType(), drogon::CT_APPLICATION_JSON);
}

TEST(GeneralHandler, BodyHasReturnField)
{
    const auto response = callHandler(&general_handlers::generalHandler);
    const auto parsed = parseBody(std::string(response->getBody()));
    ASSERT_TRUE(parsed.isMember("return"));
    EXPECT_FALSE(parsed["return"].asString().empty());
}

TEST(GeneralHandler, BodyContainsExpectedText)
{
    const auto response = callHandler(&general_handlers::generalHandler);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(
        parsed["return"].asString(),
        "HTTP-сервис на C++ (Drogon), который принимает текст и возвращает статистику по нему."
    );
}

// 
// statusHandler
// 

TEST(StatusHandler, ReturnsNonNullResponse)
{
    const auto response = callHandler(&general_handlers::statusHandler);
    ASSERT_NE(response, nullptr);
}

TEST(StatusHandler, StatusIs200)
{
    const auto response = callHandler(&general_handlers::statusHandler);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);
}

TEST(StatusHandler, ContentTypeIsJson)
{
    const auto response = callHandler(&general_handlers::statusHandler);
    EXPECT_EQ(response->contentType(), drogon::CT_APPLICATION_JSON);
}

TEST(StatusHandler, BodyHasStatusField)
{
    const auto response = callHandler(&general_handlers::statusHandler);
    const auto parsed = parseBody(std::string(response->getBody()));
    ASSERT_TRUE(parsed.isMember("status"));
    EXPECT_EQ(parsed["status"].asString(), "ok");
}

TEST(StatusHandler, BodyHasOnlyStatusField)
{
    const auto response = callHandler(&general_handlers::statusHandler);
    const auto parsed = parseBody(std::string(response->getBody()));
    EXPECT_EQ(parsed.size(), 1u);
}