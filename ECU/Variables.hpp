#ifndef VARIABLE_H
#define VARIABLE_H

#include <cstring>
#include "Std_Types.hpp"

#define DEBUG
#define DATE_SIZE 3
#define DATA_BLOCK_SIZE_RESERVE 1
// namespace Variable
// {


struct s_dataBlock {
    uint8_t id;
    uint8_t date[DATE_SIZE]; // dd/mm/yyyy
    uint8_t hour;
    uint8_t reserve[DATA_BLOCK_SIZE_RESERVE];
};

typedef s_dataBlock t_dataBlock;

class c_CheckInData_t {
  private:
    t_dataBlock _dataBlock;
    uint8_t * _sector;
    uint8_t * _blockAddr;
  public:
    c_CheckInData_t();
    bool setData(uint8_t id, uint8_t * date, uint8_t hour);
    bool setAddress(uint8_t *  sector, uint8_t * blockAddr);
    bool getData(uint8_t * id, uint8_t * date, uint8_t * hour);
    bool getAddress(uint8_t *  sector, uint8_t * blockAddr);
    bool padding();
    Std_ReturnType setID(uint8_t * id);
    Std_ReturnType getID(uint8_t * id);
    Std_ReturnType setDate(uint8_t * hour, uint8_t * date);
    Std_ReturnType getDate(uint8_t * hour, uint8_t * date);
};

extern c_CheckInData_t c_CheckInData;

// Init array that will store new NUID 
extern uint8_t nuidPICC[4];

extern bool b_RFIDWrite_g;
extern uint8_t WebSocket_Status;

// }
#endif

