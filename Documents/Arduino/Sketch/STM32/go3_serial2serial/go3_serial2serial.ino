void setup() {
    Serial.begin(115200);
    delay(100);
    Serial1.begin(115200);
    delay(100);
}

void loop() {
    if (Serial.available() > 0) {
        Serial1.print(char( Serial.read() ));
    }
    if (Serial1.available() > 0) {
        Serial.print(char( Serial1.read() ));
    }
}
