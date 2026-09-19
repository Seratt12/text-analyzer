#pragma once

#include <drogon/drogon.h>
#include <json/json.h>

namespace analyze_handlers
{
using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

void handler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
);

void handlerBatch(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
);

std::optional<std::string> validateBatchRequest(const Json::Value& body);
std::optional<std::string> validateRequest(const Json::Value& body);
}