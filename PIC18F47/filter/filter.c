
#include "filter.h"
#include <PIC18F47k42.h>
#define BL 8
float B[BL] = {
    0.0078125,0.046875,0.1640625,0.277344375,0.277344375,0.1640625,0.046875,0.0078125
};

volatile int x[BL];
volatile int k = 0;

int filter_FIR(int in){
    int i = 0;
    int inx = k;
    x[k] = in;
    float *pointer_coef = &B[0];
    int *pointer_array = &x[inx];
    
    float y = 0;
    
    for(i = 0; i < BL ;i++){
        y = (float) (*pointer_array) * (float)(*pointer_coef) + y;
        pointer_coef++;
        if(inx != 0){
            pointer_array--;
            inx--;
        }
        else{
            pointer_array = &x[BL - 1];
            inx = BL - 1;
        }
    }
    
    k++;
    k = ( k >= BL) ? 0:k;
    
    return (int)y;
} 
