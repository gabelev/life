/*
Author: Gabe Levine
NYUID: gl396
Date: April 23, 2017

Description: The Game of life.
*/

#include <stdio.h>
#include <stdlib.h>
#define ROW 10
#define COL 10

void print_world(int world[ROW][COL]);
void print_pointer(int **world);
int** generate_next_iteration(int world[ROW][COL]);
int** generate_next_iteration_p(int **world);
int find_num_neighbors(int world[ROW][COL], int x_coordinate, int y_coordinate);
int find_num_neighbors_p(int **world, int x_coordinate, int y_coordinate);
void write_output(int **world, FILE *output_file);

int main(int argc, char* argv[]) {
    FILE *output_file = fopen("output_gabe.out", "w");
    FILE *inputfile = fopen(argv[2], "r");
    
    
    int generation;
    char buffer[60];
    int world[ROW][COL];
    int i, j;
    
    generation = atoi(argv[1]);

    if (inputfile == NULL) {
        printf("No file to read");
        return(-1);
    }

    while(!feof(inputfile)) {
        for (i = 0; i < ROW; i++) {
            for (j = 0; j < COL; j++)
            fscanf(inputfile, "%1d", &world[i][j]);
        }
    } 

    // printf("start\n");
    // print_world(world);
    /*
    printf("neighbors\n");
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            printf("(%d %d) %d, ", i, j, find_num_neighbors(world, i, j));
        }
    }
    */

    
    int **new;
    int generation_counter;
    generation_counter = 0;
    // makes another array not using.
    int* values = calloc(ROW * COL, sizeof(int));
    int** pt_world = malloc(ROW * sizeof(int*));
    for (i=0; i < ROW; ++i) {
        pt_world[i] = values + i * COL;
    }

    // create the generations
    new = generate_next_iteration(world);
    while (generation_counter < generation - 1) {
        new = generate_next_iteration_p(new);
        generation_counter++;
    }
    // new = generate_next_iteration(world);
    // printf("end 1\n");
    // print_world(new);
    // print_pointer(new);

    // new = generate_next_iteration_p(new);
    // printf("end 2\n");
    // print_pointer(new);

    
    write_output(new, output_file);
    fclose(inputfile);
    fclose(output_file);
    free(new);
    free(pt_world);
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



// output our file
void write_output(int **world, FILE *output_file) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (j == COL - 1) {
                fprintf(output_file, "%d\n", world[i][j]);   
            } else {
                fprintf(output_file, "%d", world[i][j]);
            }
        }
    }
}

/* iterates through all the array locations around a given
 * point incrementing the num_neighbors if there is a 1, ignoring
 * coordinares that are out of bounds and the initial point itself.
 */
int find_num_neighbors(int world[ROW][COL], int y_coordinate, int x_coordinate) {
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
    // printf("(%d, %d: %d)", )
    return num_neighbors;
}

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
    // printf("(%d, %d: %d)", )
    return num_neighbors;
}

int** generate_next_iteration_p(int **world) {
    int* values = calloc(ROW * COL, sizeof(int));
    int** new_world = malloc(ROW * sizeof(int*));
    int i, k, num_neighbors;
    for (i=0; i < ROW; ++i) {
        new_world[i] = values + i * COL;
    }
    for (i = 0; i < ROW; i++) {
        for (k = 0; k < COL; k++) {
            num_neighbors = find_num_neighbors_p(world, i, k); // TODO check order of i,k
            if ((num_neighbors == 2) || (num_neighbors == 3)) {
                if (world[i][k] == 1) {
                    new_world[i][k] = 1;
                    continue;
                }
                if ((world[i][k] == 0) && (num_neighbors == 3)) {
                    new_world[i][k] = 1;
                    continue;
                } else {
                    new_world[i][k] = 0;
                }
            } else {
                new_world[i][k] = 0;
            }
        }
    }
    /*
    for (i = 0; i < ROW; i++) {
        for (k = 0; k < COL; k++) {
            world[i][k] = new_world[i][k];
        }
    }
    */
    // printf("DEBUG\n");
    // print_world(new_world);
    return new_world;
}
int** generate_next_iteration(int world[ROW][COL]) {
    int* values = calloc(ROW * COL, sizeof(int));
    int** new_world = malloc(ROW * sizeof(int*));
    int i, k, num_neighbors;
    for (i=0; i < ROW; ++i) {
        new_world[i] = values + i * COL;
    }
    for (i = 0; i < ROW; i++) {
        for (k = 0; k < COL; k++) {
            num_neighbors = find_num_neighbors(world, i, k); // TODO check order of i,k
            if ((num_neighbors == 2) || (num_neighbors == 3)) {
                if (world[i][k] == 1) {
                    new_world[i][k] = 1;
                    continue;
                }
                if ((world[i][k] == 0) && (num_neighbors == 3)) {
                    new_world[i][k] = 1;
                    continue;
                } else {
                    new_world[i][k] = 0;
                }
            } else {
                new_world[i][k] = 0;
            }
        }
    }
    /*
    for (i = 0; i < ROW; i++) {
        for (k = 0; k < COL; k++) {
            world[i][k] = new_world[i][k];
        }
    }
    */
    // printf("DEBUG\n");
    // print_world(new_world);
    return new_world;
}
