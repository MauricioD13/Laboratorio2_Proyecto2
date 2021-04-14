
#include "filter.h"
#include <PIC18F47k42.h>
#define BL 8
const char B[BL] = {
    2,12,42,71,71,42,12,2
};

int x[BL];
int k = 0;

long filter_FIR(int in)
{
  int i = 0;
  x[k] = in;
  int inx = k;
  char *apuntadorcoef = &B[0];
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
float filtrarIIR(float in, coef_iir_2_ord* ir) {
    
  float y;
  /*Ecuacion implementada:
  w0=a0*x-a1*w1-a2*w2 donde x es la entrada  a denota a los denominadores notese que a0 es siempre 1 por lo que da lo mismo quitarlo
  y =b0*w0+b1*w1+b2*w2
  w2=w1
  w1=w0
  */
  ir->w[0] = (ir->den[0] * in) - (ir->den[1] * ir->w[1]) - (ir->den[2] * ir->w[2]) - (ir->den[3] * ir->w[3]) - (ir->den[4] * ir->w[4]); // OJO QUE EL MENOS YA ESTA EN LA ECUACION ver en  la ayuda de filterDesign en "show filter structure" si esta es o no la ecuación que implementan en ese software
  y = ((ir->num[0] * ir->w[0]) + (ir->num[1] * ir->w[1]) + (ir->num[2] * ir->w[2])+ (ir->num[3] * ir->w[3])+ (ir->num[4] * ir->w[4]));
  ir->w[4] = ir->w[3];
  ir->w[3] = ir ->w[2];
  ir->w[2] = ir->w[1];//debe ser primero este
  ir->w[1] = ir->w[0];// y luego este para no sobreescribir
  return y;
}


/*long int filtrarFIR2(int in)
{
  long out;
  int i = 0;
  x[k] = in;
  int inx = k;
  float y = 0;
  for (i = 0; i < BL; ++i) {
    y += (float)x[inx] * (float)B[i];// verifique que para su filtro no exista overflow.
    inx = inx != 0 ? inx - 1 : BL - 1;
  }
  k++;
  k = (k >= BL) ? 0 : k;
  out = (long)y;
  return out >> 8; //si no es multiplo de 2^n divida por el factor de normalización adecuado a su filtro.

}*/
