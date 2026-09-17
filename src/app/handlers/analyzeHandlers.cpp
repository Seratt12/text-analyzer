#include "analyzeHandlers.h"
#include "responses/responses.h"
#include "core/textStatistics.h"

void analyze_handlers::handler(
    const drogon::HttpRequestPtr& request,
    Callback&& callback
)
{
    auto jsonBody = request->getJsonObject();
    if (!jsonBody || !(jsonBody->isMember("text")))
    {
        callback(responses::makeJsonError("field 'text' is required"));
        return;
    }

    std::string text = (*jsonBody)["text"].asString();
    if (text.empty())
    {
        callback(responses::makeJsonError("text is empty"));
        return;
    }

    Json::Value result;

    auto info = text_analyzer::getFullInfo(text);

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
    callback(responses::makeJsonOk(result));
}