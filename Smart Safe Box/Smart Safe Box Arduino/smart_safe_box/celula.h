/*
 * celula.h
 *
 * Created: 12/12/2018 9:02:40 AM
 *  Author: rfr_9
 */ 


#ifndef CELULA_H_
#define CELULA_H_

#include <Arduino.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include "Time.h"
#include "TimeLib.h"


#include "HX711.h"
#include "gestao.h"


int balanca_check(void);
void calibra_balanca(void);
void zeraBalanca(void);

void balanca_update_equip(equip** vet_equips, int qty_equips, char *user_atual, int peso_atual);


#endif /* CELULA_H_ */