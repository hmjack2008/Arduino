// This example code is in the public domain.
// Leostick steering wheel & pedals
// Example of Joystick.move()
// Throttle on A0, Brake on A1, steering on A2
// Buttons on D0-5

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  // Enable pullups
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}

void loop() {
  int buttons = digitalRead(0) + (digitalRead(1) << 1) + (digitalRead(2) << 2)
                + (digitalRead(3) << 3) + (digitalRead(4) << 4) + (digitalRead(5) << 5);
  int accel = analogRead(A0);
  int brk = analogRead(A1);
  int steer = analogRead(A2);
        
  // Using pedals from an old gameport wheel
  // range was about 280 - 750 so I trimmed it a bit
  // to give guaranteed full scale output swing
  accel = constrain(accel, 299, 730);
  brk = constrain(brk, 299, 730);

  // map the values to 255-0, using map to invert the output
  // 0 is full throttle/brake, 255 is no throttle/brake
  // It makes sense if you think of 0 being away from you or to your left,
  // and 255 (or 1023 for 10 bit) is closer to you or to your right.
  accel = map(accel, 299, 730, 255, 0);
  brk = map(brk, 299, 730, 255, 0);

  // Convert steering input (0-1023) to a float (-1 to 1)
  float fSteer = steer / 511.5 - 1;
  
  // Non-linear response curve, gives accurate control around center
  // and full lock to lock output.
  // graph y = 0.2 x + 1.8 x^3 - x^5 over the range -1 >= x >= 1
  // to see what I mean
  // also converts back to 0-1023 range once curve is done
  float fSteerOut = ((fSteer * 0.2 + pow(fSteer, 3) * 1.8
                    + pow(fSteer, 5) * -1.0) + 1) * 511.5;

  steer = constrain((int)fSteerOut, 0, 1023);
        
  // Call Joystick.move
  Joystick.move(accel, brk, steer, buttons);

  delay(20);
}


