/*
    Measurement of acceleration values using motion sensor KIONIX_KXCJ9-1008 

TTTTTTTTTTT

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

int outX, outY, outZ;
int xVal, yVal, zVal;
long t0 = 0;
long t1 = 0;

void setup()
{
    Wire.begin();
    Serial.begin(57600);
    Serial.println("ready 1 !");
    delay(5); //5 ms boot procedure
    
    Wire.beginTransmission(ADDRESS_KXCJ9);
    Wire.write(DATA_CTRL); 
    Wire.write(0x07);
    Wire.endTransmission();  
	
    Wire.beginTransmission(ADDRESS_KXCJ9);
    Wire.write(CTRL_REG1); 
    Wire.write(0xC0);
    Wire.endTransmission();	

    Wire.beginTransmission(ADDRESS_KXCJ9);
    Wire.write(DATA_CTRL); 
    Wire.write(0x07);
    Wire.endTransmission();
    
    Wire.beginTransmission(ADDRESS_KXCJ9);
    Wire.write(CTRL_REG1); 
    Wire.write(0xC0);
    Wire.endTransmission();      
	
    delay(5);
    
    t0 = micros();
}

void loop()
{
    t1 = micros();
    
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
    xVal = outX >> 4;
    yVal = outY >> 4;
    zVal = outZ >> 4;
	
    //Calibration
    xVal += 5;
    yVal += 8;
    zVal += 26;

    Serial.print("outX:\t"); Serial.print(xVal); Serial.print("\t");
    Serial.print("outY:\t"); Serial.print(yVal); Serial.print("\t");
    Serial.print("outZ:\t"); Serial.print(zVal); Serial.print("\t");
	
    if (abs(xVal)<9 & abs(yVal)<9) {if (zVal>0) Serial.print("z+"); else Serial.print("z-");}
    if (abs(yVal)<9 & abs(zVal)<9) {if (xVal>0) Serial.print("x+"); else Serial.print("x-");}
    if (abs(zVal)<9 & abs(xVal)<9) {if (yVal>0) Serial.print("y+"); else Serial.print("y-");} 
    Serial.print("\t");

    Serial.print(t1-t0);
    t0 = t1;
    
    Serial.print("\n");
    // delay(200);
}
