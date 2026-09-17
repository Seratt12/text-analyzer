#include "generalHandlers.h"

void general_handlers::GeneralHandler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
)
{
    Json::Value json;
    json["return"] = "Ууу, ответ тут какой-то";
    json["status"] = "ok";

    auto response = drogon::HttpResponse::newHttpJsonResponse(json);

    callback(response);
}

void general_handlers::StatusHandler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
)
{
    Json::Value json;
    json["status"] = "ok";

    auto response = drogon::HttpResponse::newHttpJsonResponse(json);

    callback(response);

}