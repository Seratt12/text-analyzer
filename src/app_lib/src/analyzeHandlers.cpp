#include "app_lib/analyzeHandlers.h"

namespace
{
const std::string fieldText = "text";
const std::string fieldTexts = "texts";

constexpr size_t MAX_BATCH_SIZE = 300;
}

std::optional<std::string> analyze_handlers::validateBatchRequest(const Json::Value& body)
{
    if (body.isNull() || !(body.isMember(fieldTexts)))
        return "field 'texts' is required";

    const Json::Value& texts = body[fieldTexts];
    if (!texts.isArray())
        return "field 'texts' must be an array";
    if (texts.empty())
        return "field 'texts' must not be empty";

    if (texts.size() > MAX_BATCH_SIZE)
        return "too many texts (max " + std::to_string(MAX_BATCH_SIZE) + ")";

    return std::nullopt;
}

std::optional<std::string> analyze_handlers::validateRequest(const Json::Value& body)
{
    if (body.isNull() || !(body.isMember(fieldText)))
        return "field 'text' is required";

    const std::string text = body[fieldText].asString();
    if (text.empty())
        return "text is empty";

    return std::nullopt;
}