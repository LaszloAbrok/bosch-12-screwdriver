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

// Declaration for the HC-SR04 UH distance sensor.
/*
const int trigPin = 12;
const int echoPin = 15;
*/

// Define sound speed in cm/uS.
/*
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
*/

// Declaration for the HC-SR04 UH distance sensor.
/*
long duration;
int distanceCm;
int distanceInch;
*/

HCSR04 distanceSensor;

// Declaration pin for FSR07BE force pressure resistor.
const int fsrAnalogPin = 0;
int fsrReading;

/*
void setup_HC_SR04(){
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}
*/

/*
float read_HC_SR04(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  

  return distanceCm;
}
*/

void setup() {
  Serial.begin(115200);
  //setup_HC_SR04();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(500);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  
  while (!Serial)
  {
  };
  LIS.begin(WIRE,0x19); //IIC init
  delay(100);
  LIS.setFullScaleRange(LIS3DHTR_RANGE_2G);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  
}

void loop() {

  // read HC-SR04
  //float distance = read_HC_SR04();
  float distance = distanceSensor.measure();

  Serial.print("Distance (cm): ");
  Serial.println(distance);

  fsrReading = analogRead(fsrAnalogPin);
  
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
  
  display.clearDisplay();
  display.setCursor(50, 25);
  // Display distance in cm
  display.print(distance);
  display.display();
  
  // Display distance in inches
  /*display.print(distanceInch);
  display.print(" in");
  display.display();
  */

  
  if(!LIS){
    Serial.println("LIS3DHTR didn't connect.");
    while (1)
      ;
    return;
  }

  Serial.print("x:"); Serial.print(LIS.getAccelerationX()); Serial.print("  ");
  Serial.print("y:"); Serial.print(LIS.getAccelerationY()); Serial.print("  ");
  Serial.print("z:"); Serial.println(LIS.getAccelerationZ());
  
  
  delay(500);
}
