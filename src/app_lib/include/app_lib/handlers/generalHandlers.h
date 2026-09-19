#pragma once

#include <drogon/drogon.h>

namespace general_handlers
{
using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

void generalHandler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
);

void statusHandler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
);
}