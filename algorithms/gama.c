#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define picloop(m,n) for(i = 0; i < m; i++ )for(j = 0; j < n; j++)
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void main(){
    int i,j;

    // open files
    FILE *ifile = fopen(INPUT_FILE,"r");
    FILE *ofile = fopen(OUTPUT_FILE,"w+");
    int size[2];
    int var;
    float c, gama;
    c = 255;
    gama = 1.1;

    // read image size
    fscanf(ifile, "%d ",&size[0]);
    fscanf(ifile, "%d\n",&size[1]);

    // scan through picture
    picloop(size[0],size[1]){
        if ( j == size[1] - 1)
            fscanf(ifile,"%d\n",&var);
        else
            fscanf(ifile,"%d ",&var);
        // process data
        var = c * pow(var/c,gama);
        // write to file
        if ( var > 255 )
            var = 255;
        if ( j == size[1] - 1)
            fprintf(ofile,"%d\n",var);
        else
            fprintf(ofile,"%d ",var);
    }

    // close file
    fclose(ifile);
    fclose(ofile);
}