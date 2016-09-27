//#include <wirish/wirish.h>
//#include "libraries/FreeRTOS/MapleFreeRTOS.h"
#include <MapleFreeRTOS821.h>

int iLED[] = {PB15,PB14,PB11,PB1};
int iLEDhi[] = {8,11,19,25};
int iLEDlow[] = {90,100,180,260};
int iLEDcyl[] = {300,800,1200,1500};


portTickType xTime1 = 0;
portTickType xTimeStaDelta0 = 0;
portTickType xTimeStaDelta1 = 0;
portTickType xTimeS0 = 0;
portTickType xTimeS1 = 0;
	
static void vTimeStatistics(void *pvParameters) {
    for (;;) {
        Serial.println( (xTimeS0-xTime1) );
        Serial.println(xTimeS0); // print out : ms
        Serial.println(xTimeS1); // print out : ms
        Serial.println(xTimeStaDelta0); // print out : ms
        Serial.println(xTimeStaDelta1); // print out : ms
        Serial.println("----------");
        Serial.println( pdMS_TO_TICKS(1) );
        Serial.println( pdMS_TO_TICKS(1000) );
        Serial.println( 72000000/portTICK_PERIOD_MS );
        Serial.println( portTICK_PERIOD_MS );
        xTime1 = xTimeS1;
        Serial.println("==========");
        vTaskDelay( 150 );
	}
}

static void vLEDminiTask1(void *pvParameters) {
    portTickType xLastWakeTime;
    portTickType xTimeSta0 = xTaskGetTickCount();
    portTickType xTimeSta1 = 0;

    xLastWakeTime = xTimeSta0;
    for (;;) {
        //for (int i=0;i<1;i++) {

            // vTaskDelay(iLEDhi[idx]);
            vTaskDelayUntil(&xLastWakeTime, 1);

        //}
        xTimeSta1 = xTaskGetTickCount();
        xTimeStaDelta0 = (xTimeSta1-xTimeS0);
		xTimeS1 = xTimeSta1;
        // (xTimeStaDelta1 - (xTimeStaDelta1>>2)) + ((xTimeSta1-xTimeSta0)>>2);
        xTimeStaDelta1 = (xTimeSta1-xTimeSta0);
        xTimeS0 = xTimeSta0;
        xTimeSta0 = xTimeSta1;
    }
}

void setup() {
    // initialize the digital pin as an output:
    Serial.begin(9600);
        
    int i = 0;
      for (i=0; i<4; i++) {
        pinMode(iLED[i], OUTPUT);
      }

    xTaskCreate(vLEDminiTask1,
                "Task1",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY + 2,
                NULL);
    xTaskCreate(vTimeStatistics,
                "TimeStatistics",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY + 3,
                NULL);

    vTaskStartScheduler();
}

void loop() {
    // Insert background code here
}


