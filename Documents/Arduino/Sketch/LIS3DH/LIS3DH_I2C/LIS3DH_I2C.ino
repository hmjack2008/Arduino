/*
    Measurement of acceleration values using motion sensor LIS3DH 





==============================================
LIS3DH temperature sensor
https://my.st.com/public/STe2ecommunities/mcu/Lists/STM32F%20MEMS%20%20iNEMO/Flat.aspx?RootFolder=https%3a%2f%2fmy%2est%2ecom%2fpublic%2fSTe2ecommunities%2fmcu%2fLists%2fSTM32F%20MEMS%20%20iNEMO%2fLIS3DH%20temperature%20sensor&FolderCTID=0x01200200770978C69A1141439FE559EB459D7580003E26E7DD54228C428E8F9FB5EE9C5185&currentviews=2641


Hello, I have a similar question that was asked before, but never answered - how to get Temperature data from LIS3HD accelerometer's temperature sensor.
I checked datasheet and application note, but there is nothing there. I also checked some sample code, but it does not seem to work.

Documents suggest that the temperature data is available in ADC3_H and ADC3_L registers. But on what location in this two registers (on which bits)? Or is maybe only ADC3_H for temperature data?
Documents also suggest that prior using temperature sensor, you must enable BIT 6 and 7 in TempCfgReg (enable AUX and enable temperature sensor). Moreover BDU must be enabled.
Is that all?

I got the enswer directlly from the STM. 
I must say that they are very helpfull.

Right: you must enable BIT 6 and 7 in TempCfgReg (enable AUX and enable temperature sensor).  

To correctly work with temperature sensor you have to enable Block Data Update, BDU, feature. CTRL_REG4(0x23) , BDU (bit#7)=1.
More, you have to read both the adc output 3 registers (because of BDU enabled): OUT_ADC_3_L(0x0C) and OUT_ADC_3_H(0x0D).
Data representation: 2's complement.
Useful bits: 8, left aligned, hence useful data in OUT_ADC_3_H.

Temperature sensor output change vs temperature: 1digit/degrCelsius

Value represents difference respect to a reference not specified value.
So temprerature sensor can be used to measure temperature variations, or, temperarture sensor isn't suitable to return absolute temperatures measures. It can be used only to measure temperature variations. So the single output doesn't return the current absolute temperature, while if you run two sequential measures and differentiate them you can get temperature variation.

This means that two devices in the same temp conditions can return different outputs.

Example1:
if you read @OUT_ADC_3_L(0x0C) and OUT_ADC_3_H(0x0D):
0xF931 means: 0xF9 = 0b11111001 = -7 (remember: two's complement representation:11111001=>00000110+1=00000111=7)
-7(digit) / 1(digit/degrCelsius) = -7 (degrCelsius)
 

Example 2:
0x0600 means : 0x06 = 6 decimal
6(digit) / 1(digit/degrCelsius) = 6 (degrCelsius)
If you run another read you can have temperature difference.
If you read 0xFA13:  0xFA = -5 degrCelsius

Final - Initial Temps: (-5) - 6 = -11 degrCelsius 
temperature decreased by 11 degrCelsius
==============================================


*/

#include <Wire.h>

#define ADDRESS_LIS3DH 0x19
#define CTRL_REG1 0x20
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define STATUS_REG 0x27
#define OUT_X_L 0x28

byte buffer[6];
byte statusReg;

boolean ready = false;
int outX, outY, outZ;
int xVal, yVal, zVal;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    delay(5); //5 ms boot procedure

    // reboot memory content, to make a clean start
    Wire.beginTransmission(ADDRESS_LIS3DH);
    Wire.write(CTRL_REG5); 
    Wire.write(0x80);
    Wire.endTransmission();

    delay(5);

    //set ODR = 1 Hz, normal mode, x/y/z axis enabled
    Wire.beginTransmission(ADDRESS_LIS3DH);
    Wire.write(CTRL_REG1); 
    Wire.write(0x17);
    Wire.endTransmission();

    //set BDU= 1, scale = +/-2g, high resolution enabled
    Wire.beginTransmission(ADDRESS_LIS3DH);
    Wire.write(CTRL_REG4); 
    Wire.write(0x80);
    Wire.endTransmission();
}

void loop()
{
    // read STATUS_REG
    while(ready == false)
    {
        Wire.beginTransmission(ADDRESS_LIS3DH);
        Wire.write(STATUS_REG); 
        Wire.endTransmission();
        Wire.requestFrom(ADDRESS_LIS3DH, 1);
        if (Wire.available() >= 1)
        {
            statusReg = Wire.read();
        }
        if (bitRead(statusReg, 3) == 1) //new data available
        {
            ready = true;
        }
        delay(10);
    }
    
    if (bitRead(statusReg, 7) == 1)
    {
        Serial.println("Some data have been overwritten.");
    }

    //read the result
    Wire.beginTransmission(ADDRESS_LIS3DH);
    Wire.write(OUT_X_L | 0x80); //read multiple bytes
    Wire.endTransmission();
    Wire.requestFrom(ADDRESS_LIS3DH, 6);
    if (Wire.available() >= 6)
    {
        for (int i = 0; i < 6; i++)
        {
            buffer[i] = Wire.read();
        }
    }

    //calculation
    outX = (buffer[1] << 8) | buffer[0]; 
    outY = (buffer[3] << 8) | buffer[2]; 
    outZ = (buffer[5] << 8) | buffer[4]; 
    xVal = outX / 16;
    yVal = outY / 16;
    zVal = outZ / 16;

    Serial.print("outX: "); Serial.print(xVal); Serial.print("  ");
    Serial.print("outY: "); Serial.print(yVal); Serial.print("  ");
    Serial.print("outZ: "); Serial.println(zVal);

    ready = false;
}