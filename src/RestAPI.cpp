#include "RestAPI.h"

// Includes for the server
#include <HTTPSServer.hpp>
#include <SSLCert.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include <util.hpp>
#include "Screen.h"

// We will use wifi
#include <WiFi.h>

// We will use SPIFFS and FS
#include <SPIFFS.h>
#include <FS.h>

// We use JSON as data format. Make sure to have the lib available
#include <ArduinoJson.h>

// Working with c++ strings
#include <string>

using namespace httpsserver;

void handleTextEvent(HTTPRequest *req, HTTPResponse *res)
{
    Serial.println("HandleTextEvent");
    // Access the parameter from the URL. See Parameters example for more details on this
    ResourceParameters *params = req->getParams();
    String str = params->getPathParameter(0).c_str();

    Serial.println(str);
    PutText(str, 0, 0, 2);
    // And return a successful response without body
    res->setStatusCode(204);
    res->setStatusText("No Content");
}

void HandleSetPinEvent(HTTPRequest *req, HTTPResponse *res)
{
    Serial.println("HandleSetPinEvent");
    // Access the parameter from the URL. See Parameters example for more details on this
    ResourceParameters *params = req->getParams();
    size_t pin = std::atoi(params->getPathParameter(0).c_str());
    size_t val = std::atoi(params->getPathParameter(1).c_str());

    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
    String str = "Set pin " + String(pin) + " to " + String(val);
    int nval = digitalRead(pin);
    String str2 = " is: " + String(nval);

    Serial.println(str + str2);
    PutText("                        ", 0, 0, 2);
    PutText(str, 0, 0, 2);
    // And return a successful response without body
    res->setStatusCode(204);
    res->setStatusText("No Content");
}

void RegisterEvents(HTTPServer *inServer)
{
    inServer->registerNode(new ResourceNode("/api/text/*", "GET", &handleTextEvent));
    inServer->registerNode(new ResourceNode("/api/pin/*/*", "GET", &HandleSetPinEvent));
}
