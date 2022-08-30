#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

double membership_formula(double *intensity_value, int n, int *img, int colsize, int i, int j)
{
    return abs((*(intensity_value + n)) - (*(img + colsize * i + j)));
}

void main()
{

    printf("\n********************************Kmeans********************************\n");

    // declaring variables
    int i, j, n, neighbour, flag, k, size[2], var;
    double tolerance, distance, d;

    // open files
    FILE *ifile = fopen(INPUT_FILE, "r");
    FILE *ofile = fopen(OUTPUT_FILE, "w+");

    // read image sizes
    fscanf(ifile, "%d ", &size[0]);
    fscanf(ifile, "%d\n", &size[1]);

    // declaring image array
    int *img = (int *)malloc(size[0] * size[1] * sizeof(int));

    // taking values
    printf("Value of k:");
    scanf("%d", &k);
    printf("Enter tolerance:");
    scanf("%lf", &tolerance);

    // scanning the image
    for (i = 0; i < size[0]; i++)
    {
        for (j = 0; j < size[1]; j++)
        {
            if (j == size[1] - 1)
                fscanf(ifile, "%d\n", &var);
            else
                fscanf(ifile, "%d ", &var);
            *(img + size[1] * i + j) = var;
        }
    }

    // intesity values initialize random
    double *intensity_value = (double *)malloc(k * sizeof(double));
    srand(time(0));
    for (i = 0; i < k; i++)
    {
        *(intensity_value + i) = (rand() % 256);
    }

    // temporary storage of new intesity values
    double *temporary_intensity = (double *)calloc(k, sizeof(double));
    int *count = (int *)calloc(k, sizeof(int));

    // membership matrix
    int *mask_matrix = (int *)malloc(size[0] * size[1] * sizeof(int));

    // iterations
    do
    {
        // closest cluster center for each pixel
        for (i = 0; i < size[0]; i++)
        {
            for (j = 0; j < size[1]; j++)
            {
                distance = 9999;
                neighbour = -1;
                for (n = 0; n < k; n++)
                {
                    d = membership_formula(intensity_value, n, img, size[1], i, j);
                    if (d < distance)
                    {
                        distance = d;
                        neighbour = n;
                    }
                }
                *(mask_matrix + size[1] * i + j) = neighbour;
                *(temporary_intensity + neighbour) += *(img + size[1] * i + j);
                *(count + neighbour) += 1;
            }
        }

        // checking convergence
        flag = 1;
        for (i = 0; i < k; i++)
        {
            *(temporary_intensity + i) /= *(count + i);
            if (abs((*(temporary_intensity + i) - (*(intensity_value + i)))) > tolerance)
            {
                flag = 0;
            }
        }

        // reassigning values of intensity
        double *temp = intensity_value;
        intensity_value = temporary_intensity;
        free(count);
        free(temp);
        temporary_intensity = (double *)calloc(k, sizeof(double));
        count = (int *)calloc(k, sizeof(int));

    } while (flag != 1);

    // write to file
    fprintf(ofile, "%d %d\n", size[0], size[1]);
    for (i = 0; i < size[0]; i++)
    {
        for (j = 0; j < size[1]; j++)
        {
            var = (int)*(intensity_value + *(mask_matrix + size[1] * i + j));
            if (j == size[1] - 1)
                fprintf(ofile, "%d\n", var);
            else
                fprintf(ofile, "%d ", var);
        }
    }
}