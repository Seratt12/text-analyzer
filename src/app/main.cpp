#include <drogon/drogon.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "routes.h"

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    auto& app = drogon::app();

    routes::registerRoutes(app);

    app.loadConfigFile("./config.json").run();
    return EXIT_SUCCESS;
}