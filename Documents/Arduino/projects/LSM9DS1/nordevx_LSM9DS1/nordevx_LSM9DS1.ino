#include <Wire.h> //add arduino I2C library;
//list of all registers binary addresses;
byte ACT_THS              = 0B00000100;
byte ACT_DUR              = 0B00000101;
byte INT_GEN_CFG_XL       = 0B00000110;
byte INT_GEN_THS_X_XL     = 0B00000111;
byte INT_GEN_THS_Y_XL     = 0B00001000;
byte INT_GEN_THS_Z_XL     = 0B00001001;
byte INT_GEN_DUR_XL       = 0B00001010;
byte REFERENCE_G          = 0B00001011;
byte INT1_CTRL            = 0B00001100;
byte INT2_CTRL            = 0B00001101;

byte WHO_AM_I             = 0B00001111;
byte CTRL_REG1_G          = 0B00010000;
byte CTRL_REG2_G          = 0B00010001;
byte CTRL_REG3_G          = 0B00010010;
byte ORIENT_CFG_G         = 0B00010011;
byte INT_GEN_SRC_G        = 0B00010100;
byte OUT_TEMP_L           = 0B00010101;
byte OUT_TEMP_H           = 0B00010110;
byte STATUS_REG           = 0B00010111;
byte OUT_X_L_G            = 0B00011000;
byte OUT_X_H_G            = 0B00011001;
byte OUT_Y_L_G            = 0B00011010;
byte OUT_Y_H_G            = 0B00011011;
byte OUT_Z_L_G            = 0B00011100;
byte OUT_Z_H_G            = 0B00011101;
byte CTRL_REG4            = 0B00011110;
byte CTRL_REG5_XL         = 0B00011111;
byte CTRL_REG6_XL         = 0B00100000;
byte CTRL_REG7_XL         = 0B00100001;
byte CTRL_REG8            = 0B00100010;
byte CTRL_REG9            = 0B00100011;
byte CTRL_REG10           = 0B00100100;

byte INT_GEN_SRC_XL       = 0B00100110;
byte STATUS_REG0           = 0B00100111;
byte OUT_X_L_XL           = 0B00101000;
byte OUT_X_H_XL           = 0B00101001;
byte OUT_Y_L_XL           = 0B00101010;
byte OUT_Y_H_XL           = 0B00101011;
byte OUT_Z_L_XL           = 0B00101100;
byte OUT_Z_H_XL           = 0B00101101;
byte FIFO_CTRL            = 0B00101110;
byte FIFO_SRC             = 0B00101111;
byte INT_GEN_CFG_G        = 0B00110000;
byte INT_GEN_THS_XH_G     = 0B00110001;
byte INT_GEN_THS_XL_G     = 0B00110010;
byte INT_GEN_THS_YH_G     = 0B00110011;
byte INT_GEN_THS_YL_G     = 0B00110100;
byte INT_GEN_THS_ZH_G     = 0B00110101;
byte INT_GEN_THS_ZL_G     = 0B00110110;
byte INT_GEN_DUR_G        = 0B00110111;


byte OFFSET_X_REG_L_M     = 0B00000101;
byte OFFSET_X_REG_H_M     = 0B00000110;
byte OFFSET_Y_REG_L_M     = 0B00000111;
byte OFFSET_Y_REG_H_M     = 0B00001000;
byte OFFSET_Z_REG_L_M     = 0B00001001;
byte OFFSET_Z_REG_H_M     = 0B00001010;

byte WHO_AM_I_M           = 0B00001111;

byte CTRL_REG1_M          = 0B00100000;
byte CTRL_REG2_M          = 0B00100001;
byte CTRL_REG3_M          = 0B00100010;
byte CTRL_REG4_M          = 0B00100011;
byte CTRL_REG5_M          = 0B00100100;

byte STATUS_REG_M         = 0B00100111;
byte OUT_X_L_M            = 0B00101000;
byte OUT_X_H_M            = 0B00101001;
byte OUT_Y_L_M            = 0B00101010;
byte OUT_Y_H_M            = 0B00101011;
byte OUT_Z_L_M            = 0B00101100;
byte OUT_Z_H_M            = 0B00101101;

