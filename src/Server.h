#ifndef SERVER_H
#define SERVER_H

#include <HTTPSServer.hpp>

using namespace httpsserver;

extern HTTPServer *secureServer;

// void ConnectServer();
void setupServer();
void Serverloop();

#endif