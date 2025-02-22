#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include <WString.h>
#include "Variables.hpp"
#include <WiFiMulti.h>
#include <ArduinoJson.h>


void onMessageCallback(websockets::WebsocketsMessage message);
void onEventsCallback(websockets::WebsocketsEvent event, String data);
void WebSocketClient_Init();
void WebSocketClient_MainFunction();


#endif