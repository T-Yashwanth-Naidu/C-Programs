/**
 * @file aeb_system.c
 * @brief Implements the functions for the Automated Emergency Braking (AEB)
 * system.
 *
 * This module defines the initialization and operational logic for an AEB
 * system using an object-oriented approach in C. It updates sensor values,
 * determines whether the braking system should be activated based on sensor
 * inputs, and applies or releases the brakes accordingly.
 */

#include "aeb_system.h"
#include <stdio.h>

/**
 * @brief Initializes the AEB system object.
 *
 * This function sets the default state for an AEBSystem instance by:
 *  - Resetting the brake applied flag.
 *  - Clearing the exit flag (used for thread termination).
 *  - Initializing sensor values:
 *      - Ultrasonic sensor is set to 100.0 meters to indicate no obstacle.
 *      - Speed sensor is set to 20.0 m/s as the initial vehicle speed.
 *      - Brake pressure sensor is set to 0.0 PSI, indicating brakes are not
 * applied.
 *
 * @param self Pointer to the AEBSystem object to initialize.
 */
void aeb_system_init(struct AEBSystem *self) {
  // Validate the object pointer to prevent dereferencing a NULL pointer.
  if (!self)
    return;

  // Set initial brake state: brakes are not applied.
  self->brake_applied = 0;
  // Set the exit flag to false (0) to indicate the system should keep running.
  self->exit_flag = 0; // Initialize exit flag to false

  // Initialize sensor values with default settings:
  // Set ultrasonic sensor distance to 100.0 meters (no nearby obstacle).
  ultrasonic_sensor_update(&self->distance_sensor, 100.0f);
  // Set vehicle speed to 20.0 m/s as the starting speed.
  speed_sensor_update(&self->speed_sensor, 20.0f);
  // Set brake pressure sensor to 0.0 PSI (no brakes applied).
  brake_pressure_sensor_update(&self->pressure_sensor, 0.0f);
}

/**
 * @brief Updates the AEB system state based on current sensor readings.
 *
 * This function evaluates sensor data to determine whether the braking system
 * should be activated. It checks if an obstacle is detected within a critical
 * distance (less than 2.0 meters) while the vehicle is in motion (speed greater
 * than 0.5 m/s). If both conditions are met, it calls aeb_apply_brakes() to
 * engage the braking system; otherwise, it calls aeb_release_brakes() to
 * disengage the brakes.
 *
 * @param self Pointer to the AEBSystem object to update.
 */
void aeb_system_update(struct AEBSystem *self) {
  // Validate the object pointer.
  if (!self)
    return;

  // Check for imminent collision conditions:
  // - Obstacle is less than 2.0 meters away.
  // - Vehicle speed is greater than 0.5 m/s.
  if (self->distance_sensor.distance < 2.0f &&
      self->speed_sensor.speed > 0.5f) {
    // Engage braking system if collision is imminent.
    aeb_apply_brakes(self);
  } else {
    // Otherwise, ensure that brakes are released.
    aeb_release_brakes(self);
  }
}

/**
 * @brief Engages the braking system.
 *
 * This function sets the internal state of the AEBSystem to indicate that
 * brakes are applied. It simulates applying the brakes by setting the brake
 * pressure sensor value to 50.0 PSI and outputs a notification to the console.
 *
 * @param self Pointer to the AEBSystem object on which to apply brakes.
 */
void aeb_apply_brakes(struct AEBSystem *self) {
  // Validate the object pointer.
  if (!self)
    return;

  // Mark that the brakes are applied.
  self->brake_applied = 1;
  // Simulate the brake pressure (50.0 PSI).
  self->pressure_sensor.pressure = 50.0f;
  // Output a console message to indicate that brakes have been applied.
  printf("🚨 Brakes Applied! 🚨\n");
}

/**
 * @brief Releases the braking system.
 *
 * This function resets the AEBSystem state to indicate that the brakes are not
 * applied. It simulates releasing the brakes by setting the brake pressure
 * sensor value to 0.0 PSI and outputs a confirmation message to the console.
 *
 * @param self Pointer to the AEBSystem object on which to release brakes.
 */
void aeb_release_brakes(struct AEBSystem *self) {
  // Validate the object pointer.
  if (!self)
    return;

  // Mark that the brakes are released.
  self->brake_applied = 0;
  // Simulate zero brake pressure.
  self->pressure_sensor.pressure = 0.0f;
  // Output a console message to confirm that brakes have been released.
  printf("✅ Brakes Released\n");
}
