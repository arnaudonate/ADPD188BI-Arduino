# ADPD188BI-Arduino
This is a repositpry with the code to use the smoke sensor ADPD188BI from Analog Devices within the arduino IDE and an ESP32 board using I2C.
It contains the initialization of the sensor so you can program it to read specific values from the appropiate registers.
You can find about the registers in the datasheet.

RECOMMENDED START-UP SEQUENCE FOLLOWED
1. At power-up, the device is in standby mode (Register 0x10 = 0x0)
2. Set the CLK32K_EN bit (Register 0x4B, Bit 7) to start the sample clock (32 kHz clock). If this clock is off, the state machine is not able to transition as defined by Register 0x10.
3. Write 0x1 to Register 0x10 to force the device into program mode.
4. Write additional control registers in any order while the device is in program mode to configure the devices as required.
5. Write 0x2 to Register 0x10 to start normal sampling operation

The settings programmed in the code are the following:
0x11 0x30A9 Writes a 32-bit sum to the FIFO for Time Slot A and Time Slot B  
0x12 0x0200 16 Hz sampling rate  
0x14 0x011D Blue Slot A, IR Slot B, combine PDs  
0x15 0x0000 No decimation  
0x17 0x0009 Time Slot A chop mode, inverted, noninverted, noninverted, inverted (see the Improving SNR Using Integrator Chopping section for more information)  
0x18 0x0000 No ADC offset  
0x19 0x3FFF Unused channel  
0x1A 0x3FFF Unused channel  
0x1B 0x3FFF Unused channel  
0x1D 0x0009 Time Slot B chop mode (inverted, noninverted, noninverted, inverted)  
0x1E 0x0000 No ADC offset  
0x1F 0x3FFF Unused channel  
0x20 0x3FFF Unused channel  
0x21 0x3FFF Unused channel  
0x22 0x3539 LED3 IR  
0x23 0x3536 LED1 blue  
0x24 0x1530 LED2 unused  
0x25 0x630C Default LED drive trim  
0x30 0x0320 3 μs LED pulse  
0x31 0x040E Four pulses, 15 μs LED offset  
0x35 0x0320 3 μs LED pulse  
0x36 0x040E Four pulses, 15 μs LED offset  
0x39 0x22F0 Integrator timing  
0x3B 0x22F0 Integrator timing  
0x3C 0x31C6 Power down Channel 2, Channel 3, and Channel 4  
0x42 0x1C34 200k TIA gain  
0x43 0xADA5 Signal path configuration  
0x44 0x1C34 200k TIA gain  
0x45 0xADA5 Signal path configuration  
0x58 0x0544 Math for chop mode inverted, noninverted, noninverted, inverted LED  
0x54 0x0AA0 PD reverse bias, approximately 250 mV  
 
ADPD188BI Integrated Optical Module for smoke detection from Analog Devices
You can find the data Sheet in the repository or here--> https://www.analog.com/media/en/technical-documentation/data-sheets/adpd188bi.pdf

The reading and writing method is based on previous work from Edward Mallon and Patricia Beddows (The Cave Pearl Project) on other sensors.
https://thecavepearlproject.org/2017/11/03/configuring-i2c-sensors-with-arduino/

The schematics on the sensor configuration for I2C can be found also in the repository or in the datasheet attached.
