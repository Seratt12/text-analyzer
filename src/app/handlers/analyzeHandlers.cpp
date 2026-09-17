#include "analyzeHandlers.h"
#include "responses/responses.h"

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
    result["your_text"] = text;
    callback(responses::makeJsonOk(result));
}