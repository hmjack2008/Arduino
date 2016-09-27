/********************************************************
*
* @file      [gokit_2.ino]
* @author    [True]
* @version   V2.3
* @date      2015-07-06
*
* @brief     机智云 只为智能硬件而生
*            Gizwits Smart Cloud  for Smart Products
*            链接｜增值｜开放｜中立｜安全｜自有｜自由｜生态
*            www.gizwits.com
*
*********************************************************/
#define DEBUG 1


#include <Arduino.h>
#include "DHT.h"
#include "I2Cdev.h"
// #include "MemoryFree.h"
// #include "MsTimer2.h"
#include "ChainableLED.h"
// #include <SoftwareSerial.h>
#define mySerial Serial
#include <Wire.h>
#include "GizWits.h"
#include "ringbuffer.h"

/*************************** HAL define ***************************/
#define   Infrared_PIN      PB7  // D2
#define   DHTPIN            PB3  // D3
#define   MOTOR_PINA        PB5  // D4
#define   MOTOR_PINB        PB4  // D5 (pwm)
#define   KEY1              PB10 // D6
#define   KEY2              PA8  // D7
#define   KEY3              PA1

#define   DHTTYPE           DHT11

#define   KEY1_SHORT_PRESS  1
#define   KEY1_LONG_PRESS   2
#define   KEY2_SHORT_PRESS  4
#define   KEY2_LONG_PRESS   8
#define   NO_KEY            0
#define   KEY_LONG_TIMER    3   //( 3s )

#define   MOTOR_MAX         100
#define   MOTOR_MAX1        -100
#define   MOTOR_MIN         0
#define   MOTOR_16

uint8_t gaterSensorFlag ;
uint8_t Set_LedStatus = 0;
uint8_t NetConfigureFlag = 0;
uint32_t Last_KeyTime = 0;
uint8_t lastTem = 0, lastHum = 0;

DHT dht(DHTPIN, DHTTYPE);
// ChainableLED leds(A5, A4, 1); // clk, data, #led
ChainableLED leds(PB8, PB9, 1);

#if(DEBUG == 1)
// SoftwareSerial mySerial(PA10, PA9); // D8 RX, D9 TX
#endif

#ifdef  MOTOR_16
typedef uint16_t MOTOR_T;
#else
typedef uint8_t MOTOR_T;
#endif

typedef enum
{
  SetLED_OnOff    = 0x01,
  SetLED_Color    = 0x02,
  SetLED_R        = 0x04,
  SetLED_G        = 0x08,
  SetLED_B        = 0x10,
  SetMotor        = 0x20,

} Attr_FlagsTypeDef;

typedef enum
{
  LED_OnOff       = 0x00,
  LED_OnOn        = 0x01,
  LED_Costom      = 0x00,
  LED_Yellow      = 0x02,
  LED_Purple      = 0x04,
  LED_Pink        = 0x06,

} LED_ColorTypeDef;

typedef struct
{
  uint8_t       LED_Cmd;
  uint8_t       LED_R;
  uint8_t       LED_G;
  uint8_t       LED_B;
  MOTOR_T       Motor;
  uint8_t       Infrared;
  uint8_t       Temperature;
  uint8_t       Humidity;
  uint8_t       Alert;
  uint8_t       Fault;
} ReadTypeDef_t;

typedef struct
{
  uint8_t             Attr_Flags;
  uint8_t             LED_Cmd;
  uint8_t             LED_R;
  uint8_t             LED_G;
  uint8_t             LED_B;
  MOTOR_T             Motor;
} WirteTypeDef_t;

WirteTypeDef_t  WirteTypeDef;
ReadTypeDef_t ReadTypeDef;
void GizWits_GatherSensorData(void);
void GizWits_ControlDeviceHandle(void);
void Motor_status(MOTOR_T motor_speed);

/*******************************************************
 *    function      : DHT11_Read_Data
 *    Description   : set gokit colorrgb led
 *    return        : none
 *
 *    Add by Alex.lin    --2015-7-1
******************************************************/
void DHT11_Read_Data(unsigned char * temperature, unsigned char * humidity)
{
  *temperature = (unsigned char)dht.readTemperature();
  *humidity = (unsigned char)dht.readHumidity();
  return;
}

