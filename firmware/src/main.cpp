#include <Arduino.h>

const int IR_PIN = 2;

void setup() {
  Serial.begin(9600);
}

uint8_t ir_meas(const int pin){
  uint8_t meas = digitalRead(pin);
  delay(10);
  return meas;
}

void loop() {
  Serial.print("IR readeing: ");
  Serial.println(ir_meas(IR_PIN),BIN);
}