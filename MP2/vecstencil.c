#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
int n;
void print_arr(float a[n][n], int n, FILE *fd)
{
    
    int i,j;
    #pragma novector
    for(i = 0; i < n; i++)
    {
         for(j = 0; j < n; j++)
         {
             fprintf(fd, "\t%f", a[i][j]);
         }
         fprintf(fd, "\n");
    }
}

void set_arr(float a[n][n], int n)
{
    int i,j;
    #pragma novector
    for(i = 0; i < n; i++)
    {
         for(j = 0; j < n; j++)
         {
             a[i][j] = 0;
         }
    }
    #pragma novector
    for(i = 0; i < n; i++)
    {
         a[0][i] = 1;
         a[1][i] = 1;
         a[n-1][i] = 1;
         a[i][0] = 1;
         a[i][n-1] = 1;
    }
}

int main (int argc , char * argv[])
{
    if(argc != 3) return 0;
    int i, j, M;
    n = atoi(argv[1]);
    int number_of_iterations = atoi(argv[2]);
    float p[n][n];
    float x[n][n];
    float y[n][n];
    /*float** p;  
    p = (**) malloc(arraySizeX*sizeof(double*));  
for (int i = 0; i < arraySizeX; i++)  
   theArray[i] = (double*) malloc(arraySizeY*sizeof(double)); */
    clock_t start, finish;
    
    //set arrays
    set_arr(p, n);
    memcpy(y, p, sizeof(float)*n*n);
    memcpy(x, p, sizeof(float)*n*n);
    //print_arr(x, n);
    FILE *arrays = fopen("ginsbur3_arrays", "w");   
    FILE *times = fopen("ginsbur3_times", "w");    
    
    //first loop
    start = clock();
    #pragma novector
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
    printf("It took %f seconds to execute first loop.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    fprintf(times, "It took %f seconds to execute first loop.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    print_arr(x, n, arrays);

    //reset arrays
    memcpy(y, p, sizeof(float)*n*n);
    memcpy(x, p, sizeof(float)*n*n);
   
    //second loop
    start = clock();
    for (M=0; M< number_of_iterations/2; M++)
    {
        
        y[2:n-3][1:n-2] = (x[1:n-3][1:n-2] +
                        x[2:n-3][0:n-2] +
                        x[3:n-3][1:n-2] +
                        x[2:n-3][2:n-2] +
                        x[0:n-3][1:n-2])/5.;
        
        x[2:n-3][1:n-2] = (y[1:n-3][1:n-2] +
                        y[2:n-3][0:n-2] +
                        y[3:n-3][1:n-2] +
                        y[2:n-3][2:n-2] +
                        y[0:n-3][1:n-2])/5.;
    }

    finish = clock();
    printf("It took %f seconds to execute second loop.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    fprintf(times, "It took %f seconds to execute second loop.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    print_arr(x, n, arrays);
    
    //reset arrays
    memcpy(y, p, sizeof(float)*n*n);
    memcpy(x, p, sizeof(float)*n*n);
   
    //third loop
    start = clock();
    for (M=0; M< number_of_iterations/2; M++)
    {
        
        for (i=2; i<n-1; i++)
        {
            y[i][1:n-2]=(x[i-1][1:n-2] +
                        x[i][0:n-2] +
                        x[i+1][1:n-2] +
                        x[i][2:n-2] +
                        x[i-2][1:n-2])/5.;
        }
        for (i=2; i<n-1; i++)
        {
            x[i][1:n-2]=(y[i-1][1:n-2] +
                        y[i][0:n-2] +
                        y[i+1][1:n-2] +
                        y[i][2:n-2] +
                        y[i-2][1:n-2])/5.;
        }
    }

    finish = clock();
    printf("It took %f seconds to execute third loop.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    fprintf(times, "It took %f seconds to execute third loop.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    print_arr(x, n, arrays);

    //reset arrays
    memcpy(y, p, sizeof(float)*n*n);
    memcpy(x, p, sizeof(float)*n*n);
 
    //fourth Loop
    start = clock();

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
    printf("It took %f seconds to execute fourth loop.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    fprintf(times, "It took %f seconds to execute third loop.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    print_arr(x, n, arrays);
    
    //printf("writing to file, may take a few seconds:\n");
    
    fclose(arrays);
    fclose(times);
    return 0;
}

   /*FILE *fw = fopen("sorted.txt", "w");    
    for(i = 0; i < size; i++) fprintf(fw, "%d\n", sortarr2[i]); 
    fclose(fw);
    free(sortarr1);*/

