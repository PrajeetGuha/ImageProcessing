#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define picloop(m, n)       \
    for (i = 0; i < m; i++) \
        for (j = 0; j < n; j++)
#define loop(m) for (i = 0; i < m; i++)
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void main()
{

    printf("\n********************************Logarithmic Transformation********************************\n");

    // declaring variables
    int i, j;

    // open file
    FILE *ifile = fopen(INPUT_FILE, "r");
    FILE *ofile = fopen(OUTPUT_FILE, "w+");
    int size[2];
    int var;

    // take size of the image
    fscanf(ifile, "%d ", &size[0]);
    fscanf(ifile, "%d\n", &size[1]);

    int max = 0;
    int min = 255;

    // scan through image
    picloop(size[0], size[1])
    {
        if (j == size[1] - 1)
            fscanf(ifile, "%d\n", &var);
        else
            fscanf(ifile, "%d ", &var);
        // find maximum and minimum value
        if (var > max)
            max = var;
        if (var < min)
            min = var;
    }

    // reset to start
    fseek(ifile, 0, SEEK_SET);
    fscanf(ifile, "%d ", &size[0]);
    fscanf(ifile, "%d\n", &size[1]);
    int c = 0;
    fprintf(ofile, "%d %d\n", size[0], size[1]);
    picloop(size[0], size[1])
    {
        if (j == size[1] - 1)
            fscanf(ifile, "%d\n", &var);
        else
            fscanf(ifile, "%d ", &var);
        // process data
        var = (log(var - min + 1) * 255) / (log(max - min + 1));
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