#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define picloop(m,n,k) for(i = k; i < m; i++ )for(j = k; j < n; j++)
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

// multiplication of filter and addition
int multi_add(int *ar, int l_r, int l_c, int n, double *filter, int b ){
    double k = 0;
    // pixel wise scanning
    for( int i = 0; i < n; i++ ){
        for( int j = 0; j < n; j++ ){
            // multiplication and addition
            k = k + (*(ar + b * (i + l_r) + j + l_c)) * (*(filter + n * j + i));
        }
    }
    // value of center pixel
    return (int)round(k);
}

void main(){
    int i,j,n,var;
    int a,b;
    
    double fo;
    // take filter size
    printf("Enter filter size:");
    scanf("%d",&n);
    double * filter = (double *)calloc(n*n,sizeof(double));

    // take filter values
    picloop(n,n,0){
        printf("Value at %d,%d:",i+1,j+1);
        scanf("%lf",&fo);
        *(filter + n * i + j) = fo;
    }
    // open files
    FILE *ifile = fopen(INPUT_FILE,"r");
    FILE *ofile = fopen(OUTPUT_FILE,"w+");
    int size[2];
    // take image size
    fscanf(ifile, "%d ",&size[0]);
    fscanf(ifile, "%d\n",&size[1]);
    // temporary image storage with padding
    a = 2*(n/2)+size[0];
    b = 2*(n/2)+size[1];
    int * ar = (int *)calloc(a*b,sizeof(int));

    // scan image pixels
    picloop(size[0],size[1],0){
        if ( j == size[1] - 1)
            fscanf(ifile,"%d\n",&var);
        else
            fscanf(ifile,"%d ",&var);
        // store pixel values
        *(ar + b * ( i + n/2 ) + n/2 + j) = var;
    }

    // scan through stored pixel values
    picloop(size[0]+n/2,size[1]+n/2,n/2){
        // find processed pixel value
        var = multi_add(ar,i-n/2,j-n/2,n,filter,b);
        // write processed pixel
        if ( j == size[1]+n/2 - 1)
            fprintf(ofile,"%d\n",var);
        else
            fprintf(ofile,"%d ",var);
    }
    
    // close files
    fclose(ifile);
    fclose(ofile);
}