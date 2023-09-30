#ifndef HCSR04_H
#include <Arduino.h>

/**
 * Simple utility class for HCSR04 UH distance sensor.
*/
class HCSR04{
    private:
    
    const int trigPin = 12;
    const int echoPin = 15;
    const float soundSpeed = 0.034;
    const float cmToInch = 0.393701;

    public:
    /**
     * Constructor
    */
    HCSR04();
    /**
     * Measurement
    */
    float measure();
};


#endif