JoyState_t joySt;

void setup()
{
	Serial.begin(9600);
	delay(8000);
	Serial.println("JoyStick");
	Serial.println("xAxis \t yAxis \t zAxis \t xRotAxis \t yRotAxis \t zRotAxis \t throttle \t rudder \t hatSw1 \t hatSw2 \t buttons");

	pinMode(13, OUTPUT);
	joySt.xAxis = 0;
	joySt.yAxis = 0;
	joySt.zAxis = 0;
	joySt.xRotAxis = 0;
	joySt.yRotAxis = 0;
	joySt.zRotAxis = 0;
	joySt.throttle = 0;
	joySt.rudder = 0;
	joySt.hatSw1 = 0;
	joySt.hatSw2 = 0;
	joySt.buttons = 0;

  // initialize mouse control :
  Mouse.begin();
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_ESC);
  delay(150);
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.print("joy.cpl");
  delay(500);
  Keyboard.press(KEY_RETURN);
  delay(150);
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('p');
  delay(500);
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_ESC);
  delay(150);
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.print("notepad.exe");
  delay(500);
  Keyboard.press(KEY_RETURN);
  delay(150);
  Keyboard.releaseAll();
  delay(1000);
  
  
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  
  delay(20000);
}

int  iMouseStep = 5;
int  xMouseMovie = 5;
int  yMouseMovie = 0;

void loop()
{
	joySt.xAxis = random(255);
	joySt.yAxis = random(255);
	joySt.zAxis = random(255);
	joySt.xRotAxis = random(255);
	joySt.yRotAxis = random(255);
	joySt.zRotAxis = random(255);
	// joySt.throttle = random(255);
	joySt.rudder = random(255);

	joySt.buttons <<= 1;
	if (joySt.buttons == 0)  joySt.buttons = 1;

/*
// Hat switch : 
// The raw value from hat switch control. 
// Usually 0 to 7 representing the 8 directions, and a number outside this range, 
// e.g. 8, meaning not pressed
// The direction the switch has been pressed in degrees, 0-315 for an 8 position switch. 
// -1 represents no press.
*/
	if (++joySt.hatSw1 > 9)  joySt.hatSw1 = 0;
	joySt.hatSw2 = 9 - joySt.hatSw1;

	if (++joySt.throttle > 255)  joySt.throttle = 0;
	if (joySt.throttle > 127)  digitalWrite(13, HIGH);
	else  digitalWrite(13, LOW);

	Serial.print(joySt.xAxis); Serial.print("X\t ");
	Serial.print(joySt.yAxis); Serial.print("Y\t ");
	Serial.print(joySt.zAxis); Serial.print("Z\t ");
	Serial.print(joySt.xRotAxis); Serial.print("x\t ");
	Serial.print(joySt.yRotAxis); Serial.print("y\t ");
	Serial.print(joySt.zRotAxis); Serial.print("z\t ");
	Serial.print(joySt.throttle); Serial.print("T\t ");
	Serial.print(joySt.rudder); Serial.print("R\t ");
	Serial.print(joySt.hatSw1); Serial.print("H\t ");
	Serial.print(joySt.hatSw2); Serial.print("h\t ");
	Serial.print(joySt.buttons, BIN); Serial.print("B\n");

	// Call Joystick.move
	Joystick.setState(&joySt);

    // Call Keyboard Mouse
    if (!digitalRead(2)) {
	Keyboard.print("Message from USB_HID Keyboard and Mouse ! \n");

        for (int i=0; i<10; i++)
        {
            Mouse.move(xMouseMovie, yMouseMovie, 0);
            delay(80);
        }
    
        if ((xMouseMovie >0) && (yMouseMovie ==0))  
          { xMouseMovie = 0; yMouseMovie = iMouseStep; Keyboard.print("1 0 \n");}
        else 
          { 
            if ((xMouseMovie ==0) && (yMouseMovie >0))  { xMouseMovie = -1 * iMouseStep; yMouseMovie = 0; Keyboard.print("0 1 \n");}
            else 
              {
                if ((xMouseMovie <0) && (yMouseMovie ==0))  { xMouseMovie = 0; yMouseMovie = -1 * iMouseStep; Keyboard.print("-1 0 \n");}
                else 
                  {
                    if ((xMouseMovie ==0) && (yMouseMovie <0))  { xMouseMovie = iMouseStep; yMouseMovie = 0; Keyboard.print("0 -1 \n");};
                  }
              }
          } 

      } // if (digitalRead(2))


    delay(2000);
}

