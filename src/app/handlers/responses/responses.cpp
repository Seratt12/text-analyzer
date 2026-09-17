#include "responses.h"

drogon::HttpResponsePtr responses::makeJsonOk(const Json::Value& body)
{
    auto response = drogon::HttpResponse::newHttpJsonResponse(body);
    return response;
}

drogon::HttpResponsePtr responses::makeJsonError(
    const std::string& errorText,
    drogon::HttpStatusCode code /* = drogon::k400BadRequest */
)
{
    Json::Value jsonReturn;
    jsonReturn["error"] = errorText;

    auto response = drogon::HttpResponse::newHttpJsonResponse(jsonReturn);
    response->setStatusCode(code);
    return response;
}