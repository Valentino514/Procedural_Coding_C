#include <stdio.h>
#include <string.h>
#include "aggregate.h"
#include <ctype.h>

//count function
static double count(double* arr, int size){ 

   return size;

}
//returns smallest value of array
static double min(double* arr, int size) { 
 double min = arr[0];
 for(int i=1;i<size;i++){
    if(arr[i]<min){
        min = arr[i];
    }
 }
    return min;
}
//returns biggest value of array
static double max(double* arr, int size){ 
double max = arr[0];
for(int i=1;i<size;i++){
if(arr[i]>max){
    max = arr[i];
}
}
return max;
}
//returns sum of array
static double sum(double* arr, int size){
    double total=0;
   for(int i =0; i<size;i++){
    total= total +arr[i];
   }
   return total;
}
//returns avg of array
static double avg(double* arr, int size){
   double total=0;
   for(int i =0; i<size;i++){
    total= total +arr[i];
   }
   return (total/size);
}
//returns pavg of array
static double pavg(double* arr, int size){ 
    double pAVG = (arr[0]+arr[size-1])/2;
    return pAVG;
}
typedef double (*AggregateFunction)(double*, int);// using typedef for function pointers

// Array of function pointers
static AggregateFunction aggregateFunctions[] = {
    &count,&min,&max,&sum,&avg,&pavg
};

static char* funcNames[] = {
    "COUNT","MIN", "MAX", "SUM", "AVG", "PAVG"
};

double aggregate(const char* func, double* arr, int size) {
    if (func == NULL || arr == NULL || size <= 0) {
        printf("Invalid parameters\n");
        return 0;
    }

    // Convert function name to uppercase for case-insensitive comparison
    char func_upper[10];
    int i = 0;
    while (func[i]) {
        func_upper[i] = toupper(func[i]);
        i++;
    }
    func_upper[i] = '\0';

    // Find the index of the requested function (case-insensitive)
    int index = -1;
    for (i = 0; i < sizeof(funcNames) / sizeof(funcNames[0]); i++) {
        if (strcasecmp(func_upper, funcNames[i]) == 0) {
            index = i;
            break;
        }
    }

    // Call the corresponding function if found
    if (index != -1) {
        return aggregateFunctions[index](arr, size);
    } else {
        printf("Unknown function: %s\n", func);
    }

    return 0;
}
