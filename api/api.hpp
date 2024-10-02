#ifndef Server_LIB_H
#define Server_LIB_H

#include <unordered_map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <functional>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fstream>

#define MAX_CLIENTS 10
#define BUF_SIZE 1024

struct HTTPRequest
{
    std::string Method;
    std::string Path;
};

int Init(int Port)
{
    struct sockaddr_in Addr;
    int ServerFd, Opt = 1;

    ServerFd = socket(AF_INET, SOCK_STREAM, 0);

    if (ServerFd == 0)
    {
        std::cerr << "Could not create socket\n";
        exit(EXIT_FAILURE);
    }

    if (
        setsockopt(ServerFd,
            SOL_SOCKET,
            SO_REUSEADDR | SO_REUSEPORT,
            &Opt,
            sizeof(Opt))
    ){
        std::cerr << "Error applying socket Options\n";

        close(ServerFd);
        exit(EXIT_FAILURE);
    }

    Addr.sin_family = AF_INET;
    Addr.sin_addr.s_addr = INADDR_ANY;
    Addr.sin_port = htons(Port);

    if (bind(ServerFd, (struct sockaddr *)&Addr, sizeof(Addr)) < 0)
    {
        std::cerr << "Bind error\n";
        close(ServerFd);
        exit(EXIT_FAILURE);
    }

    if (listen(ServerFd, MAX_CLIENTS) < 0)
    {
        std::cerr << "Listen error\n";

        close(ServerFd);
        exit(EXIT_FAILURE);
    }

    return ServerFd;
}

HTTPRequest ParseRequest(const std::string& ClientRequest)
{
    HTTPRequest Request;

    char Method[16];
    char Path[256];

    sscanf(ClientRequest.c_str(), "%s %s", Method, Path);

    Request.Method = std::string(Method);
    Request.Path = std::string(Path);

    return Request;
}

void ServeFile(int ClientFd, const std::string& FILE_NAME)
{
    std::ifstream File(FILE_NAME);

    if (!File.is_open())
    {
        const char *Response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";

        send(ClientFd, Response, strlen(Response), 0);

        return;
    }

    std::string Content((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
    std::string Header =
        "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(Content.length()) + "\r\n\r\n";
    
    send(ClientFd, Header.c_str(), Header.length(), 0);
    send(ClientFd, Content.c_str(), Content.length(), 0);
}

void SendResponse(int ClientFd, const std::string& Status, const std::string& Body)
{
    std::string Response = Status + "\r\nContent-Length: " + std::to_string(Body.length()) + "\r\n\r\n" + Body;
    send(ClientFd, Response.c_str(), Response.length(), 0);
}

class Server
{
public:
    Server(int port) : ServerFd(Init(port)) {}
    using Handler = std::function<void(int)>;

    void AddRoute(const std::string& Path, Handler Handler)
    {
        Routes[Path] = Handler;
    }

    void Start()
    {
        int AddressLength = sizeof(sockaddr_in);
        struct sockaddr_in Address;
        char Buffer[BUF_SIZE];

        for (;;)
        {
            int ClientFd = accept(ServerFd, (struct sockaddr*)&Address, (socklen_t*)&AddressLength);

            if (ClientFd < 0)
            {
                std::cerr << "Failed to accept connection\n";
                continue;
            }

            memset(Buffer, 0, BUF_SIZE);
            read(ClientFd, Buffer, BUF_SIZE);
            HTTPRequest Request = ParseRequest(Buffer);

            if (Routes.find(Request.Path) != Routes.end())
                Routes[Request.Path](ClientFd);

            else
                SendResponse(ClientFd, "HTTP/1.1 404 Not Found", "Route not found");

            close(ClientFd);
        }
    }

private:
    int ServerFd;
    std::unordered_map<std::string, Handler> Routes;
};

#define SEND_RESPONSE(ClientFd, Status, Body) SendResponse(ClientFd, Status, Body)
#define SERVE_STATIC_FILE(ClientFd, Filename) ServeFile(ClientFd, Filename)
#define ROUTE(Path, Handler) Server.AddRoute(Path, Handler)

#endif
