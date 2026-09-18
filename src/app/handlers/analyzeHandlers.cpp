#include "analyzeHandlers.h"
#include "responses/responses.h"
#include "core/textStatistics.h"

namespace
{
const std::string fieldText = "text";
const std::string fieldTexts = "texts";

constexpr size_t MAX_BATCH_SIZE = 300;

Json::Value GetTextAnalyzeInfo(const std::string& text)
{
#ifndef NDEBUG
    LOG_DEBUG << "GetTextAnalyzeInfo with text: " << text;
#endif
    auto info = text_analyzer::getFullInfo(text);

    Json::Value result;
    result["source_text"] = text;
    result["chars"] = info.chars;
    result["words"] = info.words;
    result["unique_words"] = info.uniqueWords;
    result["sentences"] = info.sentences;
    result["average_word_length"] = info.average_word_length;
    Json::Value wordsJson{ Json::arrayValue };
    for (const auto& word : info.topWords)
    {
        Json::Value wordJson;
        wordJson["word"] = word.first;
        wordJson["count"] = static_cast<Json::UInt64>(word.second);
        wordsJson.append(wordJson);
    }
    result["top_words"] = wordsJson;
    return result;
}
}

void analyze_handlers::handler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
)
{
    auto jsonBody = request->getJsonObject();
    if (!jsonBody)
    {
        callback(responses::makeJsonError("invalid or missing JSON body"));
        return;
    }

    if (auto err = validateRequest(*jsonBody))
    {
        LOG_ERROR << *err;
        callback(responses::makeJsonError(*err));
        return;
    }

    const Json::Value result = GetTextAnalyzeInfo((*jsonBody)[fieldText].asString());
    callback(responses::makeJsonOk(result));
}

void analyze_handlers::handlerBatch(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
)
{
    auto jsonBody = request->getJsonObject();
    if (!jsonBody)
    {
        callback(responses::makeJsonError("invalid or missing JSON body"));
        return;
    }

    if (auto err = validateBatchRequest(*jsonBody))
    {
        LOG_ERROR << *err;
        callback(responses::makeJsonError(*err));
        return;
    }

    Json::Value resultArray(Json::arrayValue);
    for (const auto& textJson : (*jsonBody)[fieldTexts])
    {
        if (!textJson.isString())
        {
            callback(responses::makeJsonError("all elements of 'texts' must be strings"));
            return;
        }
        const std::string text = textJson.asString();
        Json::Value resultElement = GetTextAnalyzeInfo(text);
        resultArray.append(resultElement);
    }
    callback(responses::makeJsonOk(resultArray));
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