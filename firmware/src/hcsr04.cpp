#include "hcsr04.h"
 
 HCSR04::HCSR04(){
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 }

 float HCSR04::measure(){
    long duration;
    int distanceCm;
    int distanceInch;

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
    distanceCm = duration * soundSpeed/2;

    // Convert to inches
    distanceInch = distanceCm * cmToInch;

    return distanceCm;
 };