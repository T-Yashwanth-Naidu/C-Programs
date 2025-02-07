/**
 * @file main.c
 * @brief Main entry point for the AEB system simulation.
 *
 * @overview
 * This program simulates an Automated Emergency Braking (AEB) system in a
 * multi-threaded embedded C environment. The simulation models a vehicle with
 * dynamic speed and obstacle detection capabilities using sensor data. The
 * system's key components are:
 *
 * - Sensor Modules: Simulated sensors include an ultrasonic sensor (for
 * obstacle distance), a speed sensor (for vehicle speed), and a brake pressure
 * sensor.
 *
 * - AEB Logic: Based on the sensor readings, the AEB system determines
 * whether to engage or release the brakes. When an obstacle is detected within
 * a critical distance (less than 2.0 m) and the vehicle is moving, the system
 * applies the brakes.
 *
 * - Input Handling: A dedicated thread processes user input in non-blocking
 * mode. Users can simulate different driving scenarios:
 *      - Press 'a' to simulate an imminent accident (obstacle distance set
 * to 1.0 m).
 *      - Press 'n' to return to normal driving (obstacle distance reset to
 * 100.0 m).
 *      - Press 'q' to quit the simulation.
 *
 * - Dynamic Motion Simulation: The vehicle's speed is dynamically adjusted:
 *      - Under normal conditions, the speed fluctuates randomly within a
 * defined range.
 *      - When brakes are applied, the vehicle decelerates rapidly but does not
 * fall below a minimum speed threshold.
 *
 * - Multi-Threading and Object Pattern: The system utilizes separate
 * threads for input processing and system updates. It follows the Object
 * Pattern by encapsulating all system state within an AEBSystem structure and
 * ensuring thread safety with mutex locking.
 *
 * The main function initializes the system, starts the threads, and cleans up
 * resources upon exit.
 */

#include "aeb_system.h" // Contains the definition and prototypes for the AEB system
#include "input_handler.h" // Contains the input processing thread function and terminal handling
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/**
 * @brief Thread function for updating the AEB system state and simulating
 * vehicle motion.
 *
 * This function continuously updates the AEB system by:
 *  - Locking the system state for thread-safe access.
 *  - Checking the exit flag to terminate the thread when required.
 *  - Calling aeb_system_update() to process sensor inputs and apply/release
 * brakes.
 *  - Simulating vehicle motion:
 *      - If brakes are applied, the vehicle decelerates quickly (but not below
 * a minimum speed).
 *      - If brakes are not applied, the vehicle speed is randomly adjusted
 * within a defined range.
 *  - Copying sensor data locally and printing the system status.
 *  - Sleeping for 500 milliseconds before the next update cycle.
 *
 * @param arg Pointer to an AEBSystem instance.
 * @return Always returns NULL.
 */
void *update_aeb_system(void *arg) {
  // Cast the argument to an AEBSystem pointer.
  struct AEBSystem *self = (struct AEBSystem *)arg;

  // Define speed limits and rates for normal driving simulation.
  const float MIN_NORMAL_SPEED = 29.0f; // Lower bound (~65 mph)
  const float MAX_NORMAL_SPEED = 33.0f; // Upper bound (~74 mph)
  const float DECELERATION_RATE =
      10.0f;                     // Braking deceleration (m/s per update)
  const float MIN_SPEED = 10.0f; // Minimum allowed speed during braking

  // Main update loop
  while (1) {
    // Lock the AEB system to ensure thread-safe access.
    pthread_mutex_lock(&self->lock);

    // If exit flag is set, release the lock and break the loop to terminate the
    // thread.
    if (self->exit_flag) {
      pthread_mutex_unlock(&self->lock);
      break;
    }

    // Update the AEB logic based on current sensor readings.
    aeb_system_update(self);

    // --- Dynamic Motion Simulation ---
    if (self->brake_applied) {
      // If brakes are applied, decelerate quickly (but not below MIN_SPEED).
      if (self->speed_sensor.speed > MIN_SPEED) {
        self->speed_sensor.speed -= DECELERATION_RATE;
        if (self->speed_sensor.speed < MIN_SPEED)
          self->speed_sensor.speed = MIN_SPEED;
      }
    } else {
      // In normal driving mode, adjust the speed randomly.
      // Calculate a random delta value between 3.5 and 6.5.
      float randomDelta =
          ((float)rand() / (float)RAND_MAX) * (6.5f - 3.5f) + 3.5f;
      // Randomly decide whether to accelerate or decelerate.
      if (rand() % 2 == 0)
        self->speed_sensor.speed += randomDelta;
      else
        self->speed_sensor.speed -= randomDelta;

      // Clamp the speed within the normal driving range.
      if (self->speed_sensor.speed < MIN_NORMAL_SPEED)
        self->speed_sensor.speed = MIN_NORMAL_SPEED;
      if (self->speed_sensor.speed > MAX_NORMAL_SPEED)
        self->speed_sensor.speed = MAX_NORMAL_SPEED;
    }
    // --- End Dynamic Motion Simulation ---

    // Copy sensor data to local variables for thread-safe printing.
    float speed = self->speed_sensor.speed;
    float distance = self->distance_sensor.distance;
    float pressure = self->pressure_sensor.pressure;
    uint8_t brake_status = self->brake_applied;

    // Unlock the AEB system state.
    pthread_mutex_unlock(&self->lock);

    // Clear the terminal screen using ANSI escape codes.
    printf("\033[H\033[J");
    // Print the AEB system status.
    printf("=== AEB SYSTEM STATUS ===\n");
    printf("Vehicle Speed:     %.2f m/s\n", speed);
    printf("Obstacle Distance: %.2f m\n", distance);
    printf("Brake Pressure:    %.2f PSI\n", pressure);
    printf("AEB Status:        %s\n",
           brake_status ? "ACTIVE 🚨" : "INACTIVE ✅");
    printf("\n[Press 'a' for imminent accident]\n");
    printf("[Press 'n' for normal driving]\n");
    printf("[Press 'q' to quit]\n");

    // Sleep for 500 milliseconds before the next update cycle.
    usleep(500000);
  }
  return NULL;
}

/**
 * @brief Main function: Initializes the AEB system simulation and spawns
 * threads.
 *
 * This function:
 *  - Seeds the random number generator.
 *  - Initializes the AEB system and its mutex.
 *  - Creates threads for user input processing and AEB system updates.
 *  - Waits for both threads to finish (using pthread_join).
 *  - Cleans up resources by destroying the mutex and restoring terminal
 * settings.
 *
 * @return int Exit status of the program.
 */
int main() {
  // Create an instance of the AEB system.
  struct AEBSystem car_aeb;

  // Seed the random number generator using the current time.
  srand(time(NULL));

  // Initialize the mutex for thread-safe access.
  pthread_mutex_init(&car_aeb.lock, NULL);
  // Initialize the AEB system with default sensor values and state.
  aeb_system_init(&car_aeb);

  // Thread identifiers for user input and system update threads.
  pthread_t input_thread, update_thread;

  // Create a thread to process user input.
  pthread_create(&input_thread, NULL, process_user_input, (void *)&car_aeb);
  // Create a thread to update the AEB system and simulate vehicle motion.
  pthread_create(&update_thread, NULL, update_aeb_system, (void *)&car_aeb);

  // Wait for both threads to finish execution.
  pthread_join(input_thread, NULL);
  pthread_join(update_thread, NULL);

  // Clean up: Destroy the mutex and restore the terminal to its original
  // settings.
  pthread_mutex_destroy(&car_aeb.lock);
  disable_non_blocking_input();

  return 0;
}
