# ADPD188BI-Arduino

This is a repository with the code to use the **smoke sensor ADPD188BI** from Analog Devices within the **Arduino IDE** and an **ESP32** board using **I2C**.

It contains the initialization of the sensor so you can program it to read specific values from the appropriate registers. You can learn more about the registers in the [datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/adpd188bi.pdf).

---

## ✅ Recommended Start-Up Sequence

1. At power-up, the device is in standby mode (`Register 0x10 = 0x00`)
2. Set the `CLK32K_EN` bit (`Register 0x4B`, Bit 7) to start the 32 kHz sample clock. Without it, the device state machine won't transition.
3. Write `0x01` to `Register 0x10` to enter program mode.
4. Configure the desired registers while in program mode.
5. Write `0x02` to `Register 0x10` to start normal sampling.

---

## 📟 Register Configuration in Code

| Register | Value  | Description |
|----------|--------|-------------|
| 0x11     | 0x30A9 | 32-bit sum to FIFO for Time Slot A & B |
| 0x12     | 0x0200 | 16 Hz sampling rate |
| 0x14     | 0x011D | Blue Slot A, IR Slot B, combine PDs |
| 0x15     | 0x0000 | No decimation |
| 0x17     | 0x0009 | Time Slot A chop mode |
| 0x18     | 0x0000 | No ADC offset |
| 0x19-0x1B| 0x3FFF | Unused channels |
| 0x1D     | 0x0009 | Time Slot B chop mode |
| 0x1E     | 0x0000 | No ADC offset |
| 0x1F-0x21| 0x3FFF | Unused channels |
| 0x22     | 0x3539 | LED3 IR |
| 0x23     | 0x3536 | LED1 blue |
| 0x24     | 0x1530 | LED2 unused |
| 0x25     | 0x630C | Default LED drive trim |
| 0x30     | 0x0320 | 3 μs LED pulse |
| 0x31     | 0x040E | Four pulses, 15 μs LED offset |
| 0x35     | 0x0320 | 3 μs LED pulse |
| 0x36     | 0x040E | Four pulses, 15 μs LED offset |
| 0x39     | 0x22F0 | Integrator timing |
| 0x3B     | 0x22F0 | Integrator timing |
| 0x3C     | 0x31C6 | Power down Channel 2, 3, and 4 |
| 0x42     | 0x1C34 | 200k TIA gain |
| 0x43     | 0xADA5 | Signal path config |
| 0x44     | 0x1C34 | 200k TIA gain |
| 0x45     | 0xADA5 | Signal path config |
| 0x58     | 0x0544 | Chop mode math |
| 0x54     | 0x0AA0 | PD reverse bias (~250 mV) |

---

## 📚 Reference

- [ADPD188BI Datasheet (Analog Devices)](https://www.analog.com/media/en/technical-documentation/data-sheets/adpd188bi.pdf)
- Sensor communication methods inspired by [The Cave Pearl Project](https://thecavepearlproject.org/2017/11/03/configuring-i2c-sensors-with-arduino/)

Schematics for I2C configuration are available in the repo or datasheet.

---

## ⚠️ Notes

- ✅ Compatible with **Arduino IDE v2.3.6+**
- 🛠️ Fixed compilation errors:
  - `i2c_readRegisterByte` now returns a valid value.
  - `i2c_setRegisterBit` call updated with the correct number of parameters.
  - Ensure `Wire.begin()` is called before using any I2C function.
