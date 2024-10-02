#include "../../api/api.hpp"

void InitServer(const int PORT)
{
    Server MNASMD(PORT);

    MNASMD.AddRoute("/", [](int ClientFd) -> void
    {
        SERVE_STATIC_FILE(ClientFd, "public/index.html");
    });

    MNASMD.Start();
}
