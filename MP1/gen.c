#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int argc , char * argv[])
{
    if(argc != 2) return 0;
    int size = atoi(argv[1]);
    int i = 0;
    FILE *fw = fopen("numbers.txt", "w");
    
    for(i = 0; i < size; ++i) fprintf(fw, "%d\n", abs((int)rand())); 
    fclose(fw);
    return 0;
}

