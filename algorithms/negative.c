#include <stdio.h>
#include <stdlib.h>

#define picloop(m, n)       \
    for (i = 0; i < m; i++) \
        for (j = 0; j < n; j++)
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void main()
{

    printf("\n********************************Negative Transformation********************************\n");

    // declaring variables
    int i, j;

    // open files
    FILE *ifile = fopen(INPUT_FILE, "r");
    FILE *ofile = fopen(OUTPUT_FILE, "w+");
    int size[2];
    int var;
    // take size of the image
    fscanf(ifile, "%d ", &size[0]);
    fscanf(ifile, "%d\n", &size[1]);

    // scan through image data
    fprintf(ofile, "%d %d\n", size[0], size[1]);
    picloop(size[0], size[1])
    {
        if (j == size[1] - 1)
            fscanf(ifile, "%d\n", &var);
        else
            fscanf(ifile, "%d ", &var);
        // process data
        var = 255 - var;
        // write processed data
        if (j == size[1] - 1)
            fprintf(ofile, "%d\n", var);
        else
            fprintf(ofile, "%d ", var);
    }
    // close files
    fclose(ifile);
    fclose(ofile);
}