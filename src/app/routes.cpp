#include "routes.h"
#include "app_lib/handlers/generalHandlers.h"
#include "app_lib/handlers/analyzeHandlers.h"

void routes::registerRoutes(drogon::HttpAppFramework& app)
{
    app.registerHandler("/", &general_handlers::generalHandler);
    app.registerHandler("/status", &general_handlers::statusHandler);

    app.registerHandler(
        "/analyze",
        &analyze_handlers::handler,
        { drogon::Post }
    );
    app.registerHandler(
        "/analyze/batch",
        &analyze_handlers::handlerBatch,
        { drogon::Post }
    );
}