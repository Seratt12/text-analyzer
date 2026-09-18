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
    const auto jsonBody = request->getJsonObject();
    if (!jsonBody || !(jsonBody->isMember(fieldText)))
    {
        LOG_ERROR << "no find field 'text'";
        callback(responses::makeJsonError("field 'text' is required"));
        return;
    }

    const std::string text = (*jsonBody)[fieldText].asString();
    if (text.empty())
    {
        LOG_ERROR << "field 'text' is empty";
        callback(responses::makeJsonError("text is empty"));
        return;
    }

    const Json::Value result = GetTextAnalyzeInfo(text);
    callback(responses::makeJsonOk(result));
}

void analyze_handlers::handlerBatch(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
)
{
    auto jsonBody = request->getJsonObject();
    if (!jsonBody || !(jsonBody->isMember(fieldTexts)))
    {
        LOG_ERROR << "no find field 'texts'";
        callback(responses::makeJsonError("field 'texts' is required"));
        return;
    }

    const Json::Value& texts = (*jsonBody)[fieldTexts];
    if (!texts.isArray() || texts.empty())
    {
        LOG_ERROR << "field 'texts' is empty or not array";
        callback(responses::makeJsonError("texts is empty or not array"));
        return;
    }

    if (texts.size() > MAX_BATCH_SIZE)
    {
        callback(responses::makeJsonError("too many texts (max " + std::to_string(MAX_BATCH_SIZE) + ")"));
        return;
    }

    Json::Value resultArray(Json::arrayValue);
    for (const auto& textJson : texts)
    {
        if (!textJson.isString())
        {
            Json::Value jsonReturn;
            jsonReturn["error"] = "element is not a string";
            resultArray.append(jsonReturn);
            continue;
        }
        const std::string text = textJson.asString();
        const Json::Value resultElement = GetTextAnalyzeInfo(text);
        resultArray.append(resultElement);
    }
    callback(responses::makeJsonOk(resultArray));
}