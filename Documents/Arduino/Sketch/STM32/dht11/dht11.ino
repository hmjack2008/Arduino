
#include "DHT.h"

#define DHTPIN PB3
#define DHTTYPE DHT11   // DHT 11 
// #define DHTTYPE DHT22   // DHT 22  (AM2302)
// #define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor for normal 16mhz Arduino
// DHT dht(DHTPIN, DHTTYPE);

// NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
// might need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// Example to initialize DHT sensor for Arduino Due:
DHT dht(DHTPIN, DHTTYPE, 30);

void setup() {
  Serial.begin(9600); 
  delay(5000);
  Serial.println("DHTxx test!");
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();  delay(50);
  // Read temperature as Celsius
  float t = dht.readTemperature();  delay(50);
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);  delay(50);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: ");  delay(50);
  Serial.print(h);  delay(50);
  Serial.print(" %\t");  delay(50);
  Serial.print("Temperature: ");  delay(50);
  Serial.print(t);  delay(50);
  Serial.print(" *C ");  delay(50);
  Serial.print(f);  delay(50);
  Serial.print(" *F\t");  delay(50);
  Serial.print("Heat index: ");  delay(50);
  Serial.print(hi);  delay(50);
  Serial.println(" *F");  delay(50);
}
