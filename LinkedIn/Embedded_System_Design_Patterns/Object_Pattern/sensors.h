#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

// Ultrasonic Sensor for obstacle detection.
struct UltrasonicSensor {
    float distance;
};

// Wheel Speed Sensor for measuring vehicle speed.
struct SpeedSensor {
    float speed;
};

// Brake Pressure Sensor.
struct BrakePressureSensor {
    float pressure;
};

// Function prototypes for sensor updates.
void ultrasonic_sensor_update(struct UltrasonicSensor *self, float distance);
void speed_sensor_update(struct SpeedSensor *self, float speed);
void brake_pressure_sensor_update(struct BrakePressureSensor *self, float pressure);

#endif
