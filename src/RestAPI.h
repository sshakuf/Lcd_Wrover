
// Includes for the server
#include <HTTPSServer.hpp>
#include <SSLCert.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include <util.hpp>

#include <string>

using namespace httpsserver;

void RegisterEvents(HTTPServer *inServer);
void handleTextEvent(HTTPRequest *req, HTTPResponse *res);
