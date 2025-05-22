/*
 * ADPD188BI Integrated Optical Module for smoke detection from Analog Devices
 * Data Sheet --> https://www.analog.com/media/en/technical-documentation/data-sheets/adpd188bi.pdf
 * Using I2C Configuration on custom-made PCB
 * 
 * Author: Arnau Donate Duch
 * 
 * Inspired by work from Edward Mallon and Patricia Beddows (The Cave Pearl Project)
 * https://thecavepearlproject.org/2017/11/03/configuring-i2c-sensors-with-arduino/
*/

#include <Wire.h>

#define ADPD188BI         0x64
#define MODE              0x10
#define SAMPLE_CLK        0x4B

#define PROGRAM_MODE_MSB          0b00000000
#define PROGRAM_MODE_LSB          0b00000001
#define NORMAL_MODE_MSB           0b00000000
#define NORMAL_MODE_LSB           0b00000010 
#define SAMPLE_CLK_ENABLED_MSB    0b01001100
#define SAMPLE_CLK_ENABLED_LSB    0b10010010

void setup() {
  Serial.begin(115200);
  Wire.begin();
  ADPD188BI_StartSampling();
}

void loop() {
  i2c_readRegisterByte(ADPD188BI, 0x64, 2);
}

void ADPD188BI_StartSampling () {
  i2c_writeRegisterByte(ADPD188BI, SAMPLE_CLK, SAMPLE_CLK_ENABLED_MSB, SAMPLE_CLK_ENABLED_LSB);
  i2c_writeRegisterByte(ADPD188BI, MODE, PROGRAM_MODE_MSB, PROGRAM_MODE_LSB);

  i2c_writeRegisterByte(ADPD188BI, 0x11, 0b00110000, 0b01101000);
  i2c_writeRegisterByte(ADPD188BI, 0x12, 0b00000010, 0b00000000);
  i2c_writeRegisterByte(ADPD188BI, 0x14, 0b00000001, 0b00011101);
  i2c_writeRegisterByte(ADPD188BI, 0x15, 0b00000000, 0b00000000);
  i2c_writeRegisterByte(ADPD188BI, 0x17, 0b00000000, 0b00001001);
  i2c_writeRegisterByte(ADPD188BI, 0x18, 0b00000000, 0b00000000);
  i2c_writeRegisterByte(ADPD188BI, 0x19, 0b00111111, 0b11111111);
  i2c_writeRegisterByte(ADPD188BI, 0x1A, 0b00111111, 0b11111111);
  i2c_writeRegisterByte(ADPD188BI, 0x1B, 0b00111111, 0b11111111);
  i2c_writeRegisterByte(ADPD188BI, 0x1D, 0b00000000, 0b00001001);
  i2c_writeRegisterByte(ADPD188BI, 0x1E, 0b00000000, 0b00000000);
  i2c_writeRegisterByte(ADPD188BI, 0x1F, 0b00111111, 0b11111111);
  i2c_writeRegisterByte(ADPD188BI, 0x20, 0b00111111, 0b11111111);
  i2c_writeRegisterByte(ADPD188BI, 0x21, 0b00111111, 0b11111111);
  i2c_writeRegisterByte(ADPD188BI, 0x22, 0b00110101, 0b00111001);
  i2c_writeRegisterByte(ADPD188BI, 0x23, 0b00110101, 0b00110110);
  i2c_writeRegisterByte(ADPD188BI, 0x24, 0b00010101, 0b00110000);
  i2c_writeRegisterByte(ADPD188BI, 0x25, 0b01100011, 0b00001100);
  i2c_writeRegisterByte(ADPD188BI, 0x30, 0b00000011, 0b00100000);
  i2c_writeRegisterByte(ADPD188BI, 0x31, 0b00000100, 0b00001110);
  i2c_writeRegisterByte(ADPD188BI, 0x35, 0b00000011, 0b00100000);
  i2c_writeRegisterByte(ADPD188BI, 0x36, 0b00000100, 0b00001110);
  i2c_writeRegisterByte(ADPD188BI, 0x39, 0b00100010, 0b11110000);
  i2c_writeRegisterByte(ADPD188BI, 0x3B, 0b00100010, 0b11110000);
  i2c_writeRegisterByte(ADPD188BI, 0x3C, 0b00110001, 0b11000110);
  i2c_writeRegisterByte(ADPD188BI, 0x42, 0b00011100, 0b00110100);
  i2c_writeRegisterByte(ADPD188BI, 0x43, 0b10101101, 0b10100101);
  i2c_writeRegisterByte(ADPD188BI, 0x44, 0b00011100, 0b00110100);
  i2c_writeRegisterByte(ADPD188BI, 0x45, 0b10101101, 0b10100101);
  i2c_writeRegisterByte(ADPD188BI, 0x58, 0b00000101, 0b01000100);
  i2c_writeRegisterByte(ADPD188BI, 0x11, 0b00110000, 0b10101001);

  i2c_writeRegisterByte(ADPD188BI, MODE, NORMAL_MODE_MSB, NORMAL_MODE_LSB);
}

int i2c_readRegisterByte(uint8_t deviceAddress, uint8_t registerAddress, int bytes) {
  byte MSB = 0, LSB = 0;
  int fullByte = -1;

  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, bytes);

  if (bytes == 2) {
    MSB = Wire.read();
    LSB = Wire.read();
    fullByte = (((int)MSB) << 8) | LSB;
    Serial.println(fullByte, DEC);
    return fullByte;
  } else if (bytes == 1) {
    MSB = Wire.read();
    Serial.print("0x");
    Serial.print(registerAddress, HEX);
    Serial.print(" = 0x");
    Serial.println(MSB, HEX);
    return MSB;
  } else {
    Serial.println("Number of bytes retrieved not supported.");
    return -1;
  }
}

byte i2c_writeRegisterByte(uint8_t deviceAddress, uint8_t registerAddress, uint8_t MSB_RegisterByte, uint8_t LSB_RegisterByte) {
  byte result;
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);
  Wire.write(MSB_RegisterByte);
  Wire.write(LSB_RegisterByte);
  result = Wire.endTransmission();
  if (result > 0) {
    Serial.print(F("FAIL in I2C register write! Error code: "));
    Serial.println(result);
  }
  return result;
}

byte i2c_setRegisterBit(uint8_t deviceAddress, uint8_t registerAddress, uint8_t bitPosition, bool state) {
  byte registerByte = i2c_readRegisterByte(deviceAddress, registerAddress, 1);
  if (state) {
    registerByte |= (1 << bitPosition);
  } else {
    registerByte &= ~(1 << bitPosition);
  }
  return i2c_writeRegisterByte(deviceAddress, registerAddress, registerByte, 0x00);
}

bool i2c_getRegisterBit(uint8_t deviceAddress, uint8_t registerAddress, uint8_t bitPosition) {
  byte registerByte = i2c_readRegisterByte(deviceAddress, registerAddress, 1);
  return ((registerByte >> bitPosition) & 0x01);
}


