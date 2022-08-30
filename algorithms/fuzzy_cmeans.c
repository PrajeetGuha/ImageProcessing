#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

int **DD_array_int(int r, int c)
{
    int **arr = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++)
        arr[i] = (int *)calloc(c, sizeof(int));
    return arr;
}

double **DD_array_double(int r, int c)
{
    double **arr = (double **)malloc(r * sizeof(double *));
    for (int i = 0; i < r; i++)
        arr[i] = (double *)calloc(c, sizeof(double));
    return arr;
}

int *D_array(int n)
{
    int *arr = (int *)calloc(n, sizeof(int));
    return arr;
}

void recalculate_membership(double **memberships, int *cluster_centers, int **image, int nr, int nc, int c, int m)
{

    double numer, denom = 0, val, maxval = 0;
    int maxval_c = 0;

    for (int i = 0; i < nr; i++)
    {
        for (int j = 0; j < nc; j++)
        {
            maxval = 0;
            for (int k1 = 0; k1 < c; k1++)
            {
                numer = image[i][j] - cluster_centers[k1];
                for (int k2 = 0; k2 < c; k2++)
                {
                    denom = denom + image[i][j] - cluster_centers[k2];
                }
                val = pow(numer / denom, 2 / (m - 1));
                memberships[k1][i * nc + j] = val;
                if (val > maxval)
                {
                    maxval_c = k1;
                    maxval = val;
                }
            }
            for (int k2 = 0; k2 < c; k2++)
            {
                if (k2 != maxval_c)
                {
                    memberships[k2][i * nc + j] = 0;
                }
            }
        }
    }
}

int *recalculate_cluster_centers(double **memberships, int **image, int c, int nr, int nc, int m)
{

    int *cluster_centers = (int *)malloc(c * sizeof(int));
    double numer, denom, tempval;

    for (int k1 = 0; k1 < c; k1++)
    {
        numer = 0;
        denom = 0;
        for (int i = 0; i < nr; i++)
        {
            for (int j = 0; j < nc; j++)
            {
                tempval = pow(memberships[k1][i * nc + j], m);
                numer = numer + tempval * image[i][j];
                denom = denom + tempval;
            }
        }
        cluster_centers[k1] = (int)(numer / denom);
    }
    return cluster_centers;
}

int main()
{
    // declaring variables
    int size[2], var, i, j, k, c, repeat, choose;
    double m, convergence, tolerance, denom, numer, cost, val, tempval, temp_cost = 0;

    // file opening
    FILE *ifile = fopen(INPUT_FILE, "r");
    FILE *ofile = fopen(OUTPUT_FILE, "w+");

    // reading the size of the image
    fscanf(ifile, "%d ", &size[0]);
    fscanf(ifile, "%d\n", &size[1]);
    int N = size[0] * size[1];

    // creating empty image array
    int **image = DD_array_int(size[0], size[1]);

    // reading the image
    for (i = 0; i < size[0]; i++)
    {
        for (j = 0; j < size[1]; j++)
        {
            if (j == size[1] - 1)
                fscanf(ifile, "%d\n", &var);
            else
                fscanf(ifile, "%d ", &var);
            image[i][j] = var;
        }
    }

    // reading value of m
    printf("Enter value of m:");
    scanf("%lf", &m);

    // reading number of clusters
    printf("Enter number of clusters:");
    scanf("%d", &c);

    // reading tolerance value
    printf("Enter tolerance:");
    scanf("%lf", &tolerance);

    // starting intensity value of clusters
    int *cluster_centers = D_array(c);
    srand(time(0));
    for (i = 0; i < c; i++)
    {
        cluster_centers[i] = (int)round(rand() % 256);
    }

    // membership matrix
    double **memberships = DD_array_double(c, N);

    // iterative finding of membership clusters
    repeat = 0;
    do
    {
        cost = temp_cost;
        temp_cost = 0;

        // calculate memberships
        recalculate_membership(memberships, cluster_centers, image, size[0], size[1], c, m);

        // calculating new cluster centers
        int *temp_cluster_centers = recalculate_cluster_centers(memberships, image, c, size[0], size[1], m);

        // repeating check
        for (k = 0; k < c; k++)
        {
            if (abs(temp_cluster_centers[k] - cluster_centers[k]) > tolerance)
            {
                int *temp;
                repeat = 1;
                temp = cluster_centers;
                cluster_centers = temp_cluster_centers;
                free(temp);
            }
        }

    } while (repeat);

    // finding the cluster to which each pixel belongs and writing to files
    fprintf(ofile, "%d %d\n", size[0], size[1]);
    for (i = 0; i < size[0]; i++)
    {
        for (j = 0; j < size[1]; j++)
        {

            for (k = 0; k < c; k++)
            {
                if (memberships[k][i * size[1] + j] > 0)
                {
                    choose = k;
                    break;
                }
            }
            var = cluster_centers[choose];
            if (j == size[1] - 1)
                fprintf(ofile, "%d\n", var);
            else
                fprintf(ofile, "%d ", var);
        }
    }

    // close files
    fclose(ifile);
    fclose(ofile);
}