byte INT_CFG_M            = 0B00110000;
byte INT_SRC_M            = 0B00110001;
byte INT_THS_L_M          = 0B00110010;
byte INT_THS_H_M          = 0B00110011;

byte Read    = 0B00000001;
byte Write   = 0B00000000;
byte Address_AG = 0B11010110;  //address of accelerometer/gyro with SAO connected to Vdd
byte Address_M  = 0B00111100;  //address of gyro with SAO connected to Vdd

/*
Wire.h sets these for us in arduino...that's analog pin 4 and 5
const int SDA = 4; 
const int SCL = 5; 
*/

void setup() {
  Serial.begin(57600);
  //start the Wire library;
  Wire.begin();
  
WriteRegister_AG(CTRL_REG4,0B00111000);  //enable gyro axis
WriteRegister_AG(CTRL_REG5_XL,0B00111000); //enable accelerometer
WriteRegister_AG(CTRL_REG6_XL,0B10010000); // CTRL_REG6_XL (0x20)  ODR:238Hz full-scale:+/-4g
WriteRegister_AG(CTRL_REG1_G,0B01000000); //gyro/accel odr and bw
WriteRegister_M(CTRL_REG3_M,0B00000000); //enable mag continuous

delay(100);
}

void loop() {

byte WHOAMI = ReadRegister_AG(WHO_AM_I);
Serial.print("Who am I: \t");
Serial.println(WHOAMI, BIN);
delay(50);


//gyro section
byte X_L = ReadRegister_AG(OUT_X_L_G); delay(5);
byte X_H = ReadRegister_AG(OUT_X_H_G); delay(5);
byte Y_L = ReadRegister_AG(OUT_Y_L_G); delay(5);
byte Y_H = ReadRegister_AG(OUT_Y_H_G); delay(5);
byte Z_L = ReadRegister_AG(OUT_Z_L_G); delay(5);
byte Z_H = ReadRegister_AG(OUT_Z_H_G); delay(5);

int X_AXIs = X_H <<8 | X_L;
int Y_AXIs = Y_H <<8 | Y_L;
int Z_AXIs = Z_H <<8 | Z_L;

Serial.print("gyro X Y Z -Axis: (raw) \t");
Serial.print(X_AXIs, DEC); //raw x axis data
Serial.print("\t");
Serial.print(Y_AXIs, DEC);  //raw y axis data
Serial.print("\t");
Serial.println(Z_AXIs, DEC);  //raw z axis data

Serial.print("X Y Z -Axis: (dps) \t");  //.00875 is from the datasheet and my settings when i writeregister
Serial.print(0.00875*(X_AXIs+8147), DEC);
Serial.print("\t");            
Serial.print(0.00875*(Y_AXIs+4078), DEC);
Serial.print("\t");                
Serial.println(0.00875*(Z_AXIs-3397), DEC);
                                            
//the number 110 above comes from me averaging the first 100 samples of raw gyro                                            
//data sitting still in this axis and applying the equation .00875((rawdata axis data)-(average data))                                            
//everyones gyro will be different so nobodys will be the same and YOU have to manually                                            
//provide it or write in the code which would be best.(I know I'll get on it lol..priorities)                                            
//All axis will also be a different number...I also put a datasheet in the resources about this.                                            
//Output will be in dps(degrees per second)                                              
                                            
//accelerometer/magnetometer section
byte X_L_M = ReadRegister_M(OUT_X_L_M); delay(5);
byte X_H_M = ReadRegister_M(OUT_X_H_M); delay(5);
byte Y_L_M = ReadRegister_M(OUT_Y_L_M); delay(5);
byte Y_H_M = ReadRegister_M(OUT_Y_H_M); delay(5);
byte Z_L_M = ReadRegister_M(OUT_Z_L_M); delay(5);
byte Z_H_M = ReadRegister_M(OUT_Z_H_M); delay(5);

byte X_L_A = ReadRegister_AG(OUT_X_L_XL); delay(5);
byte X_H_A = ReadRegister_AG(OUT_X_H_XL); delay(5);
byte Y_L_A = ReadRegister_AG(OUT_Y_L_XL); delay(5);
byte Y_H_A = ReadRegister_AG(OUT_Y_H_XL); delay(5);
byte Z_L_A = ReadRegister_AG(OUT_Z_L_XL); delay(5);
byte Z_H_A = ReadRegister_AG(OUT_Z_H_XL); delay(5);

int X_AXIS_M = X_H_M <<8 | X_L_M;
int Y_AXIS_M = Y_H_M <<8 | Y_L_M;
int Z_AXIS_M = Z_H_M <<8 | Z_L_M;

int X_AXIS_A = X_H_A <<8 | X_L_A;
int Y_AXIS_A = Y_H_A <<8 | Y_L_A;
int Z_AXIS_A = Z_H_A <<8 | Z_L_A;

//temperature section
byte Temp_L = ReadRegister_AG(OUT_TEMP_L); delay(5);
byte Temp_H = ReadRegister_AG(OUT_TEMP_H); delay(5);

int Temp = Temp_H <<8 | Temp_L;

Serial.print("Temp_L/H: \t");
Serial.print(Temp_L, HEX);
Serial.print("\t");
Serial.print(Temp_H, HEX);

Serial.print("\t Temperature: (C) \t");  
Serial.println((Temp/16.0)+25, 4);    //16 came from datasheet and adding 25 came from
  //it saying when output is 0 it's 25C...awfully cryptic to find the temperature or I'm doing something wrong...

Serial.print("X Y Z -Axis_M: (raw) \t");
Serial.print(X_AXIS_M, DEC); 
Serial.print("\t");
Serial.print(Y_AXIS_M, DEC);
Serial.print("\t");
Serial.println(Z_AXIS_M, DEC);

Serial.print("X Y Z -Axis_M: (gauss) \t");
Serial.print(X_AXIS_M*0.00014, DEC); // .00014 comes from the datasheet and my settings for the magnetometer.
Serial.print("\t");
Serial.print(Y_AXIS_M*0.00014, DEC);
Serial.print("\t");
Serial.println(Z_AXIS_M*0.00014, DEC);


Serial.print("X Y Z -Axis_A: (G) \t");
Serial.print(X_AXIS_A*0.000122, DEC); // +/-2g  .000061 comes from the datasheet and my settings for the accelerometer.
Serial.print("\t");
Serial.print(Y_AXIS_A*0.000122, DEC); // +/-4g  .000122 comes from the datasheet and my settings for the accelerometer.
Serial.print("\t");
Serial.println(Z_AXIS_A*0.000122, DEC);


delay(500);
}

