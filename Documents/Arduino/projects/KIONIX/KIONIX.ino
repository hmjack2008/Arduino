/*
    Measurement of acceleration values using motion sensor KIONIX_KXCJ9-1008 



==============================================

KIONIX_KXCJ9-1008 

http://zh-cn.kionix.com/downloads

http://firewall.kionix.com/application-notes
AN028 Getting Started with the KXCJ9.pdf


==============================================


*/

#include <Wire.h>

#define ADDRESS_KXCJ9 0xF
#define CTRL_REG1 0x1B // 0100 0000 ->                      ->1100 0000 (12-14bits)
#define CTRL_REG2 0x1D //             -> 1000 0110 (50Hz) ->
#define DATA_CTRL 0x21 //             -> 0000 0010 (default, Output Data = 50Hz, LPF Roll-off = 25Hz)
#define STATUS_REG 0x18
#define INT_CTRL_REG1 0x1E // 0001 1000
#define INT_CTRL_REG2 0x1F // 0011 1111

#define OUT_X_L 0x6
#define OUT_X_H 0x7
#define OUT_Y_L 0x8
#define OUT_Y_H 0x9
#define OUT_Z_L 0xA
#define OUT_Z_H 0xB

byte buffer[6];
byte statusReg;

boolean ready = false;
int outX, outY, outZ;
int xVal, yVal, zVal;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    Serial.println("ready 1 !");
    delay(5); //5 ms boot procedure

//	//set 12-14bits , +/-2g
//    Wire.beginTransmission(ADDRESS_KXCJ9);
//    Wire.write(CTRL_REG1); 
//    Wire.write(0x42);
//    Wire.endTransmission();
//
//    //reboot memory content, 50Hz
//    Wire.beginTransmission(ADDRESS_KXCJ9);
//    Wire.write(CTRL_REG2); 
//    Wire.write(0x86);
//    Wire.endTransmission();
//	
//    // interrupt will transmit one pulse with a period
//    Wire.beginTransmission(ADDRESS_KXCJ9);
//    Wire.write(INT_CTRL_REG1); 
//    Wire.write(0x18);
//    Wire.endTransmission();
//	
//    // Output Data = 50Hz, LPF Roll-off = 25Hz
//    Wire.beginTransmission(ADDRESS_KXCJ9);
//    Wire.write(DATA_CTRL); 
//    Wire.write(0x02);
//    Wire.endTransmission();
//    delay(50);	
//	
//	//reboot memory content, 50Hz
//	  Wire.beginTransmission(ADDRESS_KXCJ9);
//    Wire.write(CTRL_REG2); 
//    Wire.write(0x86);
//    Wire.endTransmission();
	
    Wire.beginTransmission(ADDRESS_KXCJ9);
    Wire.write(CTRL_REG1); 
    Wire.write(0xC0);
    Wire.endTransmission();	
	
    delay(5);
}

void loop()
{
    
//    // read STATUS_REG
//    while(ready == false)
//    {
//	      Wire.beginTransmission(ADDRESS_KXCJ9);
//        Wire.write(STATUS_REG); 
//        Wire.endTransmission();
//        Wire.requestFrom(ADDRESS_KXCJ9, 1);
//        if (Wire.available() >= 1)
//        {
//            statusReg = Wire.read();
//        }
//        if (bitRead(statusReg, 3) == 1) //new data available
//        {
//            ready = true;
//        }
//        delay(10);
//    }
//    
//    if (bitRead(statusReg, 7) == 1)
//    {
//        Serial.println("Some data have been overwritten.");
//    }

    //read the result
    Wire.beginTransmission(ADDRESS_KXCJ9);
    Wire.write(OUT_X_L | 0x80); //read multiple bytes
    Wire.endTransmission();
    Wire.requestFrom(ADDRESS_KXCJ9, 6);
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

    Serial.print("outX:\t"); Serial.print(xVal); Serial.print("\t");
    Serial.print("outY:\t"); Serial.print(yVal); Serial.print("\t");
    Serial.print("outZ:\t"); Serial.println(zVal);

    ready = false;
    delay(200);
}
