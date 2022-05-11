#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define picloop(m,n) for(i = 0; i < m; i++ )for(j = 0; j < n; j++)
#define loop(m) for(i = 0; i < m; i++ )
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void main(){
    int i,j;

    // open files
    FILE *ifile = fopen(INPUT_FILE,"r");
    FILE *ofile = fopen(OUTPUT_FILE,"w+");
    int size[2];
    int var;

    // read image sizes
    fscanf(ifile, "%d ",&size[0]);
    fscanf(ifile, "%d\n",&size[1]);

    int * hist = (int *)calloc(256,sizeof(int));
    
    // scan through image
    picloop(size[0],size[1]){
        if ( j == size[1] - 1)
            fscanf(ifile,"%d\n",&var);
        else
            fscanf(ifile,"%d ",&var);
        // fequency calculation
        *(hist + var) = *(hist + var) + 1;
    }

    // processing histogram data for probability and value
    double previous = 0;
    double present = 0;
    loop(256){
        present = ( *(hist + i) / (1.0 * size[0] * size[1]) );
        *(hist + i) = (int)round((present + previous) * 255);
        previous = present + previous;
    }

    // resetting pointer to start
    fseek(ifile,0,SEEK_SET);
    fscanf(ifile, "%d ",&size[0]);
    fscanf(ifile, "%d\n",&size[1]);
    int c = 0;

    // scan through image
    picloop(size[0],size[1]){
        if ( j == size[1] - 1)
            fscanf(ifile,"%d\n",&var);
        else
            fscanf(ifile,"%d ",&var);
        // assigning value
        var = *(hist + var);
        // writing the value to output data
        if ( j == size[1] - 1)
            fprintf(ofile,"%d\n",var);
        else
            fprintf(ofile,"%d ",var);
    }
    
    // close files
    fclose(ifile);
    fclose(ofile);
}