#include <Wire.h>  //调用arduino自带的I2C库
// #include <LiquidCrystal.h>   //调用arduino自带的LiquidCrystal库
 
// 定义ITG3200陀螺仪常量
#define GYRO 0x68 // 设置IIC地址,AD0与GND相接,二进制数值为11101000.
#define G_SMPLRT_DIV 0x15
#define G_DLPF_FS 0x16
#define G_INT_CFG 0x17
#define G_PWR_MGM 0x3E
 
#define G_TO_READ 8 // x, y, z 每个轴输出为2个字节
 
// LiquidCrystal lcd(12, 11, 10, 9, 8, 7);//设置LCD接口
 
//  XYZ三轴偏移量修正
int g_offx = 8;     // 修正X轴误差
int g_offy = -14;   // 修正Y轴误差
int g_offz = 5;     // 修正Z轴误差
float hx, hy, hz, turetemp;
 
// 初始化陀螺仪
void initGyro()
{
  /*****************************************
  * ITG 3200
  * 电源管理设置:
  * 时钟选择为内部振荡器
  * 无复位、无睡眠模式
  * 无待机模式
  * 采样率 = 1KHz
  * 参数为+ / - 2000度/秒
  * 低通滤波 = 5Hz
  * 没有中断
  ******************************************/
  writeTo(GYRO, G_PWR_MGM, 0x00);
  writeTo(GYRO, G_SMPLRT_DIV, 0x07); // EB, 50, 80, 7F, DE, 23, 20, FF
  writeTo(GYRO, G_DLPF_FS, 0x1E); // +/- 2000 dgrs/sec, 1KHz, 1E, 19
  writeTo(GYRO, G_INT_CFG, 0x00);
}
 
 
void getGyroscopeData(int * result)
{
  /**************************************
  Gyro ITG-3200 I2C
  注册:
  temp MSB = 1B, temp LSB = 1C
  x axis MSB = 1D, x axis LSB = 1E
  y axis MSB = 1F, y axis LSB = 20
  z axis MSB = 21, z axis LSB = 22
  *************************************/
 
  int regAddress = 0x1B;
  int temp, x, y, z;
  byte buff[G_TO_READ];
 
  readFrom(GYRO, regAddress, G_TO_READ, buff); // 从ITG3200读取数据
 
  result[0] = ((buff[2] << 8) | buff[3]) + g_offx;
  result[1] = ((buff[4] << 8) | buff[5]) + g_offy;
  result[2] = ((buff[6] << 8) | buff[7]) + g_offz;
  result[3] = (buff[0] << 8) | buff[1]; // 温度
 
}
 
void setup()
{
  // lcd.begin(16, 2);  //初始化LCD
  Serial.begin(57600);
  delay(500);
  Wire.begin();  //初始化I2C
  delay(100);
  initGyro();
}
 
void loop()
{
  int gyro[4];
  getGyroscopeData(gyro);
  hx = gyro[0] / 14.375; // 输出值转换为角速度,单位是度/秒
  hy = gyro[1] / 14.375;
  hz = gyro[2] / 14.375;
  turetemp = 35+ ((double) (gyro[3] + 13200)) / 280; // 输出值转换为摄氏度
 
  // lcd.clear(); //清屏
  // lcd.print("X="); //使屏幕显示文字X=
  // lcd.print(hx,4);
  // lcd.setCursor(8, 0);
  // lcd.print("Y=");
  // lcd.print(hy,4);
  // lcd.setCursor(0, 1);
  // lcd.print("Z=");
  // lcd.print(hz,4);
  // lcd.setCursor(8, 1);
  // lcd.print("T=");
  // lcd.print(turetemp,4);
  // lcd.print((char)223);
  // lcd.print("C");
  

  Serial.print("X=\t");
  Serial.print(hx);

  Serial.print("\t Y=\t");
  Serial.print(hy);

  Serial.print("\t Z=\t");
  Serial.print(hz);

  Serial.print("\t F=\t");
  Serial.print(turetemp);

  Serial.print("\n");
  
  delay(200);  //延时，刷新频率这里进行调整
}
 
//---------------- 函数
// 将值写入累加器中的地址寄存器
void writeTo(int DEVICE, byte address, byte val) {
   Wire.beginTransmission(DEVICE); // 开始传输数据到累加器
   Wire.write(address);        //  发送寄存器地址
   Wire.write(val);        //  发送要写入的值
   Wire.endTransmission(); // 结束传输
}
 
 
// 从累加器的地址寄存器中读取buff数组数据
void readFrom(int DEVICE, byte address, int num, byte buff[]) {
  Wire.beginTransmission(DEVICE); // 开始传输数据到累加器
  Wire.write(address);        // 发送读取的地址
  Wire.endTransmission(); // 结束传输
 
  Wire.beginTransmission(DEVICE); // 开始传输数据到累加器
  Wire.requestFrom(DEVICE, num);    //  从累加器请求6个字节数据
 
  int i = 0;
  while(Wire.available())    
  { 
    buff[i] = Wire.read(); // 接收一个字节
    i++;
  }
  Wire.endTransmission(); // 结束传输
}

