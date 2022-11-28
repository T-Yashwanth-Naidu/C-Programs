#ifndef __GETCOORD__
#define __GETCOORD__

#define POINTS 5

extern int x_coordinates[POINTS];
extern int y_coordinates[POINTS];

int get_x_coordinates();
int get_y_coordinates();
void generate_coordinates();
void print_coordinates();
void goto_destination();
void back_to_home();
void to_home_at_once();

#endif