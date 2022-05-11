#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

double membership_formula(double *intensity_value,int n,int *img,int colsize,int i,int j){
    return abs((*(intensity_value + n)) - (*(img + colsize*i + j)));
}

void main(){
    int i,j,n,neighbour,flag,k;
    double tolerance,distance,d;
    // open files
    FILE *ifile = fopen(INPUT_FILE,"r");
    FILE *ofile = fopen(OUTPUT_FILE,"w+");
    int size[2];
    int var;

    // read image sizes
    fscanf(ifile, "%d ",&size[0]);
    fscanf(ifile, "%d\n",&size[1]);

    int * img = (int *)malloc(size[0]*size[1]*sizeof(int));

    for( i = 0; i < size[0]; i++ ){
        for( j = 0; j < size[1]; j++ ){
            if ( j == size[1] - 1)
                fscanf(ifile,"%d\n",&var);
            else
                fscanf(ifile,"%d ",&var);
            *(img + size[1]*i + j) = var;
        }
    }

    printf("The k or c value:");
    scanf("%d",&k);
    printf("Enter tolerance value:");
    scanf("%f",&tolerance);

    double *intensity_value = (double *)malloc(k*sizeof(double));
    srand(time(0));
    for( i = 0; i < k; i++ ){
        *(intensity_value + i) = (rand()% 256);
    }
    double *temporary_intensity = (double *)calloc(k,sizeof(double));
    int *count = (int *)calloc(k,sizeof(int));

    int * mask_matrix = (int *)malloc(size[0]*size[1]*sizeof(int));
    int c = 0;
    do{
        for( i = 0; i < size[0]; i++ ){
            for( j = 0; j < size[1]; j++ ){
                distance = 9999;
                neighbour = -1;
                for( n = 0; n < k; n++ ){
                    d = membership_formula(intensity_value,n,img,size[1],i,j);
                    if (d < distance){
                        distance = d;
                        neighbour = n;
                    }
                }
                *(mask_matrix + size[1] * i + j) = neighbour;
                *(temporary_intensity + neighbour) += *(img + size[1]*i + j);
                *(count + neighbour) += 1;
            }
        }
        // printf("Checkpoint 1");
        flag = 1;
        for( i = 0; i < k; i++ ){
            *(temporary_intensity + i) /= *(count + i);
            // printf("Checkpoint 3");
            if ( abs((*(temporary_intensity + i) - (*(intensity_value + i)))) > tolerance ){
                flag = 0;
            }
            // printf("Checkpoint 4");
        }
        // printf("Checkpoint 2");
        double *temp = intensity_value;
        intensity_value = temporary_intensity;
        free(count);
        free(temp);
        temporary_intensity = (double *)calloc(k,sizeof(double));
        count = (int *)calloc(k,sizeof(int));
        c += 1;
    }while(flag != 1);

    printf("Number of iterations: %d",c);

    for( i = 0; i < size[0]; i++){
        for( j = 0; j < size[1]; j++ ){
            var = (int)*(intensity_value + *(mask_matrix + size[1]*i + j));
            if ( j == size[1] - 1)
                fprintf(ofile,"%d\n",var);
            else
                fprintf(ofile,"%d ",var);
        }
    }
}