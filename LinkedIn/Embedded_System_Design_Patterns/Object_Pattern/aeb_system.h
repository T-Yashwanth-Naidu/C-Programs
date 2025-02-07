#ifndef AEB_SYSTEM_H
#define AEB_SYSTEM_H

#include "sensors.h"        // Include definitions for sensor structures (e.g., UltrasonicSensor, SpeedSensor, BrakePressureSensor)
#include <pthread.h>        // Include POSIX threads API for thread synchronization primitives (pthread_mutex_t)
#include <stdint.h>         // Include standard integer types

/**
 * @brief Structure representing the Automated Emergency Braking (AEB) system.
 *
 * This structure encapsulates all components and state variables required for the AEB system.
 * It includes sensor objects for detecting obstacles, measuring vehicle speed, and monitoring brake pressure.
 * Additionally, it contains flags for brake status and termination control, as well as a mutex for ensuring
 * thread-safe access in a multi-threaded environment.
 */
struct AEBSystem {
    struct UltrasonicSensor distance_sensor; /**< Ultrasonic sensor object used for obstacle detection. */
    struct SpeedSensor speed_sensor;         /**< Speed sensor object used for measuring the vehicle's current speed. */
    struct BrakePressureSensor pressure_sensor; /**< Brake pressure sensor object for monitoring the applied brake pressure. */
    uint8_t brake_applied;                    /**< Flag indicating whether the brakes are applied (1 if applied, 0 if not). */
    pthread_mutex_t lock;                     /**< Mutex to ensure thread-safe access to the AEBSystem object. */
    int exit_flag;                            /**< Flag to signal threads to terminate (0 = continue, non-zero = exit). */
};

/* Function Prototypes */

/**
 * @brief Initializes the AEB system object.
 *
 * This function sets the initial state of the AEBSystem instance:
 * - Resets the brake_applied flag.
 * - Clears the exit_flag used for thread termination.
 * - Initializes all sensor values with their default settings.
 *
 * @param self Pointer to the AEBSystem instance to be initialized.
 */
void aeb_system_init(struct AEBSystem *self);

/**
 * @brief Updates the AEB system state based on current sensor readings.
 *
 * This function processes the sensor data to decide if the braking system should be engaged.
 * If an obstacle is detected within a critical distance while the vehicle is in motion,
 * the function engages the brakes; otherwise, it releases them.
 *
 * @param self Pointer to the AEBSystem instance to update.
 */
void aeb_system_update(struct AEBSystem *self);

/**
 * @brief Engages the braking system.
 *
 * This function simulates the application of brakes by:
 * - Setting the brake_applied flag.
 * - Adjusting the brake pressure sensor value.
 * - Optionally providing a console output to indicate that the brakes have been applied.
 *
 * @param self Pointer to the AEBSystem instance on which to apply brakes.
 */
void aeb_apply_brakes(struct AEBSystem *self);

/**
 * @brief Releases the braking system.
 *
 * This function simulates the release of brakes by:
 * - Clearing the brake_applied flag.
 * - Resetting the brake pressure sensor value.
 * - Optionally providing a console output to confirm that the brakes have been released.
 *
 * @param self Pointer to the AEBSystem instance on which to release brakes.
 */
void aeb_release_brakes(struct AEBSystem *self);

#endif /* AEB_SYSTEM_H */
