#define MAX30100_INT_STATUS     0x00  
#define MAX30100_INT_ENABLE     0x01  
#define MAX30100_FIFO_WR_PTR    0x02  
#define MAX30100_OVRFLOW_CTR    0x03  
#define MAX30100_FIFO_RD_PTR    0x04  
#define MAX30100_FIFO_DATA      0x05  
#define MAX30100_MODE_CONFIG    0x06  
#define MAX30100_SPO2_CONFIG    0x07  // Oximetria
#define MAX30100_LED_CONFIG     0x09  // Pulso
#define MAX30100_TEMP_INTG      0x16  
#define MAX30100_TEMP_FRAC      0x17  
#define MAX30100_REV_ID         0xFE 
#define MAX30100_PART_ID        0xFF  

#define MAX30100_ADDRESS        0x57  

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef enum{
  pw200,    // 200us
  pw400,    // 400us 
  pw800,    // 800us 
  pw1600    // 1600us
}pulseWidth;

typedef enum{
  sr50,    // 50 
  sr100,   // 100
  sr167,   // 167
  sr200,   // 200 
  sr400,   // 400
  sr600,   // 600
  sr800,   // 800 
  sr1000   // 1000 
}sampleRate;

typedef enum{
  i0,    // 0
  i4,    // 4.4mA
  i8,    // 7.6mA
  i11,   // 11.0mA
  i14,   // 14.2mA
  i17,   // 17.4mA
  i21,   // 20.8mA
  i27,   // 27.1mA
  i31,   // 30.6mA
  i34,   // 33.8mA
  i37,   // 37.0mA
  i40,   // 40.2mA
  i44,   // 43.6mA
  i47,   // 46.8mA
  i50    // 50.0mA
}ledCurrent;

class MAX30100 {
public:
  uint16_t IR = 0;     //data
  uint16_t RED = 0;    

  MAX30100();
  void  setLEDs(pulseWidth pw, ledCurrent red, ledCurrent ir); 
  void  setSPO2(sampleRate sr); 
  int   getNumSamp(void);       
  void  readSensor(void);      
  void  shutdown(void);   
  void  reset(void);      
  void  startup(void);    
  int   getRevID(void);   
  int   getPartID(void);  //  ID
  void  begin(pulseWidth pw = pw1600, // comprido
              ledCurrent ir = i50,    // alto
              sampleRate sr = sr100); // baixo
  void  printRegisters(void);

private:
  void    I2CwriteByte(uint8_t address, uint8_t subAddress, uint8_t data);
  uint8_t I2CreadByte(uint8_t address, uint8_t subAddress);
  void    I2CreadBytes(uint8_t address, uint8_t subAddress, uint8_t * dest, uint8_t count);
};
