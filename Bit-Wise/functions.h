/*
    This file contains declaration for all the funcitons in this repo
*/

#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H
#include "libs.h"

bool check_even_odd(int);            // Check if the number is even or odd
bool check_opposite_signs(int, int); // Check if 2 numbers have opposite signs
void swap_integers(int *, int *);    // Swap 2 integers
void set_unset_kth_bit(int *, int, int ); // Set or Unset a bit
struct set_bit_struct find_set_bits(int ); // Find set bits
void free_set_bit_struct(struct set_bit_struct *); // Free memory for number of bits set

void print_binary(void *, size_t); // Print binary of a given value
#endif