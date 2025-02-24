#include "Variables.hpp"

uint8_t WebSocket_Status = WEBSOCKET_INIT;

c_CheckInData_t::c_CheckInData_t()
{
  _dataBlock.id = 0;
  for (size_t i=0; i < DATE_SIZE; i++) {
    _dataBlock.date[i] = 0xFF;
  }
  _dataBlock.hour = 0xFF;
  _dataBlock.minute = 0xFF;
  _dataBlock.second = 0xFF;
  _sector = 0;
  _blockAddr = 0;
}

bool c_CheckInData_t::setData(uint8_t id, uint8_t * date, uint8_t hour)
{
  Std_ReturnType retVal = E_NOT_OK;
  if ((date != nullptr) && (id != NULL) & (hour != NULL))
  {
    _dataBlock.id = id;
    memcpy(_dataBlock.date, date, DATE_SIZE);
    _dataBlock.hour = hour;
    
    retVal = E_OK;
  } else {
    
  }

  return retVal;
}

bool c_CheckInData_t::setAddress(uint8_t *  sector, uint8_t * blockAddr)
{
  Std_ReturnType retVal = E_NOT_OK;
  if ((sector != nullptr) && (blockAddr != nullptr)) 
  {
    _sector = sector;
    _blockAddr = blockAddr;
    retVal = E_OK;
  } else {

  }

  return retVal;
}

bool c_CheckInData_t::getData(uint8_t * id, uint8_t * date, uint8_t * hour)
{
  Std_ReturnType retVal = E_OK;
  *id = _dataBlock.id;
  memcpy(date, _dataBlock.date, DATE_SIZE);
  *hour = _dataBlock.hour;
  return retVal;
}

bool c_CheckInData_t::getAddress(uint8_t * sector, uint8_t * blockAddr)
{
  Std_ReturnType retVal = E_OK;
  sector = _sector;
  blockAddr = _blockAddr;
  return retVal;
}

Std_ReturnType c_CheckInData_t::setDate(uint8_t * date)
{
  Std_ReturnType retVal = E_NOT_OK;
  for (size_t i=0; i<DATE_SIZE; i++)
  {
    _dataBlock.date[i] = date[i];
  }
  retVal = E_OK;
  return retVal;
}

Std_ReturnType c_CheckInData_t::getDate(uint8_t * date)
{
  Std_ReturnType retVal = E_NOT_OK;
  for (size_t i=0; i<DATE_SIZE; i++)
  {
    date[i] = _dataBlock.date[i];
  }
  retVal = E_OK;
  return retVal;
}

Std_ReturnType c_CheckInData_t::setTime(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
  Std_ReturnType retVal = E_NOT_OK;
  _dataBlock.hour = *hour;
  _dataBlock.minute = *minute;
  _dataBlock.second = *second;
  

  retVal = E_OK;
  return retVal;
}

Std_ReturnType c_CheckInData_t::getTime(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
  Std_ReturnType retVal = E_NOT_OK;
  *hour = _dataBlock.hour;
  *minute = _dataBlock.minute;
  *second = _dataBlock.second; 

  retVal = E_OK;
  return retVal;
}

Std_ReturnType c_CheckInData_t::setID(uint8_t * id)
{
  Std_ReturnType retVal = E_NOT_OK;
  _dataBlock.id = *id;
  retVal = E_OK;
  return retVal;
}
Std_ReturnType c_CheckInData_t::getID(uint8_t * id)
{
  Std_ReturnType retVal = E_NOT_OK;
  *id = _dataBlock.id;
  retVal = E_OK;
  return retVal;
}
