#include "WebSocketClient.hpp"

const char* ssid = "NewYork 24Ghz"; //Enter SSID
const char* password = "UnitedStates#0407"; //Enter Password

const char* websockets_connection_string = "ws://192.168.0.65:8000/"; //Enter server adress

using namespace websockets;

WebsocketsClient client;

void onMessageCallback(WebsocketsMessage message)
{
#ifdef DEBUG
  Serial.println("Got message");
  Serial.println(message.data());
#endif
}

void onEventsCallback(WebsocketsEvent event, String data)
{
  if(event == WebsocketsEvent::ConnectionOpened)
  {
#ifdef DEBUG
    Serial.println("Connnection Opened");
#endif
  }
  else if (event == WebsocketsEvent::ConnectionClosed)
  {
#ifdef DEBUG
    Serial.println("Connnection Closed");
#endif
  } 
  else if (event == WebsocketsEvent::GotPing)
  {
#ifdef DEBUG
    Serial.println("Connnection Closed");
#endif
  } 
  else if (event == WebsocketsEvent::GotPong)
  {
#ifdef DEBUG
    Serial.println("Got a Ping!");
#endif
  } else
  {
    Serial.println("Got a Pong!");
  }
}

void WebSocketClient_Init() 
{
  JsonDocument data;
  websockets::WSInterfaceString payload;
  data["message"] = "Done";
  serializeJson(data, payload);

  WiFi.begin(ssid, password);

  // Wait some time to connect to wifi
  while (WiFi.status() != WL_CONNECTED)
  {
      WiFi.reconnect();
      Serial.print(".");
      delay(10000);
  }

  // run callback when messages are received
  client.onMessage(onMessageCallback);
  
  // run callback when events are occuring
  client.onEvent(onEventsCallback);
  // String data = "Hello Server";
  // Connect to server
  if(client.connect(websockets_connection_string))
  {
    Serial.println("Connected to websocket server");
  }
  else
  {
    while (1)
    {
      Serial.print("Cannot connect: "); Serial.println(websockets_connection_string);
      delay(1000);
    }
  }


  client.send(payload);
  // Send a ping
  client.ping();
}

void WebSocketClient_MainFunction()
{
  switch (WebSocket_Status) 
  {
    case WEBSOCKET_INIT:
      break;
    case WEBSOCKET_PENDING:
      break;
    case WEBSOCKET_SEND:
        JsonDocument payload;
        uint8_t buff[5];
        c_CheckInData.getID(&buff[0]);
        c_CheckInData.getDate(&buff[1], &buff[4]);

        payload["id"] = buff[0];

        payload["day"] = buff[1];
        payload["month"] = buff[2];
        payload["year"] = buff[3];

        payload["hour"] = buff[4];
      
        websockets::WSInterfaceString data; 
        serializeJson(payload, data);

      	client.send(data);
        WebSocket_Status = WEBSOCKET_INIT;
      break;
  }

  client.poll();
}