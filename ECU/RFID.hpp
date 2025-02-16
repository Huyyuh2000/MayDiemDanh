#ifndef RFID_H
#define RFID_H

#include "Std_Types.hpp"
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5
#define RST_PIN 13


void RFID_ReadWriteHandler();
void RFID_Init();
void RFID_MainFunction();
void RFID_ReadUID();
Std_ReturnType RFID_WriteData(uint8_t blockAddr, uint8_t * dataBlock, uint8_t size);
Std_ReturnType RFID_ReadData(uint8_t blockAddr, uint8_t * dataBlock, uint8_t size);


void printHex(uint8_t *buffer, uint8_t bufferSize);
void printDec(uint8_t *buffer, uint8_t bufferSize);
#endif