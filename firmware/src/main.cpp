/**
 * The code base contains the 
 * firmware developed at Code #LikeABosch Hackathon
 * 29-30. 09. 2023.
 * Author: Laszlo Abrok
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "LIS3DHTR.h"
#include "hcsr04.h"

// LIS3DHTR TwoWire object
LIS3DHTR<TwoWire> LIS; //IIC
#define WIRE Wire

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

HCSR04 distanceSensor;

// Declaration pin for FSR07BE force pressure resistor.
const int fsrAnalogPin = 0;
int fsrReading;

// Declaration for relay.
const int relayPin = 4;

void setup() {
  Serial.begin(115200);
  // Set relayPin direction
  pinMode(relayPin, OUTPUT);

  // Set up display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(500);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  // Set up gyro
  while (!Serial)
  {
  };
  LIS.begin(WIRE,0x19); //IIC init
  delay(100);
  LIS.setFullScaleRange(LIS3DHTR_RANGE_2G);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);

  digitalWrite(relayPin,LOW);
}


void loop() {
  digitalWrite(relayPin,LOW);

  float distance = distanceSensor.measure();
  Serial.println(distance);
  // Set display text
  // display.clearDisplay();
  display.setCursor(50, 25);
  // Display distance in cm
  display.print(05.89);
  display.display();

  // read HC-SR04
  //float distance = read_HC_SR04();

  //float distance = distanceSensor.measure();

  //Serial.print("Distance (cm): ");
  //Serial.println(distance);

  /*
  display.clearDisplay();
  display.setCursor(50, 25);
  // Display distance in cm
  display.print(distance);
  display.display();
  */

  /*
  while (distance <= 0.00 || distance > 999.99)
  {
    distance = distanceSensor.measure();
  }
  if (distance  < 50.0){

    digitalWrite(relayPin,HIGH);
    delay(5000);
    digitalWrite(relayPin,LOW);
    delay(5000);
  }
  else{
    display.clearDisplay();
    display.setCursor(50, 25);
    // Display distance in cm
    display.print(distance);
    display.display();
  }
  */

  // Print out force pressure resistor data
  fsrReading = analogRead(fsrAnalogPin);
  
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
  
  // Print out gyro data
  if(!LIS){
    Serial.println("LIS3DHTR didn't connect.");
    /*
        while (1)
      ;
    return;
    */
  }
  
  float gyro_x = LIS.getAccelerationX();
  float gyro_y = LIS.getAccelerationY();
  float gyro_z = LIS.getAccelerationZ();

  Serial.println(gyro_x);
  Serial.println(gyro_y);
  Serial.println(gyro_z);

  if(gyro_z>1.0){
    digitalWrite(relayPin,HIGH);
  }

  //Serial.print("x:"); Serial.print(LIS.getAccelerationX()); Serial.print("  ");
  //Serial.print("y:"); Serial.print(LIS.getAccelerationY()); Serial.print("  ");
  //Serial.print("z:"); Serial.println(LIS.getAccelerationZ());
  
  delay(50000);
}
