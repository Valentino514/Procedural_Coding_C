#include <stddef.h>
#include "singular.h"
#include <stdio.h>
#include <math.h>

void print(double a[], size_t size,int precision){
    int counter = 0;
    for(int i=0;i<size;i++){
        printf("%.*lf ",precision, a[i]);
        counter=1;
    }
    if(counter!=0){ //doesnt print a new line if the row is empty
    printf("\n");
    }
}
void shift(double a[], size_t size, double by,int precision){// shift function
    for(int i=0;i<size;i++){
        printf("%.*lf ",precision, (a[i]+by));
    }
    printf("\n");

}
// defines each filter case
size_t filter(double a[], size_t count, enum filter_type t, double threshold) { 
      size_t i, j;

    for (i = 0, j = 0; i < count; i++) {
        switch(t){
            case EQ: //equals
                if (a[i] == threshold){ 
                    a[j] = a[i]; 
                    j++; 
                }
                break;
                // the concept to adjust the values of the other filter cases is the same as the EQ case.
            case NEQ:
                if (a[i] != threshold){
                    a[j] = a[i];
                    j++;
                }
                break;
            case GEQ:
                if (a[i] >= threshold){
                    a[j] = a[i];
                    j++;
                }
                break;
            case LEQ:
                if (a[i] <= threshold){
                    a[j] = a[i];
                    j++;
                }
                break;
            case LESS:
                if (a[i] < threshold){
                    a[j] = a[i];
                    j++;
                }
                break;
            case GREATER:
                if (a[i] > threshold){
                    a[j] = a[i];
                    j++;
                }
                break;
        }
    }
// returns the new size of the jagged array, where values are updated.
    return j;
}

