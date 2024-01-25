# Procderual_Coding_C
 
compiled and ran under gcc on ubuntu.

Relevant Concepts include Pointers, File I/O, Dynamic memory allocation, and Jagged-Array manipulation.

Program called mathpipe that performs simple operations on some input numbers that are read from a .txt file. The program uses a dynmaic jagged-array from the standard input to store the numbers  and applies the requested operation (avg, Pavg, sum, max etc) on each row and prints the result to the standard output. Upon processing a row, the output will be printed to the standard output. In case of any processing error, the error message is reported to the stderr followed by the immediate abnormal termination of the program. In case of no error, the program successfully terminates. Examples of processing errors are an invalid function name, a bad number format, memory allocation error, etc.

the numbers are read from a .txt file 

the aggregate operations are:

COUNT: prints the number of the elements in a given array.

MIN: applies the function min({ai}), that returns the minimum of the elements in a given array.

MAX: applies the function max({ai}), that returns the maximum of the elements in a given array.

SUM: applies the function sum({ai}), that returns the sum of the elements in a given array.

AVG: applies the function avg({ai}), that returns the average of the elements in a given array.

PAVG: applies the function pseudo_avg({i}) = (min({i}) + max({ai}))/2.

Individual operations:

Print: simply prints the number to the standard output, no change in value.

Filter: prints the number(s) if they pass the filter defined by <TYPE> nnn.nn. Supported types are EQ, NEQ, GEQ, LEQ, LESS, and GREATER. nnn is the threshold
in floating point (decimals).


Shift nnn.nn: adds nnn.nn to each element number of the array.



