#include "routes.h"
#include "handlers/generalHandlers.h"
#include "handlers/analyzeHandlers.h"

void registerRoutes(drogon::HttpAppFramework& app)
{
    app.registerHandler("/", &general_handlers::generalHandler);
    app.registerHandler("/status", &general_handlers::statusHandler);
    app.registerHandler("/analyze", &analyze_handlers::handler, { drogon::Post });
}