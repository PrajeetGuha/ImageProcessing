#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MEMBERSHIP_FILE "membership.txt"

int main()
{

    // file opening and reading ad storing image in an array
    FILE *ifile = fopen(INPUT_FILE, "r");
    FILE *ofile = fopen(OUTPUT_FILE, "w+");
    FILE *mfile = fopen(MEMBERSHIP_FILE,"w+");
    int size[2], var, i, j, k;
    fscanf(ifile, "%d ", &size[0]);
    fscanf(ifile, "%d\n", &size[1]);

    int *img = (int *)malloc(size[0] * size[1] * sizeof(int));

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


    int m;
    printf("Enter value of m:");
    scanf("%d", &m);

    int c;
    printf("Enter value of c:");
    scanf("%d", &c);

    // starting intensity value of clusters
    double *cluster_centers = (double *)malloc(c * sizeof(double));
    srand(time(0));
    for (i = 0; i < c; i++)
    {
        *(cluster_centers + i) = (double)(rand() % 256);
    }

    // initializing membership values with 1
    int N = size[0] * size[1];
    double *u = (double *)malloc(c * N * sizeof(double));
    for (i = 0; i < c; i++)
    {
        for (j = 0; j < N; j++)
        {
            *(u + i * N + j) = 1;
        }
    }

    // calculate initial cost
    double temp_cost = 0;
    for (i = 0; i < size[0]; i++)
    {
        for (j = 0; j < size[1]; j++)
        {
            for (k = 0; k < c; k++)
            {
                temp_cost = temp_cost + pow((*(u + k * N + (i * size[1] + j))), m) * pow((*(img + size[1] * i + j)) - (*(cluster_centers + k)), 2);
            }
        }
    }

    double tolerance;
    printf("Enter tolerance:");
    scanf("%lf", &tolerance);

    double cost, val, denom, numer, tempval;

    // iterative finding of membership clusters
    do
    {
        
        cost = temp_cost;
        temp_cost = 0;
        // calculate memberships
        for (i = 0; i < c; i++)
        {
            for (j = 0; j < N; j++)
            {
                val = 0;
                for (k = 0; k < c; k++)
                {
                    if ((*(img + j)) - (*(cluster_centers + k)) != 0){
                        tempval = (fabs((*(img + j)) - (*(cluster_centers + i))) / fabs((*(img + j)) - (*(cluster_centers + k))));
                    }
                    else{
                        tempval = 0;
                    }
                    val = val +  pow(tempval, (2.0 / (m - 1)));
                }
                *(u + N * i + j) = val;
            }
        }

        // calculating new cluster centers
        for (i = 0; i < c; i++)
        {
            numer = 0;
            denom = 0;
            for (j = 0; j < N; j++)
            {
                numer = numer + pow((*(u + N * i + j)), m) * (*(img + j));
                denom = denom + pow((*(u + N * i + j)), m);
            }
            *(cluster_centers + i) = round(numer / denom);
        }

        // calculating cost with new memberships
        for (i = 0; i < size[0]; i++)
        {
            for (j = 0; j < size[1]; j++)
            {
                for (k = 0; k < c; k++)
                {
                    temp_cost = temp_cost + pow((*(u + k * N + (i * j))), m) * pow((*(img + size[1] * i + j)) - (*(cluster_centers + k)), 2);
                }
            }
        }
        break;

    } while (fabs(temp_cost - cost) > tolerance);

    // writing to file the memberships
    for(i = 0; i < c; i++){
        for(j = 0; j < N; j++){
            var = *(u + i*N + j);
            if ( j == N - 1)
                fprintf(mfile,"%d\n",var);
            else
                fprintf(mfile,"%d ",var);
        }
    }

    int intensity_val = 255 / c;
    double maxi = 0;
    int choose = 0;

    // finding the cluster to which each pixel belongs and writig to files
    for( i = 0; i < size[0]; i++){
        for( j = 0; j < size[1]; j++ ){
            
            for (k = 0; k < c; k++){
                if ( (*(u + N*k + (i * size[1] + j))) > maxi ){
                    maxi = (*(u + N*k + (i * size[1] + j)));
                    choose = k;
                }
            }
            var = intensity_val * choose;
            if ( j == N - 1)
                fprintf(ofile,"%d\n",var);
            else
                fprintf(ofile,"%d ",var);
        }
    }
}