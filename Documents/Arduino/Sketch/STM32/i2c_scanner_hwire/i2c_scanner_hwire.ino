// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, August 1, 2015
//    Modified to support HardWire for STM32duino
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

/**
 * @brief Initialize an I2C device as bus master
 * @param dev Device to enable
 * @param flags Bitwise or of the following I2C options:
 *              I2C_FAST_MODE: 400 khz operation,
 *              I2C_DUTY_16_9: 16/9 Tlow/Thigh duty cycle (only applicable for
 *                             fast mode),
 *              I2C_BUS_RESET: Reset the bus and clock out any hung slaves on
 *                             initialization,
 *              I2C_10BIT_ADDRESSING: Enable 10-bit addressing,
 *              I2C_REMAP: (deprecated, STM32F1 only) Remap I2C1 to SCL/PB8
 *                         SDA/PB9.
 */
#include <HardWire.h>

/* 1:I2C1 2:I2C2
I2C1 : PB6_SCL PB7_SDA
I2C1 Remap : PB8_SCL PB9_SDA
I2C2 : PB10_SCL PB11_SDA
*/

HardWire HWire(1, (I2C_FAST_MODE|I2C_REMAP)); // 1:I2C1 2:I2C2

void setup() {
  Serial.begin(9600);
  HWire.begin();
  delay(5000);
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.

    HWire.beginTransmission(address);
    error = HWire.endTransmission();
    
    if (error == 0) {
      Serial.print("  I2C device found at address 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("  Unknown error at address 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("done");

  delay(5000);           // wait 5 seconds for next scan
}
