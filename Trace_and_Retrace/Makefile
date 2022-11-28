output: Move_to_coordinates_and_back.o Generate_Coordinates.o Stack_implementation.o
	gcc Move_to_coordinates_and_back.o Generate_Coordinates.o Stack_implementation.o -o output

Move_to_coordinates_and_back.o: Move_to_coordinates_and_back.c
	gcc -c Move_to_coordinates_and_back.c

Generate_Coordinates.o: Generate_Coordinates.c
	gcc -c Generate_Coordinates.c

Stack_implementation.o: Stack_implementation.c
	gcc -c Stack_implementation.c
clean:
	rm *.o output