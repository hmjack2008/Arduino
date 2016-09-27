
const int Tim3Ch1 = PB4; //PA6; PB4; PC6; D5 (pwm)
const int Tim3Ch2 = PB5; //PA7; PB5; PC7; D4
const int Tim3Ch3 = PB0; //PB0;      PC8;
const int Tim3Ch4 = PB1; //PB1;      PC9

int outputValue = 1; // duty value output to the PWM
uint16 max_duty; // set by setPeriod to maximum timer count

// PWM Timer has to be initialized 
HardwareTimer timer( 3 ); 

void setup()
{  
 Serial.begin (9600);

 afio_cfg_debug_ports(AFIO_DEBUG_NONE);
 // afio_remap(AFIO_REMAP_TIM3_FULL);
 afio_remap(AFIO_REMAP_TIM3_PARTIAL); // Tim3Ch1:PB4 Tim3Ch2:PB5
 pinMode(Tim3Ch1, PWM);
 pinMode(Tim3Ch2, OUTPUT);

 // Initialize the Timer for the PWM channels
 timer.pause ();
 timer.setMode(1, TIMER_PWM); // channel_1
 // timer.setMode(2, TIMER_PWM); // channel_2

 // setPeriod( usecs) sets internally the prescaler and max duty count for respective timer
 // and returns the max duty count for given usecs period
 max_duty =  timer.setPeriod(1000); // in microseconds => 1kHz
 // returns  7200 at   100 => 100us 7200count, 1ms 72000count
 // returns 14400 at   200
 // returns 28800 at   400
 // returns 36000 at   500
 // returns 57600 at   800
 // returns 36000 at  1000
 // returns 36828 at  1023
 // returns 36864 at  1024
 // returns 48000 at  2000
 // returns 57600 at  4000
 // returns 64800 at  7200
 // returns 64000 at  8000
 // returns 65455 at 10000

 timer.refresh ();
 timer.resume ();
}

int outputChange = 0;
void loop() {
 // change the PWM duty value:
 pwmWrite(Tim3Ch1, outputValue);
 digitalWrite(Tim3Ch2, outputChange);

 // Print out to see what is going on
 Serial.print(outputValue);
 Serial.print("/");
 Serial.println(max_duty);

 outputChange = 1-outputChange;
 outputValue = outputValue + (max_duty>>5);
 if (outputValue>max_duty) {
   outputValue = 1;
 }

 delay(200);
}
