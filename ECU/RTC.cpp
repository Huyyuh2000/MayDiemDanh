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
  uint16_t year = 0xFFFF;
  uint8_t hour = 0xFF;
  uint8_t minute = 0xFF;
  uint8_t second = 0xFF;
  DateTime now = rtc.now();

  hour = now.hour();
  minute = now.minute();
  second = now.second();
  l_Date[0] = now.day();
  l_Date[1] = now.month();
  l_Date[2] = now.year() - 0xD0;
#ifdef DEBUG
  Serial.print("ESP32 RTC Date Time: ");
  Serial.print(l_Date[0]);
  Serial.print('/');
  Serial.print(l_Date[1]);
  Serial.print('/');
  Serial.print(l_Date[2]);
  Serial.print(" (");
  Serial.print(now.dayOfTheWeek());
  Serial.print(") ");
  Serial.print(hour);
  Serial.print(':');
  Serial.print(minute);
  Serial.print(':');
  Serial.println(second);
  delay(1000);
#endif

  c_CheckInData.setDate(l_Date);
  c_CheckInData.setTime(&hour, &minute, &second);
}