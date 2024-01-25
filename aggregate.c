#include <stdio.h>
#include <string.h>
#include "aggregate.h"
#include <ctype.h>

static double count(double* arr, int size){ //count function (imn not sure why the assignmnent wanted to include the array[] as a parameter since we dont really need it, we just return the size parameter)

   return size;

}
static double min(double* arr, int size) { //returns smallest value of array
 double min = arr[0];
 for(int i=1;i<size;i++){
    if(arr[i]<min){
        min = arr[i];
    }
 }
    return min;
}

static double max(double* arr, int size){ //returns biggest value of array
double max = arr[0];
for(int i=1;i<size;i++){
if(arr[i]>max){
    max = arr[i];
}
}
return max;
}

static double sum(double* arr, int size){//returns sum of array
    double total=0;
   for(int i =0; i<size;i++){
    total= total +arr[i];
   }
   return total;
}

static double avg(double* arr, int size){//returns avg of array
   double total=0;
   for(int i =0; i<size;i++){
    total= total +arr[i];
   }
   return (total/size);
}
static double pavg(double* arr, int size){ //returns pavg of array
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
