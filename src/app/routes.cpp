#include "routes.h"
#include "handlers/generalHandlers.h"

void registerRoutes(drogon::HttpAppFramework& app)
{
    app.registerHandler("/", &general_handlers::GeneralHandler);
    app.registerHandler("/status", &general_handlers::StatusHandler);
}