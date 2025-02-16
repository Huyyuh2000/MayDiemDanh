#include "RFID.hpp"
#include "Variables.hpp"
#include "cstring"

using namespace std;

c_CheckInData_t c_CheckInData;
bool b_RFIDWrite_g = false;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 

uint8_t nuidPICC[4];

void RFID_Init() {
  for (size_t i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  SPI.begin();
  rfid.PCD_Init();
}

void RFID_ReadWriteHandler()
{
  String c;
  char * write = "w";
  char * read = "r";
  char * delim = ";";
  uint8_t delim_i = 0;
  String id_str;

  if (Serial.available())
  {
    c = Serial.readStringUntil('\n');
  }
  char command = c[0];
  if (command == write[0])
  {
    b_RFIDWrite_g = true;
    for (size_t i=0; i<c.length();i++) // find index of delimeter
    {
      if (c[i] == delim[0])
      {
        delim_i = i;
      }
    }

    for (size_t i=delim_i+1; i<c.length();i++) // take id after delimeter
    {
      id_str.concat(c[i]);
    }

    uint8_t t = id_str.toInt();
    c_CheckInData.setID(&t);
    Serial.println(t);
  }
  else if (command == read[0])
  {
    b_RFIDWrite_g = false;
    Serial.println("2");
  } 
  else
  {

  }
  delay(1000);
}

void RFID_MainFunction() 
{
  uint8_t readID[18];
  uint8_t writeID = 0xFF; 
  MFRC522::StatusCode status;

  if (!rfid.PICC_IsNewCardPresent())
  {
    return;
  }

  if ( ! rfid.PICC_ReadCardSerial())
  {
    return;
  }

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }


  if (b_RFIDWrite_g)
  {
    c_CheckInData.getID(&writeID);
    RFID_WriteData(1, &writeID, 1u);
  } 
  else
  {
    Serial.println(F("**Card Detected:**"));

    //-------------------------------------------

    rfid.PICC_DumpDetailsToSerial(&(rfid.uid)); //dump some details about the card

    RFID_ReadData(1, readID, 18u);
    c_CheckInData.setID(&readID[0]);
  #ifdef DEBUG
    Serial.print("ID from block 1: ");
    Serial.println(readID[0], HEX);
  #endif
    WebSocket_Status = WEBSOCKET_SEND;
  }
  

    // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void RFID_ReadUID() {
    if (rfid.uid.uidByte[0] != nuidPICC[0] ||
        rfid.uid.uidByte[1] != nuidPICC[1] ||
        rfid.uid.uidByte[2] != nuidPICC[2] ||
        rfid.uid.uidByte[4] != nuidPICC[4])
    {
#ifdef DEBUG
      Serial.println("A new card has been deteced.");
#endif
      for (size_t i=0; i<4; i++)
      {
        nuidPICC[i] = rfid.uid.uidByte[i];
      }

#ifdef DEBUG
      Serial.println(F("The NUID tag is:"));
      Serial.print(F("In hex: "));
      printHex(rfid.uid.uidByte, rfid.uid.size);
      Serial.println();
      Serial.print(F("In dec: "));
      printDec(rfid.uid.uidByte, rfid.uid.size);
      Serial.println();
#endif
    }
}

Std_ReturnType RFID_ReadData(uint8_t blockAddr, uint8_t * dataBlock, uint8_t size)
{
  Std_ReturnType retVal = E_NOT_OK;
  MFRC522::StatusCode status;

  status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(rfid.GetStatusCodeName(status));
  }
  else
  {
    if (dataBlock != nullptr)
    {
  #ifdef DEBUG
      Serial.print("Reading data from block: "); 
      Serial.println(blockAddr);
  #endif
      status = (MFRC522::StatusCode)rfid.MIFARE_Read(blockAddr, dataBlock, &size);
      if (status != MFRC522::STATUS_OK)
      {
        retVal = E_NOT_OK;
      } 
      else 
      {
        retVal = E_OK;
      }
    }
    else
    {
  #ifdef DEBUG
      Serial.println("Null pointer");
  #endif
    }
  }

  return retVal;
}

Std_ReturnType RFID_WriteData(uint8_t blockAddr, uint8_t * dataBlock, uint8_t size)
{
  Std_ReturnType retVal = E_NOT_OK;
  MFRC522::StatusCode status;

  status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(rfid.GetStatusCodeName(status));
  }
  else
  {
#ifdef DEBUG
    Serial.println("Writing data into block: "); Serial.println(blockAddr);
#endif

    uint8_t buf[16];

    for (size_t i=0; i<16; i++)
    {
      if (i<size)
      {
        buf[i] = dataBlock[i];
      }
      else
      {
        buf[i] = 0xFF;
      }
    }

    status = (MFRC522::StatusCode)rfid.MIFARE_Write(blockAddr, buf, 16);
    if (status != MFRC522::STATUS_OK)
    {
      retVal = E_NOT_OK;
    } 
    else 
    {
      retVal = E_OK;
      b_RFIDWrite_g = false;
    }
  }

  return retVal;
}

void printHex(uint8_t *buffer, uint8_t bufferSize) {
  for (size_t i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(uint8_t *buffer, uint8_t bufferSize) {
  for (size_t i = 0; i < bufferSize; i++) {
    Serial.print(' ');
    Serial.print(buffer[i], DEC);
  }
}

