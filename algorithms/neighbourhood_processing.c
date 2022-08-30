#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define picloop(m, n, k)    \
    for (i = k; i < m; i++) \
        for (j = k; j < n; j++)
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

// multiplication of filter and addition
int multi_add(int *ar, int l_r, int l_c, int n, double *filter, int b)
{
    double k = 0;
    // pixel wise scanning
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // multiplication and addition
            k = k + (*(ar + b * (i + l_r) + j + l_c)) * (*(filter + n * j + i));
        }
    }
    // value of center pixel
    return (int)round(k);
}

int max_val(int *ar, int l_r, int l_c, int n, int b)
{

    // finding maximum value
    int v, max = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            v = (*(ar + b * (i + l_r) + j + l_c));
            if (v > max)
                max = v;
        }
    }
    // value of center pixel
    return max;
}

int min_val(int *ar, int l_r, int l_c, int n, int b)
{

    // finding minimum value
    int v, min = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            v = (*(ar + b * (i + l_r) + j + l_c));
            if (v < min)
                min = v;
        }
    }
    // value of center pixel
    return min;
}

int median_val(int *ar, int l_r, int l_c, int n, int b)
{
    int *val = (int *)calloc(n * n, sizeof(int));
    int temp, p, k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp = (*(ar + b * (i + l_r) + j + l_c));
            p = k - 1;
            while (p > -1 && *(val + p) > temp)
            {
                *(val + p + 1) = *(val + p);
                p--;
            }
            *(val + p + 1) = temp;
            k++;
        }
    }
    return *(val + (n * n) / 2);
}

int get_val(int option, int *ar, double *filter, int n, int a, int b, int i, int j)
{
    if (option == 1)
    {
        *(ar + b * i + j) = multi_add(ar, i - n / 2, j - n / 2, n, filter, b);
        return *(ar + b * i + j);
    }
    else if (option == 2)
    {
        return max_val(ar, i - n / 2, j - n / 2, n, b);
    }
    else if (option == 3)
    {
        return min_val(ar, i - n / 2, j - n / 2, n, b);
    }
    else if (option == 4)
    {
        *(ar + b * i + j) = median_val(ar, i - n / 2, j - n / 2, n, b);
        return *(ar + b * i + j);
    }
    else if (option == 5)
    {
        return abs(multi_add(ar, i - 1, j - 1, 3, filter, b));
    }
    else if (option == 6)
    {
        double *gx = (double *)calloc(n * n, sizeof(double));
        double *gy = (double *)calloc(n * n, sizeof(double));

        *(gx + 0) = -1;
        *(gx + 3) = -2;
        *(gx + 6) = -1;
        *(gx + 2) = 1;
        *(gx + 5) = 2;
        *(gx + 8) = 1;

        *(gy + 0) = 1;
        *(gy + 1) = 2;
        *(gy + 2) = 1;
        *(gy + 6) = -1;
        *(gy + 7) = -2;
        *(gy + 8) = -1;

        return (int)round(sqrt(pow(multi_add(ar, i - 1, j - 1, 3, gx, b), 2) + pow(multi_add(ar, i - 1, j - 1, 3, gy, b), 2)));
    }
    else if (option == 7)
    {
        double *gx = (double *)calloc(n * n, sizeof(double));
        double *gy = (double *)calloc(n * n, sizeof(double));

        *(gx + 0) = 1;
        *(gx + 3) = 1;
        *(gx + 6) = 1;
        *(gx + 2) = -1;
        *(gx + 5) = -1;
        *(gx + 8) = -1;

        *(gy + 0) = -1;
        *(gy + 1) = -1;
        *(gy + 2) = -1;
        *(gy + 6) = 1;
        *(gy + 7) = 1;
        *(gy + 8) = 1;

        return (int)round(sqrt(pow(multi_add(ar, i - 1, j - 1, 3, gx, b), 2) + pow(multi_add(ar, i - 1, j - 1, 3, gy, b), 2)));
    }
    else if (option == 8)
    {
        double *gx = (double *)calloc(n * n, sizeof(double));
        double *gy = (double *)calloc(n * n, sizeof(double));

        *(gx + 4) = 1;
        *(gx + 8) = -1;

        *(gy + 5) = 1;
        *(gy + 7) = -1;

        return (int)round(sqrt(pow(multi_add(ar, i - 1, j - 1, 3, gx, b), 2) + pow(multi_add(ar, i - 1, j - 1, 3, gy, b), 2)));
    }
}

void main()
{

    printf("\n********************************Neighbourhood Processing********************************\n");

    // declaring variables
    int i, j, var, option, n = 3;
    int a, b;

    double fo;
    double *filter;

    // choose option
    printf("Choose option:\n1.Weighted Filter\n2.Max Filter\n3.Min Filter\n4.Median Filter\n5.Laplacian\n6.Sobel\n7.Prewitt\n8.Robert\nOption: ");
    scanf("%d", &option);

    if (option == 1)
    {

        // take filter size
        printf("Enter size of filter:");
        scanf("%d", &n);

        // take filter
        filter = (double *)calloc(n * n, sizeof(double));

        // take filter values
        picloop(n, n, 0)
        {
            printf("Value at %d,%d:", i + 1, j + 1);
            scanf("%lf", &fo);
            *(filter + n * i + j) = fo;
        }
    }
    else if (option == 2 || option == 3 || option == 4)
    {
        // take filter size
        printf("Enter size of filter:");
        scanf("%d", &n);
    }
    else if (option == 5)
    {
        int c;
        filter = (double *)calloc(n * n, sizeof(double));

        printf("\nFilters available:\n1.\n0 1 0\n1 -4 1\n0 1 0\n\n2.\n1 1 1\n1 -8 1\n1 1 1\nChoice: ");
        scanf("%d", &c);
        if (c == 1)
        {
            *(filter + 1) = 1;
            *(filter + 3) = 1;
            *(filter + 5) = 1;
            *(filter + 7) = 1;
            *(filter + 4) = -4;
        }
        else
        {
            *(filter + 0) = 1;
            *(filter + 1) = 1;
            *(filter + 2) = 1;
            *(filter + 3) = 1;
            *(filter + 5) = 1;
            *(filter + 6) = 1;
            *(filter + 7) = 1;
            *(filter + 8) = 1;
            *(filter + 4) = -8;
        }
    }

    // open files
    FILE *ifile = fopen(INPUT_FILE, "r");
    FILE *ofile = fopen(OUTPUT_FILE, "w+");
    int size[2];
    // take image size
    fscanf(ifile, "%d ", &size[0]);
    fscanf(ifile, "%d\n", &size[1]);
    // temporary image storage with padding
    a = 2 * (n / 2) + size[0];
    b = 2 * (n / 2) + size[1];
    int *ar = (int *)calloc(a * b, sizeof(int));

    // scan image pixels
    picloop(size[0], size[1], 0)
    {
        if (j == size[1] - 1)
            fscanf(ifile, "%d\n", &var);
        else
            fscanf(ifile, "%d ", &var);
        // store pixel values
        *(ar + b * (i + n / 2) + n / 2 + j) = var;
    }

    // scan through stored pixel values
    fprintf(ofile, "%d %d\n", size[0], size[1]);
    picloop(size[0] + n / 2, size[1] + n / 2, n / 2)
    {
        // find processed pixel value
        var = get_val(option, ar, filter, n, a, b, i, j);
        // write processed pixel
        if (j == size[1] + n / 2 - 1)
            fprintf(ofile, "%d\n", var);
        else
            fprintf(ofile, "%d ", var);
    }

    // close files
    fclose(ifile);
    fclose(ofile);
}