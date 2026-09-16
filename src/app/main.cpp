#include <drogon/drogon.h>

void GeneralResponse(
    const drogon::HttpRequestPtr& request,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback
)
{
    auto response = drogon::HttpResponse::newHttpResponse(
        drogon::k200OK,
        drogon::CT_TEXT_PLAIN
    );

    response->setBody("Ууу, ответ тут какой-то");

    callback(response);
}

int main()
{
    auto& app = drogon::app();

    app.registerHandler("/", &GeneralResponse);

    app.loadConfigFile("./config.json").run();

    return EXIT_SUCCESS;
}