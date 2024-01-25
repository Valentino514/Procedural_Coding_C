#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aggregate.h"
#include "singular.h"


int main(int argc, char const *argv[])
{
 double num;
 int size = 1; 
 FILE *fp; //pointer for the sample.txt 
 FILE *fp2; //another pointer for the sample.txt file
 int precision =3;// default value of precision

 if ((fp= fopen("sample.txt", "r")) == NULL){
    printf("Error opening file\n");
    exit(1);// if it cant find the file, the program will exit 
 }
 fp2 = fopen("sample.txt", "r");
//scans the file
 while(fscanf(fp, "%lf", &num) == 1){ 

    int space = fgetc(fp);
    if(space == ' '){
        size++; //this will give the number of digits for the first row if its size isnt specified.

    }
    if(space == '\n'){
        break;
    }
 }
 // checks if the user put a custom -size 
for (int i = 1; i < argc; i++) { 
        char *sizeChange = "-size=";
        const char *arg = argv[i];
        char *substring = strstr(arg, sizeChange);
        
        if (substring != NULL) {
            
            char *value = substring + strlen(sizeChange);
            size = atoi(value);     
            break;
        }
    }
    // checks if the user put a custom -precision 
    for (int i = 1; i < argc; i++) { 
        char *sizeChange = "-prec=";
        const char *arg = argv[i];
        char *substring = strstr(arg, sizeChange);
        
        if (substring != NULL) {
            char *value = substring + strlen(sizeChange);
            precision = atoi(value);// converts string to integer
            break;
        }
    }
//reset the pointer in the file
fseek(fp, 0 ,SEEK_SET);

int digitCount = 0; 
int rows = 0;
//to count the number of rows
 while(fscanf(fp, "%lf", &num) == 1){ 
     char newLine =fgetc(fp);
    digitCount++;
    if(digitCount == size || newLine == '\n'){ 
        rows++;//if the digitcount of that row has reached the maximum size or if there's a new line, a new row is added
        digitCount=0; // resets the digit count for the next row
    }
 }
  //add another column in case of left over numbers 
 if(digitCount >0){
    rows++;
    digitCount = 0;
 }

fseek(fp, 0 ,SEEK_SET); //resets the pointer

double * rowsLength = (double*)malloc(rows*sizeof(double)); //dynamically creating an array that stores the length of each row
double** jaggedArray = (double**)malloc(rows*sizeof(double*));// dynamically creating jagged Array to allocate space for each row and store the values
for(int i=0;i<rows;i++){
    while(fscanf(fp, "%lf", &num) == 1){
        digitCount++;
         char newLine =fgetc(fp);
         if(newLine == '\n' || digitCount== size){
            break;
         }
    }
    jaggedArray[i] = (double*)malloc(digitCount*sizeof(double));// allocate the size of each row in the jagged array with the number of digits
    for(int j=0;j<digitCount;j++){ //fill up the jagged array with the value from the sample.txt file
    if(fscanf(fp2,"%lf", &num) == 1){// checks the file as long as theres data in it
    jaggedArray[i][j] = num; //allocate the numbers from the .txt file into its appropriate position in the jagged array
    }else{
        printf("error reading the text file\n");//error in case file cannot open
    }
    }
    // stores the length (how many digits) are on each row 
    rowsLength[i] = digitCount; 
    digitCount =0;
    
}
//close the pointers
fclose(fp); 
fclose(fp2);

    for (int i = 1; i < argc; i++) { 
        //aggregate functions
      if(strcasecmp(argv[i], "SUM") == 0 || strcasecmp(argv[i], "COUNT") == 0 ||strcasecmp(argv[i], "MIN") == 0 ||strcasecmp(argv[i], "MAX") == 0 ||strcasecmp(argv[i], "AVG") == 0 ||strcasecmp(argv[i], "PAVG") == 0){ 
   // the functions only perform the operation for 1 row of the jagged array, so we need to loop it for each row 
        for(int j=0;j<rows;j++){ 
            printf("%.*lf ",precision,aggregate(argv[i],jaggedArray[j],rowsLength[j])); //accessing the functions via arrays
        }
        break;
        //singular functions
    }else if(strcasecmp(argv[i], "PRINT") == 0){ //print function
 // the functions only perform the operation for 1 row of the jagged array, so we need to loop it for each row 
         for(int j=0;j<rows;j++){
            print(jaggedArray[j],rowsLength[j],precision);    
        }
 break;
    }
    else if(strcasecmp(argv[i], "SHIFT") == 0 ){//shift function
 // the functions only perform the operation for 1 row of the jagged array, so we need to loop it for each row 
        double shiftValue =atof(argv[i+1]);
        for(int j=0;j<rows;j++){
            shift(jaggedArray[j],rowsLength[j],shiftValue,precision);
        }
        break;
    }
    else{
       continue;
    }
 }

 for(int i =1;i<argc;i++){
 // the program arranges the array based on the default size or given size by the user, then it filters it based on the user's needs. 
    if(strcasecmp(argv[i], "FILTER") == 0){
        double threshold;
        int filterType;
      //if user inputs filter, it will check for the next string the user inputted to see what kind of filter he wants to do on the jagged array
        if (strcasecmp(argv[i+1], "EQ") == 0 ||strcasecmp(argv[i+1], "NEQ") == 0 ||strcasecmp(argv[i+1], "GEQ") == 0 ||strcasecmp(argv[i+1], "LEQ") == 0 ||strcasecmp(argv[i+1], "LESS") == 0 ||strcasecmp(argv[i+1], "GREATER") == 0) {
            if(argv[i+2] == NULL){ //checks if the next input is the threshold (double type value)
                printf("error, missing threshold for the function\n"); //if it isnt, error message
                exit(0);
            }
            threshold = atof(argv[i+2]);
            //checks for what kind of filter the user chose
            if(strcasecmp(argv[i+1], "EQ") == 0){ 
                filterType = 0;
            }else if(strcasecmp(argv[i+1], "NEQ") == 0){
               filterType = 1;
            }else if(strcasecmp(argv[i+1], "GEQ") == 0){
               filterType = 2;
            }else if(strcasecmp(argv[i+1], "LEQ") == 0){
               filterType = 3;
            }else if(strcasecmp(argv[i+1], "LESS") == 0){
               filterType = 4;
            }else if(strcasecmp(argv[i+1], "GREATER") == 0){
               filterType = 5;
            }
         for(int j=0;j<rows;j++){ //applies the filter for each row in the jagged array
        size_t filteredSize = filter(jaggedArray[j],rowsLength[j],filterType,threshold);
        print(jaggedArray[j], filteredSize,precision);
             }

        }else{
            //prints invalid function if function isnt given
            printf("error, invalid function\n"); 
            break;
        }
     
              
    }
 }
//de-allocate the memory of the Arrays
for(int i=0;i<rows;i++){
    free(jaggedArray[i]);
}
free(jaggedArray);
free(rowsLength);


    return 0;

}
