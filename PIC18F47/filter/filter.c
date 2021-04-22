
#include "filter.h"
#include <PIC18F47k42.h>
 //Stopband

float gain_1 = 0.952;//0.2
float num_1[3] = {1,1,1};
float den_1[3] = {1,0.875,0.9063};
float w_1[3] = {0,0,0};

float gain_2 = 0.9; //0.3
float num_2[3] = { 1,1,1};
float den_2[3] = {1,1.0313,0.9063};
float w_2[3] = {0,0,0};

 
 //Low pass
/*
float gain_1 = 0.1539;
float num_1[3] = {1,2,1};
float den_1[3] = {1,-0.4531,0.4688};
float w_1[3] = {0,0,0};

float gain_2 = 0.1836;
float num_2[3] = { 1,2,1};
float den_2[3] = {1,-0.3281,0.0625};
float w_2[3] = {0,0,0};
*/

//High Pass
/*
float gain_1 = 0.05;
float num_1[3] = {1,-2,1};
float den_1[3] = {1,0,0.4531};
float w_1[3] = {0,0,0};

float gain_2 = 3;
float num_2[3] = { 1,-2,1};
float den_2[3] = {1,0,0.0469};
float w_2[3] = {0,0,0};
*/
/*
#define BL 12
int B[BL] = {
      0,    0,    4,   11,   21,   28,   28,   21,   11,    4,    0,    0
};
*/
/*
#define BL 8
int B[BL] = {
    2,12,42,71,71,42,12,2
};
 */
/*
#define BL  18
int B[BL] = {
      0,    0,    1,    1,    0,    0,    0,   24,   48,   48,   24,    0,
      0,    0,    1,    1,    0,    0
};*/

#define BL  31
int B[BL] = {
     0,    0,    0,    0,    1,    0,    0,    0,    2,    4,    0,    0,
      0,   11,   38,   52,   38,   11,    0,    0,    0,    4,    2,    0,
      0,    0,    1,    0,    0,    0,    0
};

int x[BL];
int k = 0;

long filter_FIR(int in)
{
  int i = 0;
  x[k] = in;
  int inx = k;
  int *apuntadorcoef = &B[0];
  int *apuntadorarrc = &x[inx];
  // mucho cuidado con el tamaño de los apuntadores DEBE COINCIDIR CON EL DEL ARREGLO o no va a funcionar.
  
  long y = 0;
  for (i = 0; i < BL; ++i) {
    y += (long)(*apuntadorarrc) * (long)(*apuntadorcoef);// verifique que para su filtro no exista overflow.
    apuntadorcoef++;
    if (inx != 0) {
      apuntadorarrc--;
      inx--;
    }
    else {
      apuntadorarrc = &x[BL - 1];
      inx = BL - 1;
    }
  }
  k++;
  k = (k >= BL) ? 0 : k;
  return y>>8 ; //si no es multiplo de 2^n divida por el factor de normalización adecuado a su filtro.
}

void inicializar_iir(float*num, float*den, float*w, coef_iir_2_ord* ir)
{
  for (int i = 0; i < 5; i++) {
    ir->num[i] = num[i];
    ir->den[i] = den[i];
    ir->w[i] = w[i];
  }
}

float filtrarIIR(float in) {
  float y,y1,yout;
  
  /*w[0] = (den[0] * in * gain) - (den[1] * w[1]) - (den[2] * w[2]); 
  y = ((num[0] * w[0]) + (num[1] * w[1]) + (num[2] * w[2]));
  w[2] = w[1];
  w[1] = w[0];*/

  w_1[0] = (den_1[0] * (in * gain_1)) - (den_1[1] * w_1[1]) - (den_1[2] * w_1[2]);  
  y1 = ((num_1[0] * w_1[0]) + (num_1[1] * w_1[1]) + (num_1[2] * w_1[2]));
  w_1[2] = w_1[1];
  w_1[1] = w_1[0];
  
  //y1 = y1 + 500;
  w_2[0] = (den_2[0] * (y1* gain_2)) - (den_2[1] * w_2[1]) - (den_2[2] * w_2[2]); 
  yout = ((num_2[0] * w_2[0]) + (num_2[1] * w_2[1]) + (num_2[2] * w_2[2]));
  w_2[2] = w_2[1];
  w_2[1] = w_2[0];
  
  return yout;
}

