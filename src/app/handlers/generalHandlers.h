#pragma once

#include <drogon/drogon.h>

namespace general_handlers
{
using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

void GeneralHandler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
);

void StatusHandler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
);
}