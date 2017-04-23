#include <stdio.h>

int main(int argc, char* argv[]) {
    // FILE *fp = fopen("output.out", "w");
    FILE *inputfile = fopen(argv[2], "r");
    
    char buffer[60];

    if (inputfile == NULL) {
        printf("No file to read");
        return(-1);
    }

    while(!feof(inputfile)) {
        fgets(buffer, 60, inputfile);
        printf("%s\n", buffer);
    }
    fclose(inputfile);

    return 0;
}
