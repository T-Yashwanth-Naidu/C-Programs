/**
 * @file sensors.c
 * @brief Implements sensor update functions for the AEB system simulation.
 *
 * This module defines functions to update the sensor readings for the Automated
 * Emergency Braking (AEB) system. Each sensor (Ultrasonic, Speed, and Brake
 * Pressure) is represented by its own structure, and these functions update the
 * respective sensor's data using an object-oriented approach.
 */

#include "sensors.h"

/**
 * @brief Updates the distance value of the Ultrasonic Sensor.
 *
 * This function sets the distance reading for an UltrasonicSensor object. It
 * first checks whether the object pointer is valid, and then updates the
 * object's distance field with the provided value.
 *
 * @param self Pointer to an UltrasonicSensor object.
 * @param distance The new distance value to set (in meters).
 */
void ultrasonic_sensor_update(struct UltrasonicSensor *self, float distance) {
  // Check if the sensor object is valid.
  if (!self)
    return;
  // Update the sensor's distance value.
  self->distance = distance;
}

/**
 * @brief Updates the speed value of the Speed Sensor.
 *
 * This function sets the current speed for a SpeedSensor object. It first
 * validates the pointer, then updates the object's speed field with the
 * provided value.
 *
 * @param self Pointer to a SpeedSensor object.
 * @param speed The new speed value to set (in meters per second).
 */
void speed_sensor_update(struct SpeedSensor *self, float speed) {
  // Validate the sensor object before updating.
  if (!self)
    return;
  // Update the sensor's speed value.
  self->speed = speed;
}

/**
 * @brief Updates the pressure value of the Brake Pressure Sensor.
 *
 * This function sets the brake pressure for a BrakePressureSensor object. After
 * ensuring the object pointer is not NULL, it updates the sensor's pressure
 * field with the new value.
 *
 * @param self Pointer to a BrakePressureSensor object.
 * @param pressure The new brake pressure value to set (in PSI).
 */
void brake_pressure_sensor_update(struct BrakePressureSensor *self,
                                  float pressure) {
  // Ensure the sensor object is valid.
  if (!self)
    return;
  // Update the sensor's pressure value.
  self->pressure = pressure;
}
