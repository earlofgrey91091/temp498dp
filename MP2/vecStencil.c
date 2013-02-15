#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

int main (int argc , char * argv[])
{

    //if(argc != 3) return 0;
    int i, j, M;
    int n = 5;//atoi(argv[1]);
    int number_of_iterations = 2;//atoi(argv(2));
    float x[n][n];
    float y[n][n];
    
    for(i = 0; i < n; i++)
    {
         for(j = 0; j < n; j++)
         {
             x[i][j] = 0;
         }
    }
    for(i = 0; i < n; i++)
    {
         x[i][0] = 1;
         x[i][1] = 1;
         x[i][n-1] = 1;
         x[0][i] = 1;
         x[1][i] = 1;
    }
    
    
    
    //printf("b4 radix arr contains:\n"); for(i = 0; i < size; ++i) printf("%d\n",sortarr1[i]);
    
    start = clock();
    //code from doc
    #pragma novector
    for (M=0; M< number_of_iterations/2; M++)
    {
        #pragma novector
        for (i=2; i<n-1; i++)
        {
            #pragma novector
            for (j=1; j<n-1; j++)
            {
                y[i][j]= (x[i-1][j]+x[i][j-1]+x[i+1][j]+x[i][j+1]+x[i-2][j])/5.;
            }
        }
        #pragma novector
        for (i=2; i<n-1; i++)
        {
            #pragma novector
            for (j=1; j<n-1; j++)
            {
                x[i][j]= (y[i-1][j]+y[i][j-1]+y[i+1][j]+y[i][j+1]+y[i-2][j])/5.;
            }
        }
    }

    finish = clock();
    
    start = clock();
    //code from doc
    for (M=0; M< number_of_iterations/2; M++)
    {
        for (i=2; i<n-1; i++)
        {
            for (j=1; j<n-1; j++)
            {
                y[i][j]= (x[i-1][j]+x[i][j-1]+x[i+1][j]+x[i][j+1]+x[i-2][j])/5.;
            }
        }
        for (i=2; i<n-1; i++)
        {
            for (j=1; j<n-1; j++)
            {
                x[i][j]= (y[i-1][j]+y[i][j-1]+y[i+1][j]+y[i][j+1]+y[i-2][j])/5.;
            }
        }
    }

    finish = clock();
    
    printf("writing to file, may take a few seconds:\n");
    
    FILE *fw = fopen("sorted.txt", "w");    
    for(i = 0; i < size; i++) fprintf(fw, "%d\n", sortarr2[i]); 
    fclose(fw);
    free(sortarr1);
    return 0;
}



