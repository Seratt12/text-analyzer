#include "app_lib/handlers/generalHandlers.h"

void general_handlers::generalHandler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
)
{
    Json::Value json;
    json["return"] = "HTTP-сервис на C++ (Drogon), который принимает текст и возвращает статистику по нему.";

    auto response = drogon::HttpResponse::newHttpJsonResponse(json);

    callback(response);
}

void general_handlers::statusHandler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
)
{
    Json::Value json;
    json["status"] = "ok";

    auto response = drogon::HttpResponse::newHttpJsonResponse(json);

    callback(response);

}