/*******************************************************
 *    function      : IR_Handle
 *    Description   : set gokit colorrgb led
 *    return        : none
 *
 *    Add by Alex.lin    --2015-7-1
******************************************************/
bool IR_Handle(void)
{
  if (digitalRead(Infrared_PIN))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/*******************************************************
 *    function      : LED_RGB_Control
 *    Description   : set gokit colorrgb led
 *    return        : none
 *
 *    Add by Alex.lin    --2015-7-1
******************************************************/
void LED_RGB_Control(byte red, byte green, byte blue)
{
  leds.setColorRGB(0, red, green, blue);
}

/*******************************************************
 *    function      : gokit_motor_init
 *    Description   : init gokit motor.
 *    return        : none
 *
 *    Add by Alex.lin    --2014-12-25
******************************************************/
HardwareTimer timer( 3 );
uint16 max_duty; // set by setPeriod to maximum timer count
void Motor_Init(void)
{

// MOTOR_PINA : digital D4 / PB5
// MOTOR_PINB : analog  D5 / PB4
  
  afio_cfg_debug_ports(AFIO_DEBUG_NONE);
  // Tim3Ch1:PB4 Tim3Ch2:PB5
  afio_remap(AFIO_REMAP_TIM3_PARTIAL);
  pinMode(MOTOR_PINB, PWM);
  pinMode(MOTOR_PINA, OUTPUT);
  // Initialize the Timer for the PWM channels
  timer.pause ();
  timer.setMode(1, TIMER_PWM); // channel_1 
  // setPeriod( usecs) sets internally the prescaler and max duty count for respective timer
  // and returns the max duty count for given usecs period
  max_duty =  timer.setPeriod(1000);  
  timer.refresh ();
  timer.resume ();
  // Low-Low : Stop
  pwmWrite(MOTOR_PINB, 0);
  digitalWrite(MOTOR_PINA, LOW);
  Motor_status((MOTOR_T)5);
}

/*******************************************************
 *    function      : Motor_status
 *    Description   : set gokit motor speed.
 *    return        : none
 *
 *    --2015-7-1
******************************************************/
void Motor_status(MOTOR_T motor_speed)
{

  unsigned char Temp_motor_speed = 0;
  if (motor_speed <= 5) //停止
  {
    digitalWrite(MOTOR_PINA, LOW);
    pwmWrite(MOTOR_PINB, 0);
  }
  if (motor_speed > 5) //正转
  {
    Temp_motor_speed = (motor_speed - 5) * 51;
    if (Temp_motor_speed > 255) Temp_motor_speed = 255;
    digitalWrite(MOTOR_PINA, LOW);
    pwmWrite( MOTOR_PINB, (int (Temp_motor_speed)<<7) );
  }
  if (motor_speed < 5) //反转
  {
   Temp_motor_speed = 255 - (5 - motor_speed) * 51; //Temp_motor_speed = (255 - (5 + motor_speed)) * 51;
    if (Temp_motor_speed > 255) Temp_motor_speed = 255;
    digitalWrite(MOTOR_PINA, HIGH);
    pwmWrite( MOTOR_PINB, (int (Temp_motor_speed)<<7) );
  }
}

/*******************************************************
 *    function      : gokit_time_ms
 *    Description   : gokit running time form power on
 *    return        : gokit running time(ms).
 *    Add by Alex.lin    --2014-12-25
******************************************************/
unsigned long gokit_time_ms(void)
{
  return millis();
}
/*******************************************************
 *    function      : gokit_time_m
 *    Description   : gokit running time form power on
 *    return        : gokit running time(m).
 *    Add by Alex.lin    --2014-12-25
******************************************************/
unsigned long gokit_time_s(void)
{
  return millis() / 1000;
}

/*******************************************************
 *    function      : gokit_key1down
 *    Description   : check the gokit key1 event
 *    return        : KEY1_LONG_PRESS  KEY1_SHORT_PRESS
 *                     0-no keydown event.
 *    Add by Alex.lin    --2014-12-25
******************************************************/
char gokit_key1down(void)
{
  int unsigned long keep_time = 0;
  if (digitalRead(KEY1) == LOW)
  {
    delay(100);
    if (digitalRead(KEY1) == LOW)
    {
      keep_time = gokit_time_s();
      while (digitalRead(KEY1) == LOW)
      {
        if ((gokit_time_s() - keep_time) > KEY_LONG_TIMER)
        {
          Last_KeyTime = gokit_time_s();
          return KEY1_LONG_PRESS;
        }
      } //until open the key

      if ((gokit_time_s() - Last_KeyTime) > KEY_LONG_TIMER)
      {
        return KEY1_SHORT_PRESS;
      }
      return 0;
    }
    return 0;
  }
  return 0;
}

/*******************************************************
 *    function      : gokit_key2down
 *    Description   : check the gokit key2 event
 *    return        : KEY2_LONG_PRESS  KEY2_SHORT_PRESS
 *                     0-no keydown event.
 *    Add by Alex.lin    --2014-12-25
******************************************************/
char gokit_key2down(void)
{
  int unsigned long keep_time = 0;
  if (digitalRead(KEY2) == LOW)
  {
    delay(100);
    if (digitalRead(KEY2) == LOW)
    {
      keep_time = gokit_time_s();
      while (digitalRead(KEY2) == LOW) //until open the key
      {

        if ((gokit_time_s() - keep_time) > KEY_LONG_TIMER)
        {
          Last_KeyTime = gokit_time_s();
          return KEY2_LONG_PRESS;
        }
      }

      if ((gokit_time_s() - Last_KeyTime) > KEY_LONG_TIMER)
      {
        return KEY2_SHORT_PRESS;
      }
      return 0;
    }
    return 0;
  }
  return 0;
}

/*******************************************************
 *    function      : gokit_keydown
 *    Description   : check the gokit key1 or key2 event
 *    return        : KEY1_LONG_PRESS  KEY1_SHORT_PRESS
 *                    KEY2_LONG_PRESS  KEY2_SHORT_PRESS
 *                     0-no keydown event.
 *    Add by Alex.lin    --2014-12-25
******************************************************/
char gokit_keydown(void)
{
  char ret = 0;
  ret |= gokit_key2down();
  ret |= gokit_key1down();
  return ret;

}

void KEY_Handle(void)
{
  /*  长按是指按住按键3s以上   */
  switch (gokit_keydown())
  {
    case KEY1_SHORT_PRESS:
#if (DEBUG==1)
      Serial.println(F("KEY1_SHORT_PRESS"));
#endif
      //LED_RGB_Control(0, 0, 0);
      break;
    case KEY1_LONG_PRESS:
#if (DEBUG==1)
      Serial.println(F("KEY1_LONG_PRESS ,Wifi Reset"));
#endif
      //LED_RGB_Control(0, 10, 0);
      GizWits_D2WResetCmd();
      break;
    case KEY2_SHORT_PRESS:
#if (DEBUG==1)
      Serial.println(F("KEY2_SHORT_PRESS Soft AP mode"));
#endif
      //Soft AP mode, RGB red
      LED_RGB_Control(10, 0, 0);
      GizWits_D2WConfigCmd(SoftAp_Mode);
      NetConfigureFlag = 1;
      break;
    case KEY2_LONG_PRESS:
#if (DEBUG==1)
      Serial.println(F("KEY2_LONG_PRESS ,AirLink mode"));
#endif
      //AirLink mode, RGB green
      LED_RGB_Control(0, 10, 0);
      GizWits_D2WConfigCmd(AirLink_Mode);
      NetConfigureFlag = 1;
      break;
    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : GizWits_WiFiStatueHandle
* Description    : Callback function , Judge Wifi statue
* Input          : None
* Output         : None
* Return         : Bit , Attr_Flags
* Attention     :
*******************************************************************************/
void GizWits_WiFiStatueHandle(uint16_t wifiStatue)
{
  if (((wifiStatue & Wifi_ConnClouds) == Wifi_ConnClouds) && (NetConfigureFlag == 1) ) //&& (NetConfigureFlag == 1)
  {
#if(DEBUG==1)
    Serial.println("W2M->Wifi_ConnClouds");
#endif
    NetConfigureFlag = 0;
    LED_RGB_Control(0, 0, 0);
  }
}

void GoKit_Init()
{
#if(DEBUG==1)
  //自定义引脚通信SoftwareSerial初始
  Serial.begin(9600);
#endif

  //温度传感初始
  dht.begin();

  //RGB LED初始
  leds.init();
  // digitalWrite(A0, HIGH);//使能RGB LED
  digitalWrite(PB9, HIGH); // data
  
  pinMode(PB15, OUTPUT);

  //按键初始
  pinMode(KEY1, INPUT_PULLUP); //KEY1 上拉输入
  pinMode(KEY2, INPUT_PULLUP); //KEY2 上拉输入

  //attachInterrupt(0, gokit_IR_event, CHANGE);//当引脚电平发生变化,触发中断函数gokit_IR_event pin 2

  //电机初始
  Motor_Init();
  LED_RGB_Control(0, 0, 0);

  memset(&ReadTypeDef, 0, sizeof(ReadTypeDef));
  ReadTypeDef.Motor = exchangeBytes(5);//“Motor_Speed”默认上报值应该是5
  memset(&WirteTypeDef, 0, sizeof(WirteTypeDef));
  GizWits_init(sizeof(ReadTypeDef_t));
}

void setup()
{
  GoKit_Init();

#if (DEBUG==1)
  Serial.println(F("GoKit init  OK!"));
  Serial.print(F("freeMemory()="));
  // Serial.println(freeMemory());
  Serial.println(F("64K"));
#endif

}
void loop()
{
  uint8_t ret = 0;
  uint8_t buf[256];

  KEY_Handle();
  ret = GizWits_MessageHandle(buf, sizeof(WirteTypeDef_t));
  if (ret == 0)
  {
    memcpy((uint8_t *)&WirteTypeDef, buf, sizeof(WirteTypeDef_t));
    GizWits_ControlDeviceHandle();
    GizWits_DevStatusUpgrade((uint8_t *)&ReadTypeDef, 10 * 60 * 1000, 1, NetConfigureFlag);
  }
  if (gaterSensorFlag != 0)
  {
    GizWits_GatherSensorData();
    gaterSensorFlag = 0;
  }
  GizWits_DevStatusUpgrade((uint8_t *)&ReadTypeDef, 10 * 60 * 1000, 0, NetConfigureFlag);

}

void GizWits_ControlDeviceHandle(void)
{
  if ( (WirteTypeDef.Attr_Flags & (1 << 0)) == (1 << 0))
  {
    if (Set_LedStatus != 1)
    {
      if (WirteTypeDef.LED_Cmd == LED_OnOff)
      {
        LED_RGB_Control(0, 0, 0);
        ReadTypeDef.LED_Cmd = LED_OnOff;
#if(DEBUG==1)
        Serial.print(F("SetLED_Off")); Serial.println("");
#endif
      }
      if (WirteTypeDef.LED_Cmd == LED_OnOn)
      {
        ReadTypeDef.LED_Cmd = LED_OnOn;
        LED_RGB_Control(254, 0, 0);
#if(DEBUG==1)
        Serial.print(F("SetLED_On")); Serial.println("");
#endif
      }
    }

  }
  if ( (WirteTypeDef.Attr_Flags & (1 << 1)) == (1 << 1))
  {
    if (WirteTypeDef.LED_Cmd == LED_Costom)
    {
      ReadTypeDef.LED_Cmd = LED_Costom;
      ReadTypeDef.LED_R = 0;
      ReadTypeDef.LED_G = 0;
      ReadTypeDef.LED_B = 0;
      Set_LedStatus = 0;
      LED_RGB_Control(0, 0, 0);
#if(DEBUG==1)
      Serial.print(F("SetLED LED_Costom")); Serial.println("");
#endif
    }
    if (WirteTypeDef.LED_Cmd == LED_Yellow)
    {
      Set_LedStatus = 1;
      ReadTypeDef.LED_Cmd = LED_Yellow;
      ReadTypeDef.LED_R = 254;
      ReadTypeDef.LED_G = 254;
      ReadTypeDef.LED_B = 0;

      LED_RGB_Control(254, 254, 0);
#if(DEBUG==1)
      Serial.print(F("SetLED LED_Yellow")); Serial.println("");
#endif
    }

    if (WirteTypeDef.LED_Cmd == LED_Purple)
    {
      ReadTypeDef.LED_Cmd = LED_Purple;
      ReadTypeDef.LED_R = 254;
      ReadTypeDef.LED_G = 0;
      ReadTypeDef.LED_B = 70;
      Set_LedStatus = 1;
      LED_RGB_Control(254, 0, 70);
#if(DEBUG==1)
      Serial.print(F("SetLED LED_Purple")); Serial.println("");
#endif
    }
    if (WirteTypeDef.LED_Cmd == LED_Pink)
    {
      ReadTypeDef.LED_Cmd = LED_Pink;
      ReadTypeDef.LED_R = 238;
      ReadTypeDef.LED_G = 30;
      ReadTypeDef.LED_B = 30;
      Set_LedStatus = 1;
      LED_RGB_Control(238 , 30 , 30);
#if(DEBUG==1)
      Serial.print(F("SetLED LED_Pink")); Serial.println("");
#endif
    }
  }
  if ( (WirteTypeDef.Attr_Flags & (1 << 2)) == (1 << 2))
  {
    if (Set_LedStatus != 1)
    {
      ReadTypeDef.LED_R = WirteTypeDef.LED_R;
#if(DEBUG==1)
      Serial.print(F("W2D Control LED_R = ")); Serial.print(WirteTypeDef.LED_R, HEX); Serial.println("");
#endif
      LED_RGB_Control(ReadTypeDef.LED_R, ReadTypeDef.LED_G, ReadTypeDef.LED_B);
    }

  }
  if ( (WirteTypeDef.Attr_Flags & (1 << 3)) == (1 << 3))
  {
    if (Set_LedStatus != 1)
    {
      ReadTypeDef.LED_G = WirteTypeDef.LED_G;
#if(DEBUG==1)
      Serial.print(F("W2D Control LED_G = ")); Serial.print(WirteTypeDef.LED_G, HEX); Serial.println("");
#endif
      LED_RGB_Control(ReadTypeDef.LED_R, ReadTypeDef.LED_G, ReadTypeDef.LED_B);
    }

  }
  if ( (WirteTypeDef.Attr_Flags & (1 << 4)) == (1 << 4))
  {
    if (Set_LedStatus != 1)
    {
      ReadTypeDef.LED_B = WirteTypeDef.LED_B;
#if(DEBUG==1)
      Serial.print(F("W2D Control LED_B = ")); Serial.print(WirteTypeDef.LED_B, HEX); Serial.println("");
#endif
      LED_RGB_Control(ReadTypeDef.LED_R, ReadTypeDef.LED_G, ReadTypeDef.LED_B);
    }

  }
  if ( (WirteTypeDef.Attr_Flags & (1 << 5)) == (1 << 5))
  {
    ReadTypeDef.Motor = WirteTypeDef.Motor;
#ifdef MOTOR_16
#if(DEBUG==1)
    Serial.print(F("W2D Control Motor = ")); Serial.print(exchangeBytes(WirteTypeDef.Motor), HEX); Serial.println("");
#endif
    Motor_status(exchangeBytes(WirteTypeDef.Motor));
#else
#if(DEBUG==1)
    Serial.print(F("W2D Control Motor = ")); Serial.print(exchangeBytes(WirteTypeDef.Motor), HEX); Serial.println("");
#endif
    Motor_status(WirteTypeDef.Motor);
#endif
  }
}

/*******************************************************************************
* Function Name  : GizWits_GatherSensorData();
* Description    : Gather Sensor Data
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GizWits_GatherSensorData(void)
{
  uint8_t curTem, curHum;

  ReadTypeDef.Infrared = IR_Handle();
  DHT11_Read_Data(&curTem, &curHum);
  ReadTypeDef.Temperature = (curTem + lastTem) / 2;
  ReadTypeDef.Humidity = (curHum + lastHum) / 2;
  ReadTypeDef.Temperature = ReadTypeDef.Temperature + 13;//Temperature Data Correction
  lastTem = curTem;
  lastHum = curHum;
}

