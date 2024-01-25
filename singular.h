#include <stddef.h>
#ifndef SINGULAR_H
#define SINGULAR_H

enum filter_type{
    EQ =0, NEQ =1, GEQ =2, LEQ = 3, LESS =4, GREATER = 5
};
void print(double a[], size_t size, int precision);
void shift(double a[], size_t size, double by, int precision);
size_t filter(double a[], size_t count, enum filter_type t, double threshold);




#endif //SINGULAR