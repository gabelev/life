/*
Author: Gabe Levine
NYUID: gl396
Date: April 23, 2017

Description: The Game of life.
*/

#include <stdio.h>
#define ROW 10
#define COL 10

void print_world(int world[ROW][COL]);

int main(int argc, char* argv[]) {
    FILE *output_file = fopen("output.out", "w");
    FILE *inputfile = fopen(argv[2], "r");
    
    
    int generation;
    char buffer[60];
    int world[ROW][COL];
    int i, j;

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

    print_world(world);
    fclose(inputfile);
    return 0;
}


/* print for debugging*/
void print_world(int world[ROW][COL]) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (j == 9) {
                printf("%d\n", world[i][j]);
                
            } else {
                printf("%d ", world[i][j]);
            }
        }
    }
}
