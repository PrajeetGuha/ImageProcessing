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
    printf("\n********************************Contrast Stretching********************************\n");

    // declare variable
    int i, j;

    // open files
    FILE *ifile = fopen(INPUT_FILE, "r");
    FILE *ofile = fopen(OUTPUT_FILE, "w+");
    int size[2];
    int var;

    // read the size of the image
    fscanf(ifile, "%d ", &size[0]);
    fscanf(ifile, "%d\n", &size[1]);

    int max = 0;
    int min = 255;

    //  loop through picture
    picloop(size[0], size[1])
    {
        if (j == size[1] - 1)
            fscanf(ifile, "%d\n", &var);
        else
            fscanf(ifile, "%d ", &var);
        // find the maximum and minimum
        if (var > max)
            max = var;
        if (var < min)
            min = var;
    }

    // bring file pointer to first
    fseek(ifile, 0, SEEK_SET);
    fscanf(ifile, "%d ", &size[0]);
    fscanf(ifile, "%d\n", &size[1]);
    int c = 0;

    // write to file
    fprintf(ofile, "%d %d\n", size[0], size[1]);
    // loop through picture
    picloop(size[0], size[1])
    {
        if (j == size[1] - 1)
            fscanf(ifile, "%d\n", &var);
        else
            fscanf(ifile, "%d ", &var);
        // process the picture
        var = (var - min) * (255 / (max - min));
        // write to file
        if (j == size[1] - 1)
            fprintf(ofile, "%d\n", var);
        else
            fprintf(ofile, "%d ", var);
    }

    // close file
    fclose(ifile);
    fclose(ofile);
}