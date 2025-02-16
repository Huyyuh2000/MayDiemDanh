#include "RTC.hpp"
#include "Variables.hpp"

RTC_DS3231 rtc;

void RTC_Init() 
{
  if (!rtc.begin())
  {
#ifdef DEBUG
    Serial.println("RTC module is NOT found");
#endif
    while(1);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void RTC_MainFunction()
{
  // Get date and time from server
  uint8_t l_Date[DATE_SIZE] = {0};
  uint8_t hour = 0xFF;
  DateTime now = rtc.now();

  hour = now.hour();
  l_Date[0] = now.day();
  l_Date[1] = now.month();
  l_Date[2] = now.year();
#ifdef DEBUG
  Serial.print("ESP32 RTC Date Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(now.dayOfTheWeek());
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  delay(1000);
#endif

  c_CheckInData.setDate(&hour, l_Date);
}