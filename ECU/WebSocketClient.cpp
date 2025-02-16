#include "WebSocketClient.hpp"

const char* ssid = "NewYork"; //Enter SSID
const char* password = "UnitedState#0407"; //Enter Password

const char* websockets_connection_string = "ws://localhost:8000/"; //Enter server adress

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
  WiFi.begin(ssid, password);

  // Wait some time to connect to wifi
  for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
      Serial.print(".");
      delay(1000);
  }

  // run callback when messages are received
  client.onMessage(onMessageCallback);
  
  // run callback when events are occuring
  client.onEvent(onEventsCallback);


  // Connect to server
  if(!client.connect(websockets_connection_string))
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

  // if (client.handshake()) {
  //   Serial.println("Handshake successful");
  // } else {
  //   Serial.println("Handshake failed.");
  //   while(1) {
  //     // Hang on failure
  //   }  

  String data = "Hello Server";
  // Send a message
  // client(data);
  client.send(data);

  // Send a ping
  client.ping();
}

void WebSocketClient_MainFunction()
{
  switch (WEBSOCKET_SEND) 
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
      break;
  }

  client.poll();
}