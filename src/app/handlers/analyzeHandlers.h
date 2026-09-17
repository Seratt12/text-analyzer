#pragma once

#include <drogon/drogon.h>

namespace analyze_handlers
{
using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

void handler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
);
}