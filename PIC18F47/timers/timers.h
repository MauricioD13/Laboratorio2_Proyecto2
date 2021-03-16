/* 
 * File:   timers.h
 * Author: guasonito
 *
 * Created on 15 de marzo de 2021, 12:04 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

typedef struct STATES;
typedef struct COUNTERS;

void config_T2(void);

void change_parameters(COUNTERS *counters, int *parameter); // count_to = (micro_seconds/1000) * 2


#endif	/* TIMERS_H */

