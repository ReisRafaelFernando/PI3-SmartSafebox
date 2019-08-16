/*
 * telas.h
 *
 * Created: 10/30/2018 6:11:12 PM
 *  Author: rfr_9
 */ 
#ifndef TELAS_H_
#define TELAS_H_

#include <Arduino.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "U8glib.h"

void u8g_prepare(U8GLIB_ST7920_128X64_1X u8g);
void u8g_Tela1(U8GLIB_ST7920_128X64_1X u8g, char keypad_input);  //Tela 1 - Arduino e Cia - Retangulos
void u8g_Tela2(U8GLIB_ST7920_128X64_1X u8g); //Tela 2 - Moldura e relógio
void u8g_Tela3(U8GLIB_ST7920_128X64_1X u8g); //Tela 3 - Caracteres Ascii - Pag. 1
void u8g_Tela4(U8GLIB_ST7920_128X64_1X u8g, int password[6]);  //Tela 3 - Caracteres Ascii - Pag. 2
void draw(U8GLIB_ST7920_128X64_1X u8g, int tela, int password[6], char keypad_input); //Rotina Desenho

void delay_tela(int tela);

void loop_telas_teste(U8GLIB_ST7920_128X64_1X u8g);
void print_debug_variable(U8GLIB_ST7920_128X64_1X u8g, uint8_t variable);
void print_img_test(U8GLIB_ST7920_128X64_1X u8g, int password[6]);
#endif /* TELAS_H_ */