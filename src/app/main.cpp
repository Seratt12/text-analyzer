#include <drogon/drogon.h>
#include "routes.h"

int main()
{
    auto& app = drogon::app();

    registerRoutes(app);

    app.loadConfigFile("./config.json").run();
    return EXIT_SUCCESS;
}