#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "aeb_system.h"  // Include the AEB system definitions to access the AEBSystem structure

/**
 * @brief Thread function to process user input.
 *
 * This function runs as a separate thread and continuously monitors for user input
 * in non-blocking mode. Depending on the key pressed by the user, it updates the AEB system:
 *  - 'a': Simulates an imminent accident by modifying the sensor data.
 *  - 'n': Returns the system to normal driving mode.
 *  - 'q': Signals the simulation to exit.
 *
 * The function adheres to the pthread signature, allowing it to be used directly with
 * pthread_create().
 *
 * @param arg Pointer to an AEBSystem instance.
 * @return Always returns NULL.
 */
void *process_user_input(void *arg);

/**
 * @brief Restores the terminal settings to their original configuration.
 *
 * When the simulation ends, this function is called to revert the terminal from non-blocking,
 * non-echo mode back to its original state. This is important to ensure that the terminal
 * behaves normally after the simulation terminates.
 */
void disable_non_blocking_input(void);

#endif /* INPUT_HANDLER_H */
