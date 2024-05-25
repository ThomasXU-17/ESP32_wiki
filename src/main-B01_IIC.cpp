#include <Arduino.h>
#include <Wire.h>


#ifndef IIC_SAMPLE_ESP32S3
#define IICPIN_SDA 8
#define IICPIN_SCL 9
#endif

union byte2int32{
  byte array[4];
  int32_t int32;
};

void receive_iic_data(byte addr, byte cmd, byte *data, byte datalen){
  Wire.beginTransmission(addr);     //发送I2C协议的起始信号，器件地址为0X5A 
  Wire.write(cmd);                  //写入要操作的寄存器地址
  Wire.endTransmission(false);
  if (Wire.requestFrom((uint16_t)addr, (uint8_t)datalen, (bool)true) == datalen){
    for (int i = 0; i < datalen; i++){
      data[datalen - i -1] = Wire.read();
    }
  }else{
    Serial.print("\n> receive_iic_data length error.");
  }
}


void setup()
{
  Serial.begin(115200);

  Wire.begin(IICPIN_SDA, IICPIN_SCL);

  // IIC Scanner
  Serial.println("\n[I2C Scanner]");
  byte error, address;
  int nDevices = 0;
  Serial.println("|> Scanning...");
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    char addr_buffer[3];
    sprintf(addr_buffer, "%02x", address);
    if (error == 0) {
      Serial.print("|> I2C device found at address 0x");
      Serial.println(addr_buffer);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("|> Unknown error at address 0x");
      Serial.println(addr_buffer);
    }    
  }
  if (nDevices == 0) {
    Serial.println("|> No I2C devices found");
  }
  else {
    Serial.print("|> The number of i2c devices found:");
    Serial.println(nDevices);
  }
  delay(100);  
  Serial.println("|> Done\n");
  
  // IIC Read one byte
  Wire.beginTransmission(0x01);
  Wire.write(0X85);
  Wire.endTransmission(false);
  Wire.requestFrom((uint16_t)0x01, (uint8_t)1, (bool)true);
  byte addr_flow_sensor = Wire.read();
  Serial.print("> addr_flow_sensor: 0x");
  Serial.println(addr_flow_sensor, HEX);

  // IIC Read bytes
  byte2int32 flow_rate;
  receive_iic_data(0x01, 0x83, flow_rate.array, 4);
  Serial.print("> flow_rate: ");
  Serial.println(flow_rate.int32);

  // IIC Write
  Wire.beginTransmission(0x01);
  Wire.write(0X05);
  Wire.write(0X02);
  byte rt = Wire.endTransmission(true);
  Serial.print("> return: ");
  Serial.println(rt);

  Wire.end();
}

void loop(){
  delay(1000);
}