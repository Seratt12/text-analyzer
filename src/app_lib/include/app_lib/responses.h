#pragma once

#include <drogon/drogon.h>

namespace responses
{
drogon::HttpResponsePtr makeJsonOk(const Json::Value& body);
drogon::HttpResponsePtr makeJsonError(
    const std::string& errorText,
    drogon::HttpStatusCode code = drogon::k400BadRequest
);
}