byte ReadRegister_AG(int Register){
byte result = 0;
Wire.beginTransmission((Address_AG | Write) >>1 ); //slave ID start talking
//ask for info in register
Wire.write(Register);
//complete the send
Wire.endTransmission(0);
//Request 1 byte

Wire.requestFrom((Address_AG | Read) >>1 , 1);
//wait for info
while( Wire.available() == 0);
result = Wire.read();  
//get info
Wire.endTransmission();
return(result);  
}

void WriteRegister_AG(byte Register, byte Value){
  Wire.beginTransmission((Address_AG | Write) >>1 );
  Wire.write(Register);
  Wire.write(Value);
  Wire.endTransmission();
}


byte ReadRegister_M(int Register){
byte result = 0;
Wire.beginTransmission((Address_M | Write) >>1 ); //slave ID start talking
//ask for info in register
Wire.write(Register);
//complete the send
Wire.endTransmission(0);
//Request 1 byte

Wire.requestFrom((Address_M | Read) >>1 , 1);
//wait for info
while( Wire.available() == 0);
result = Wire.read();  
//get info
Wire.endTransmission();
return(result);  
}

void WriteRegister_M(byte Register, byte Value){
  Wire.beginTransmission((Address_M | Write) >>1 );
  Wire.write(Register);
  Wire.write(Value);
  Wire.endTransmission();
}
