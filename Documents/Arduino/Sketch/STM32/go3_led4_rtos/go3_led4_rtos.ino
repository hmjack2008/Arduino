//#include <wirish/wirish.h>
//#include "libraries/FreeRTOS/MapleFreeRTOS.h"
#include <MapleFreeRTOS821.h>

int iLED[] = {PB15,PB14,PB11,PB1};
int iLEDhi[] = {8,11,19,25};
int iLEDlow[] = {90,100,180,260};
int iLEDcyl[] = {300,800,1200,1500};

void LEDFtime(int idx, int *pLEDhi, int *pLEDlow, int *pLEDcyl) {
    
    pLEDhi[idx] = pLEDhi[idx]+5;
    if (pLEDhi[idx]>pLEDcyl[idx]) { pLEDhi[idx] = 1; }
    pLEDlow[idx] = iLEDcyl[idx] - pLEDhi[idx];
    /*
    pLEDhi[idx] = pLEDhi[idx]+2;
    if (pLEDhi[idx]>5000) { pLEDhi[idx] = idx*2 + 2; }
    pLEDlow[idx] = pLEDlow[idx]+250;
    if (pLEDlow[idx]>5000) { pLEDlow[idx] = idx*2 + 90; }
    */
    
    /*
    Serial.print("idx/LEDhi/LEDlow : ");
    Serial.print(idx);
    Serial.print("/");
    Serial.print(pLEDhi[idx]);
    Serial.print("/");
    Serial.print(pLEDlow[idx]);
    Serial.println("\n");
    */
}

portTickType xTimeStaDelta1 = 0;
static void vTimeStatistics(void *pvParameters) {
    for (;;) {
        Serial.println(xTimeStaDelta1); // print out : us
        vTaskDelay(5000);
	}
}

static void vLEDFlashTask1(void *pvParameters) {
    portTickType xLastWakeTimeHi;
    portTickType xLastWakeTimeLow;
    portTickType xTimeSta0 = xTaskGetTickCount();
    portTickType xTimeSta1 = 0;

    int idx = 0;
    int iLight = 1;
    xLastWakeTimeHi = xTimeSta0;
    xLastWakeTimeLow = xTimeSta0;
    for (;;) {
        LEDFtime(idx, iLEDhi, iLEDlow, iLEDcyl);
        for (int i=0;i<2;i++) {
            digitalWrite(iLED[idx], iLight);
            iLight = 1-iLight;
            // vTaskDelay(iLEDhi[idx]);
            vTaskDelayUntil(&xLastWakeTimeHi, pdMS_TO_TICKS(iLEDhi[idx]));

            //digitalWrite(iLED[idx], LOW);
            // vTaskDelay(iLEDlow[idx]);
            //vTaskDelayUntil(&xLastWakeTimeLow, pdMS_TO_TICKS(500));
        }
        xTimeSta1 = xTaskGetTickCount();
        xTimeStaDelta1 = (xTimeSta1-xTimeSta0); // (xTimeStaDelta1 - (xTimeStaDelta1>>2)) + ((xTimeSta1-xTimeSta0)>>2);
        xTimeSta0 = xTimeSta1;
    }
}
static void vLEDFlashTask2(void *pvParameters) {
    int idx = 1;
    for (;;) {
        LEDFtime(idx, iLEDhi, iLEDlow, iLEDcyl);
        for (int i=0;i<2;i++) {
            digitalWrite(iLED[idx], HIGH);
            vTaskDelay(iLEDhi[idx]);
            digitalWrite(iLED[idx], LOW);
            vTaskDelay(iLEDlow[idx]);
        }
    }
}
static void vLEDFlashTask3(void *pvParameters) {
    int idx = 2;
    for (;;) {
        LEDFtime(idx, iLEDhi, iLEDlow, iLEDcyl);
        digitalWrite(iLED[idx], HIGH);
        vTaskDelay(iLEDhi[idx]);
        digitalWrite(iLED[idx], LOW);
        vTaskDelay(iLEDlow[idx]);
    }
}
static void vLEDFlashTask4(void *pvParameters) {
    int idx = 3;
    for (;;) {
        LEDFtime(idx, iLEDhi, iLEDlow, iLEDcyl);
        digitalWrite(iLED[idx], HIGH);
        vTaskDelay(iLEDhi[idx]);
        digitalWrite(iLED[idx], LOW);
        vTaskDelay(iLEDlow[idx]);
    }
}

void setup() {
    // initialize the digital pin as an output:
    Serial.begin(9600);
        
    int i = 0;
      for (i=0; i<4; i++) {
        pinMode(iLED[i], OUTPUT);
      }

    xTaskCreate(vLEDFlashTask1,
                "Task1",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY + 2,
                NULL);
    xTaskCreate(vLEDFlashTask2,
                "Task2",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY + 2,
                NULL);
    xTaskCreate(vLEDFlashTask3,
                "Task3",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY + 2,
                NULL);
    xTaskCreate(vLEDFlashTask4,
                "Task4",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY + 2,
                NULL);
    xTaskCreate(vTimeStatistics,
                "TimeStatistics",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY + 2,
                NULL);

    vTaskStartScheduler();
}

void loop() {
    // Insert background code here
}


