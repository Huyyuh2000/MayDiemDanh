#include "Variables.hpp"
#include "RFID.hpp"
#include "RTC.hpp"
#include "WebSocketClient.hpp"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WebSocketClient_Init();
  // RTC_Init();
  RFID_Init();
}



void loop() {

  RFID_ReadWriteHandler();
  // RTC_MainFunction();
  RFID_MainFunction();
  WebSocketClient_MainFunction();
}
