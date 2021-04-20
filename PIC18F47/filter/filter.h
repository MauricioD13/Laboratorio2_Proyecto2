/* 
 * File:   filter.h
 * Author: guasonito
 *
 * Created on 9 de abril de 2021, 10:59 AM
 */

#ifndef FILTER_H
#define	FILTER_H

#define FIR_FILTER_LENGTH 8

typedef struct coef_iir_2_ord {// este va a ser el nombre de la estructura
  float num[5]; // ponga aquí su numerador
  float den[5]; // ponga aquí su denominador
  float w[3];
} coef_iir_2_ord;// este va a ser el nombre del typedef

long filter_FIR(int in);
long filtrarFIR2(int in);
void inicializar_iir(float*num, float*den, float*w, coef_iir_2_ord* ir);

float filtrarIIR(float in);

#endif	/* FILTER_H */

