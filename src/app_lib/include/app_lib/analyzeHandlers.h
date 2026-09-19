#pragma once

#include <optional>
#include <string>
#include <json/json.h>

namespace analyze_handlers
{
std::optional<std::string> validateBatchRequest(const Json::Value& body);
std::optional<std::string> validateRequest(const Json::Value& body);
}