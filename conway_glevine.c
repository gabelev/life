/*
Author: Gabe Levine
NYUID: gl396
Date: April 23, 2017

Description: The Game of life, now in C.
*/

#include <stdio.h>
#include <stdlib.h>
#define ROW 10
#define COL 10

int** create_array();
int find_num_neighbors(int **world, int x_coordinate, int y_coordinate);
int** generate_next_iteration(int **world);
void print_world(int world[ROW][COL]);
void print_pointer(int **world);
int** swap_arrays(int **temp, int **original);
void write_output(int **world, FILE *output_file);

int main(int argc, char* argv[]) {
    char *input_file_name = argv[2];
    char *output_file_name;
    asprintf(&output_file_name,"%s%s", input_file_name, ".out");
    FILE *output_file = fopen(output_file_name, "w");
    FILE *inputfile = fopen(argv[2], "r"); 
    int generation, i, j;
    int **new, **world;

    generation = atoi(argv[1]);

    if (inputfile == NULL) {
        printf("No file to read");
        return(-1);
    }
    world = create_array();
    while(!feof(inputfile)) {
        for (i = 0; i < ROW; i++) {
            for (j = 0; j < COL; j++)
            fscanf(inputfile, "%1d", &world[i][j]);
        }
    } 
    // it seems to speed up the code, when we create an array here.
    new = create_array();
    new = generate_next_iteration(world);
    // create the generations
    while (generation > 0) {
        new = generate_next_iteration(new);
        --generation;
    }

    write_output(world, output_file);
    fclose(inputfile);
    fclose(output_file);
    free(new);
    return 0;
}

/* print for debugging */
void print_world(int world[ROW][COL]) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (j == COL - 1) {
                printf("%d\n", world[i][j]);
                
            } else {
                printf("%d ", world[i][j]);
            }
        }
    }
}

void print_pointer(int **world) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (j == COL - 1) {
                printf("%d\n", world[i][j]);
                
            } else {
                printf("%d ", world[i][j]);
            }
        }
    }
}

/* output our file */
void write_output(int **world, FILE *output_file) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (j == COL - 1) {
                fprintf(output_file, "%d \n", world[i][j]);   
            } else {
                fprintf(output_file, "%d ", world[i][j]);
            }
        }
    }
}

/* iterates through all the array locations around a given
 * point incrementing the num_neighbors if there is a 1, ignoring
 * coordinates that are out of bounds and the initial point itself.
 */
int find_num_neighbors_p(int **world, int y_coordinate, int x_coordinate) {
    int i, j;
    int num_neighbors = 0;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if((y_coordinate + i >=0) &&
               (x_coordinate + j >= 0) &&
               (y_coordinate + i < COL) &&
               (x_coordinate + j < ROW)) {
                    if (world[y_coordinate + i][x_coordinate + j] == 1) {
                        if (i == 0 && j == 0) {
                            continue;
                        } else {
                            num_neighbors++;
                        }
                    }
            }
        }
    }
    return num_neighbors;
}

/* allocates memory for our world array and returns a pointer to it. */
int** create_array(){
    int* cells = calloc(ROW * COL, sizeof(int));
    int** multi_array = malloc(ROW * sizeof(int*));
    int i, k;
    for (i=0; i < ROW; ++i) {
        multi_array[i] = cells + i * COL;
    }
    return multi_array;
}

/* let's swap arrays. */
int** swap_arrays(int **temp, int **original) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            original[i][j] = temp[i][j];
        }
    }
    return original;
}

/* Generates the next world based on conway rules.
 * param: pointer to a 2D array.
 * return: pointer to a 2D array solution.
 */
int** generate_next_iteration(int **world) {
    int** temp_world;
    int i, k, num_neighbors;
    temp_world = create_array();
    for (i = 0; i < ROW; i++) {
        for (k = 0; k < COL; k++) {
            num_neighbors = find_num_neighbors_p(world, i, k); 
            if ((num_neighbors == 2) || (num_neighbors == 3)) {
                if (world[i][k] == 1) {
                    temp_world[i][k] = 1;
                    continue;
                }
                if ((world[i][k] == 0) && (num_neighbors == 3)) {
                    temp_world[i][k] = 1;
                    continue;
                } else {
                    temp_world[i][k] = 0;
                }
            } else {
                temp_world[i][k] = 0;
            }
        }
    }
    world = swap_arrays(temp_world, world);
    free(temp_world);
    return world;
}

