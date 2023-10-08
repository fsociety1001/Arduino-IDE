#include "Arduino.h"
#include <Wire.h>
#include "Protocentral_MAX30100.h"

MAX30100::MAX30100(){
}

void MAX30100::setLEDs(pulseWidth pw, ledCurrent red, ledCurrent ir){
  uint8_t reg = I2CreadByte(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG);
  reg = reg & 0xFC;
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG, reg | pw); 
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_LED_CONFIG, (red<<4) | ir); // led cfg.
}

void MAX30100::setSPO2(sampleRate sr){
  uint8_t reg = I2CreadByte(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG);
  reg = reg & 0xE3;
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG, reg | (sr<<2)); 
  reg = I2CreadByte(MAX30100_ADDRESS, MAX30100_MODE_CONFIG);
  reg = reg & 0xf8;
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG, reg | 0x03);
}

int MAX30100::getNumSamp(void){
    uint8_t wrPtr = I2CreadByte(MAX30100_ADDRESS, MAX30100_FIFO_WR_PTR);
    uint8_t rdPtr = I2CreadByte(MAX30100_ADDRESS, MAX30100_FIFO_RD_PTR);
    return (abs( 16 + wrPtr - rdPtr ) % 16);
}

void MAX30100::readSensor(void){
  uint8_t temp[4] = {0};  // buffer ttemporario
  I2CreadBytes(MAX30100_ADDRESS, MAX30100_FIFO_DATA, &temp[0], 4);  //fifo
  IR = (temp[0]<<8) | temp[1]; 
  RED = (temp[2]<<8) | temp[3];   
}

void MAX30100::shutdown(void){
  uint8_t reg = I2CreadByte(MAX30100_ADDRESS, MAX30100_MODE_CONFIG); 
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_MODE_CONFIG, reg | 0x80);   
}

void MAX30100::reset(void){
  uint8_t reg = I2CreadByte(MAX30100_ADDRESS, MAX30100_MODE_CONFIG); 
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_MODE_CONFIG, reg | 0x40); 
}

void MAX30100::startup(void){
  uint8_t reg = I2CreadByte(MAX30100_ADDRESS, MAX30100_MODE_CONFIG); 
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_MODE_CONFIG, reg & 0x7F);   
}

int MAX30100::getRevID(void){
  return I2CreadByte(MAX30100_ADDRESS, MAX30100_REV_ID);
}

int MAX30100::getPartID(void){
  return I2CreadByte(MAX30100_ADDRESS, MAX30100_PART_ID);
}

void MAX30100::begin(pulseWidth pw, ledCurrent ir, sampleRate sr){
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_MODE_CONFIG, 0x03); // freq. cardiaca
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_LED_CONFIG, 0XFF);
   I2CwriteByte(MAX30100_ADDRESS, MAX30100_LED_CONFIG, ir<<4|0x0f);
  I2CwriteByte(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG, (sr<<2)|pw);
}

void MAX30100::printRegisters(void){
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_INT_STATUS),  BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_INT_ENABLE),  BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_FIFO_WR_PTR), BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_OVRFLOW_CTR), BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_FIFO_RD_PTR), BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_FIFO_DATA),   BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_MODE_CONFIG), BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG), BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_LED_CONFIG),  BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_TEMP_INTG),   BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_TEMP_FRAC),   BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_REV_ID),      BIN);
  Serial.println(I2CreadByte(MAX30100_ADDRESS, MAX30100_PART_ID),     BIN);
}

void MAX30100::I2CwriteByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
	Wire.beginTransmission(address); 
	Wire.write(subAddress);        
	Wire.write(data);                 
	Wire.endTransmission();         
}

uint8_t MAX30100::I2CreadByte(uint8_t address, uint8_t subAddress)
{
	uint8_t data; //  data
	Wire.beginTransmission(address);         
	Wire.write(subAddress);	                
	Wire.endTransmission(false);             
	Wire.requestFrom(address, (uint8_t) 1); 
	data = Wire.read();                     
	return data;                            
}

void MAX30100::I2CreadBytes(uint8_t address, uint8_t subAddress, uint8_t * dest, uint8_t count)
{
	Wire.beginTransmission(address);  

	Wire.write(subAddress);  
	Wire.endTransmission(false);    
	uint8_t i = 0;
	Wire.requestFrom(address, count); 
	while (Wire.available())
	{
		dest[i++] = Wire.read(); 
	}
}
