#include "analyzeHandlers.h"
#include "responses/responses.h"
#include "core/textStatistics.h"

namespace
{
const inline std::string fieldText = "text";
const inline std::string fieldTexts = "texts";

Json::Value GetTextAnalyzeInfo(std::string text)
{
    LOG_INFO << "GetTextAnalyzeInfo with text: " << text.c_str();
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
        LOG_ERROR << "analyze_handlers::handler no find field 'text'";
        callback(responses::makeJsonError("field 'text' is required"));
        return;
    }

    const std::string text = (*jsonBody)[fieldText].asString();
    if (text.empty())
    {
        LOG_ERROR << "analyze_handlers::handler field 'text' is empty";
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
        LOG_ERROR << "analyze_handlers::handlerBatch no find field 'texts'";
        callback(responses::makeJsonError("field 'texts' is required"));
        return;
    }

    Json::Value texts = (*jsonBody)[fieldTexts];
    if (texts.empty() || !texts.isArray() || texts.size() == 0)
    {
        LOG_ERROR << "analyze_handlers::handlerBatch field 'texts' is empty or not array";
        callback(responses::makeJsonError("texts is empty or not array"));
        return;
    }

    Json::Value result;

    for (const auto& textJson : texts)
    {
        const std::string text = textJson.asString();
        const Json::Value resultElement = GetTextAnalyzeInfo(text);
        result.append(resultElement);
    }
    callback(responses::makeJsonOk(result));
}