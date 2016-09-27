
/*
#define SDA 25 //25:PB9  19:PB3
#define SCL 24 //24:PB8  20:PB4
*/
// PB0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
// D16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//#include <Wire.h>

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

1:I2C1 2:I2C2
I2C1       : PB6_SCL PB7_SDA
I2C1 REMAP : PB8_SCL PB9_SDA
I2C2       : PB10_SCL PB11_SDA
*/
//#include <HardWire.h>
//HardWire HWire(1, (I2C_FAST_MODE|I2C_REMAP)); // 1:I2C1 2:I2C2 , flag

#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x20 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x20,16,2);

void setup()
{
  // initialize the lcd 
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.clear();
}


void loop()
{
  //lcd.clear();
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("[Hello, world !]");
  
  lcd.setCursor(0,1);
  lcd.print("STM32 Arduino   ");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("Arduino LCM IIC ");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("I2C Soft/Hard   ");
  delay(3000);
}
