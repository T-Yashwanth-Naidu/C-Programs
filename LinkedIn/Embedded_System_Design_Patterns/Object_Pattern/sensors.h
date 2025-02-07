#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

/**
 * @brief Structure representing an ultrasonic sensor used for obstacle detection.
 *
 * This sensor measures the distance between the vehicle and an obstacle.
 * The distance value is used by the AEB system to determine whether braking is necessary.
 */
struct UltrasonicSensor {
    float distance; /**< Distance reading from the sensor in meters. */
};

/**
 * @brief Structure representing a wheel speed sensor.
 *
 * This sensor measures the current speed of the vehicle.
 * The speed value is used to assess whether the vehicle is in motion and to adjust dynamic behavior.
 */
struct SpeedSensor {
    float speed; /**< Current speed reading from the sensor in meters per second. */
};

/**
 * @brief Structure representing a brake pressure sensor.
 *
 * This sensor monitors the pressure applied to the brakes.
 * The pressure reading helps determine the state of the braking system.
 */
struct BrakePressureSensor {
    float pressure; /**< Current brake pressure reading in PSI (pounds per square inch). */
};

/* Function Prototypes for Sensor Updates */

/**
 * @brief Updates the distance reading of an ultrasonic sensor.
 *
 * This function sets the distance value of the given UltrasonicSensor object.
 *
 * @param self Pointer to an UltrasonicSensor instance.
 * @param distance New distance value to be updated (in meters).
 */
void ultrasonic_sensor_update(struct UltrasonicSensor *self, float distance);

/**
 * @brief Updates the speed reading of a wheel speed sensor.
 *
 * This function sets the speed value of the given SpeedSensor object.
 *
 * @param self Pointer to a SpeedSensor instance.
 * @param speed New speed value to be updated (in meters per second).
 */
void speed_sensor_update(struct SpeedSensor *self, float speed);

/**
 * @brief Updates the brake pressure reading of a brake pressure sensor.
 *
 * This function sets the pressure value of the given BrakePressureSensor object.
 *
 * @param self Pointer to a BrakePressureSensor instance.
 * @param pressure New pressure value to be updated (in PSI).
 */
void brake_pressure_sensor_update(struct BrakePressureSensor *self, float pressure);

#endif /* SENSORS_H */
