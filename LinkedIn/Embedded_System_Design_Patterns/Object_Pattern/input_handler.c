/**
 * @file input_handler.c
 * @brief Handles non-blocking user input for the AEB system simulation.
 *
 * This module configures the terminal to operate in non-blocking mode so that
 * user input can be captured without waiting for newline characters. It also
 * defines the thread function that processes user input and updates the AEB
 * system accordingly.
 */

#include "input_handler.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

// Static variable to store the original terminal settings.
// This allows restoring the terminal to its original state when the program
// exits.
static struct termios orig_termios;

//------------------------------------------------------------------------------
// Function Definitions
//------------------------------------------------------------------------------

/**
 * @brief Enables non-blocking input mode for the terminal.
 *
 * This function retrieves the current terminal settings, stores them in a
 * static variable, and then modifies the settings to disable canonical mode and
 * echo. In non-canonical mode, input is available immediately without waiting
 * for a newline, and disabling echo prevents characters from being displayed as
 * they are typed.
 */
void enable_non_blocking_input() {
  struct termios ttystate;

  // Retrieve the current terminal settings and store them in orig_termios.
  tcgetattr(STDIN_FILENO, &orig_termios);
  ttystate = orig_termios;

  // Disable canonical mode (ICANON) so that input is processed immediately.
  ttystate.c_lflag &= ~ICANON;
  // Disable echo (ECHO) so that typed characters are not printed to the screen.
  ttystate.c_lflag &= ~ECHO;
  // Set the minimum number of characters for non-blocking read to 0.
  ttystate.c_cc[VMIN] = 0;
  // Set the timeout for non-blocking read to 0 (no waiting).
  ttystate.c_cc[VTIME] = 0;

  // Apply the modified settings immediately.
  tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

/**
 * @brief Restores the original terminal settings.
 *
 * This function resets the terminal to the state it was in before non-blocking
 * input mode was enabled. This is important to ensure that the terminal behaves
 * normally after the program terminates.
 */
void disable_non_blocking_input() {
  // Restore the terminal settings from orig_termios.
  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

/**
 * @brief Retrieves a single character from the standard input in non-blocking
 * mode.
 *
 * This function attempts to read one character from the standard input. Because
 * the terminal is in non-blocking mode, it returns immediately, even if no
 * character is available.
 *
 * @return The character read from the input, or 0 if no character is available.
 */
char get_key_press() {
  char buf = 0;
  // Attempt to read 1 byte from standard input.
  read(STDIN_FILENO, &buf, 1);
  return buf;
}

/**
 * @brief Thread function to process user input.
 *
 * This function continuously checks for user input and updates the AEB system
 * state accordingly. It simulates driving scenarios by modifying sensor
 * readings based on key presses:
 *  - 'a': Simulates an imminent accident by setting the obstacle distance
 * to 1.0 meter.
 *  - 'n': Returns the system to normal driving by setting the obstacle distance
 * to 100.0 meters.
 *  - 'q': Signals the simulation to exit.
 *
 * The function locks the AEB system object before modifying shared data to
 * ensure thread safety.
 *
 * @param arg Pointer to the AEBSystem object.
 * @return NULL upon thread exit.
 */
void *process_user_input(void *arg) {
  // Cast the argument to an AEBSystem pointer.
  struct AEBSystem *self = (struct AEBSystem *)arg;

  // Enable non-blocking input mode.
  enable_non_blocking_input();

  // Main input processing loop.
  while (1) {
    // Get a key press (non-blocking).
    char key = get_key_press();

    // Lock the AEB system to ensure thread-safe modifications.
    pthread_mutex_lock(&self->lock);

    // Check for specific key presses and update system state accordingly.
    if (key == 'a') {
      // Simulate an imminent accident: set obstacle distance to 1.0 meter.
      ultrasonic_sensor_update(&self->distance_sensor, 1.0f);
      printf("\n🚨 Accident Imminent! AEB Engaged!\n");
    } else if (key == 'n') {
      // Return to normal driving: set obstacle distance to 100.0 meters.
      ultrasonic_sensor_update(&self->distance_sensor, 100.0f);
      printf("\n✅ Normal Driving Mode\n");
    } else if (key == 'q') {
      // Signal exit: update exit flag and output exit message.
      printf("\nExiting simulation...\n");
      self->exit_flag = 1;
      pthread_mutex_unlock(&self->lock);
      break; // Exit the loop to terminate the thread.
    }

    // Unlock the AEB system after processing input.
    pthread_mutex_unlock(&self->lock);

    // Sleep for 50 milliseconds to reduce CPU usage and avoid busy-waiting.
    usleep(50000);
  }

  // Return NULL as required by the pthread signature.
  return NULL;
}
