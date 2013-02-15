#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

// my machine has about a 1 MB L2 Cache size that is approximately 524288 
// integers, we'll split the buckets if they're less than 500,000
#define CACHE_SIZE 100000//500000
#define BASE 10

void reverse_sort(int* , int, int, int);

static int powers_Ten[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 
                            100000000, 1000000000};

// assuming base 10
void radix(int *arr, int size, int rev, int maxdigits)
{
    // sanity check
    if(size < 2) return;
    
    int i, j, temp, temp2;
    int *temp_vector;
    
    int *S = arr;
    int *D = malloc(size*sizeof(int));   
    
    int digits = maxdigits - rev;
    int accum[BASE][digits]; 
    memset(accum, 0, sizeof(int) * BASE * (digits));
    //get all statistical data
    for(i = 0; i < size; i++)
    {
        j = 0;
        while(j < digits)
        {
            //printf("%dth digit of %d is %d\n", j, S[i], nthdigit(S[i],j));
            accum[nthdigit(S[i],j)][j]++;
            ++j;
        }
    }

    //get offsets
    for(i = 0; i < digits; i++)
    {
        temp = accum[0][i];
        accum[0][i] = 0; 
        for(j = 1; j < BASE; ++j)
        {
            temp2 = accum[j][i];
            accum[j][i] = temp;
            temp += temp2;
        }
    }

    //sort
    for(i = 0; i < digits; i++)
    {
        for(j = 0; j < size; j++)
        {
            int tempvar = S[j];
            D[accum[nthdigit(S[j],i)][i]] = tempvar;
            accum[nthdigit(S[j],i)][i]++;
        }
        temp_vector = S;
        S = D;
        D = temp_vector;
        temp_vector = NULL;
    }
    
    //we need to make sure we've written to the given bucket
    if(S!=arr) 
    {
        memcpy(D, S, (size_t)(size * sizeof(int)));
        temp_vector = S;
        S = D;
        D = temp_vector;
        temp_vector = NULL;
        S = NULL;
    }
    free(D);
}


void cc_radix(int *arr, int size, int rev, int maxdigits)
{
    if(size < CACHE_SIZE) radix(arr, size, rev, maxdigits);
    else reverse_sort(arr, size, rev, maxdigits);
}

void reverse_sort(int *arr, int size, int rev, int maxdigits)
{
    int digit = maxdigits - rev - 1; //get relevant digit in cs notation
    if(digit < 0) return;
    int i, j, temp, temp2;
    
    int *S = arr;//malloc(size*sizeof(int));
    int *D = malloc(size*sizeof(int));   
    
    
    int stat[BASE];
    int *accum = malloc(BASE*sizeof(int));
    int *offset[BASE];
    memset(stat, 0, sizeof(int) * BASE);
    
    //get all statistical data
    for(i = 0; i < size; i++) stat[nthdigit(S[i],digit)]++;
    //get offsets
    temp = stat[0];
    accum[0] = 0;
    offset[0] = arr; 
    for(i = 1; i < BASE; ++i)
    {
        temp2 = stat[i];
        accum[i] = temp;
        offset[i] = arr + temp;
        temp += temp2;
    }
    //sort
    for(i = 0; i < size; i++)
    {
        int tempvar = S[i];
        D[accum[nthdigit(S[i],digit)]] = tempvar;
        accum[nthdigit(S[i],digit)]++;
    }
    //we need to make sure we write to the given bucket
    memcpy(S, D, (size_t)(size * sizeof(int)));

    free(accum);
    free(D);
    for(i = 0; i < BASE; i++) cc_radix(offset[i], stat[i], rev+1, maxdigits);
}



//helper function modified from http://stackoverflow.com/questions/203854
int nthdigit(int x, int n)
{
    return ((x / powers_Ten[n]) % 10); //BASE10
}

//helper function modified from http://stackoverflow.com/questions/1489830
int max_digits(int *arr, int size) //BASE10
{
    int i, max = 0;
    for(i = 0; i < size; i++) if(arr[i] > max) max = arr[i];
    i = 0;
    while (max != 0) 
    {
        max /= 10;
        i++; 
    }
    return i;
}

//helper function which iterate through the array and checks if it's sorted
int check_sorted(int *arr, int size)
{
    int i = 0;
    while(i + 1 < size && arr[i] <= arr[i+1]) i++;
    if(i + 1 < size){
     printf("broken entry is number %d\n", i);
     return 0;
    }
    return 1;
}

int main (int argc , char * argv[])
{
    if(argc != 2) return 0;
    char line[100];
    int size = atoi(argv[1]);
    int *sortarr1 = malloc(size*sizeof(int));
    int *sortarr2 = malloc(size*sizeof(int));
    int i = 0;
    clock_t start;
    clock_t finish;
    FILE *fr = fopen("numbers.txt", "r");
    
    while(fgets(line, 30, fr) != NULL && (i < size))
    {
       sortarr1[i] = atoi(line);
       i++;
    } 
    fclose(fr);
    memcpy(sortarr2, sortarr1, (size_t)(size * sizeof(int)));
    
    //printf("b4 radix arr contains:\n"); for(i = 0; i < size; ++i) printf("%d\n",sortarr1[i]);
    
    start = clock();
    radix(sortarr1, size, 0, max_digits(sortarr1, size));
    finish = clock();
    
    printf("It took %f seconds to execute standard radix.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    if(check_sorted(sortarr1, size)) printf("Check_sorted returns true for standard_radix\n");else printf("Check_sorted returns false for standard_radix\n");
    
    //printf("after radix arr contains:\n"); for(i = 0; i < size; ++i) printf("%d\n",sortarr1[i]);
    
    
    //printf("b4 ccradix arr contains:\n"); for(i = 0; i < size; ++i) printf("%d\n",sortarr2[i]);
    
    start = clock();
    cc_radix(sortarr2, size, 0, max_digits(sortarr2, size));
    finish = clock();
    
    printf("It took %f seconds to execute cc_radix.\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);
    if(check_sorted(sortarr2, size)) printf("Check_sorted returns true for cc_radix\n");else printf("Check_sorted returns false for cc_radix\n");
    
    //printf("after cc_radix arr contains:\n"); for(i = 0; i < size; ++i) printf("%d\n",sortarr2[i]);
    printf("writing to file, may take a few seconds:\n");
    
    FILE *fw = fopen("sorted.txt", "w");    
    for(i = 0; i < size; i++) fprintf(fw, "%d\n", sortarr2[i]); 
    fclose(fw);
    free(sortarr1);
    free(sortarr2);
    return 0;
}



