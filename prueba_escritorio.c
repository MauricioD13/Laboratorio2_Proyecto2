#include <stdio.h>
#define BL 8
char B[BL] = {
    2,12,42,71,71,42,12,2
};

int coseno[100] = {
  1023, 1021, 1015, 1005, 991,  973,  951,  926,    896,    864,    828,    788,    746,    700,    652,  601,  548,  493,  436,  377,
  316,  254,  192,  128,  64,   0,    -64,  -128,   -192,   -254,   -316,   -377,   -436,   -493,   -548, -601, -652, -700, -746, -788,
  -828, -864, -896, -926, -951, -973, -991, -1005,  -1015,  -1021,  -1023,  -1021,  -1015,  -1005,  -991, -973, -951, -926, -896, -864,
  -828, -788, -746, -700, -652, -601, -548, -493,   -436,   -377,   -316,   -254,   -192,   -128,   -64,  -0,   64,   128,  192,  254,
  316,  377,  436,  493,  548,  601,  652,  700,    746,    788,    828,    864,    896,    926,    951,  973,  991,  1005, 1015, 1021
};

int x[BL];
int k = 0;
long filtrarFIR2(int in)
{
  int i = 0;
  x[k] = in;
  int inx = k;
  printf("Entrada: %d\t",in);
  long y = 0;
  for (i = 0; i < BL; ++i) {
    y += (long)x[inx] * (long)B[i];// verifique que para su filtro no exista overflow.
    printf("Salida: %d, inx: %d, B[i]: %d\t",y,inx,B[i]);
    inx = inx != 0 ? inx - 1 : BL - 1;
    printf("inx actualizado: %d\n",inx);
  }
  k++;
  k = (k >= BL) ? 0 : k;
  y = y>>8;
  printf("Salida: %d\n",y);
  return y; //si no es multiplo de 2^n divida por el factor de normalización adecuado a su filtro.

}
int salida = 0;
int main(){
    for(int i = 0; i<10;i++){
        printf("RONDA %d\n",i);
        salida = filtrarFIR2(coseno[i]);
    }
    
}