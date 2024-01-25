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
size_t filter(double a[], size_t count, enum filter_type t, double threshold) { //fucntion that defines each  filter case
      size_t i, j;

    for (i = 0, j = 0; i < count; i++) {
        switch(t){
            case EQ: //equals
                if (a[i] == threshold){ //if its equal
                    a[j] = a[i]; //we bring the value that matches it to the j position
                    j++; // its the new size of the jagged array. we will then print out the values until j, because its only those that have been changed.
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

    return j;// returns the new size of the jagged array, where values are updated.
}

