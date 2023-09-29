#ifndef DISTANCE_SENSOR_H
#include <Arduino.h>

/**
 * @brief Utility class for HC-SR04 UH distance sensor.
 * Author: Laszlo Abrok
*/
class DistanceSensor{
    private:
        int trigPin;
        int echoPin;
        int sound_velocity = 0.034;
        int cm_to_inch = 0.393701;
        long duration;
        float distanceCm;
        float distanceInch;
    public:
    DistanceSensor(int trigPin, int echoPin);

    float measure();
};

#endif