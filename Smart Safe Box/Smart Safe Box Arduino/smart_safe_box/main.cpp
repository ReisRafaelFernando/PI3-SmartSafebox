/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

#include "time.h"
#include "U8glib.h"
#include "user.h"
#include "gestao.h"
#include "keypad/Keypad.h"
#include "RFID/MFRC522.h"
#include "RFID/SPI.h"
#include "telas.h"
#include "menu.h"
#include "HX711.h"
#include "celula.h"
#include "TimeLib.h"

//--------------Global Variables --------------------------------
int keypad_input;
user_t** vet_users;
equip_t** vet_equips;
int qty_users = 0;
int qty_equips =0;
int password[6] = {0};
int tela = 1;
char *user_atual = "Rafael";
int peso_atual;


//------------------ RFID Variable -----------------------------
MFRC522 mfrc522(10, 0);

//----------------- Display Variable ---------------------------
U8GLIB_ST7920_128X64_1X u8g(A3, A4, A5 ,A2); //Enable, RW, RS, RESET

//------------------ Keypad Variables ---------------------------
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char hexaKeys[ROWS][COLS] = {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 2, 9, 8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//---------------------------------------------------------------

void setup()
{
	Serial.begin(9600);   // Inicia a serial
	SPI.begin();      // Inicia  SPI bus
	mfrc522.PCD_Init();
	
	Serial.print("Fluxo de equipamentos - Smart Safe Box");
	Serial.println();
	
	
	pinMode(A2, OUTPUT); // LED DE SINALIZACAO
	pinMode(A0, INPUT);
	pinMode(A1, OUTPUT);
		
	
// 	Serial.println();                                                // salta uma linha
// 	Serial.println("HX711 - Calibracao da Balança");                 // imprime no monitor serial
// 	Serial.println("Remova o peso da balanca");
// 	Serial.println("Depois que as leituras começarem, coloque um peso conhecido sobre a Balança");
// 	Serial.println("Pressione a,s,d,f para aumentar Fator de Calibração por 10,100,1000,10000 respectivamente");
// 	Serial.println("Pressione z,x,c,v para diminuir Fator de Calibração por 10,100,1000,10000 respectivamente");
// 	Serial.println("Após leitura correta do peso, pressione t para TARA(zerar) ");
	
	zeraBalanca();
	calibra_balanca();
	zeraBalanca();
	//Serial.println("Aproxime o seu cartao do leitor...");
	//Serial.println();

	vet_users = (user_t**)malloc(sizeof(user_t*)*3);
	vet_users[0] = preset_users(1);
	vet_users[1] = preset_users(2);
	vet_users[2] = preset_users(3);
	qty_users = 3;
	
	vet_equips = (equip_t**)malloc(sizeof(equip_t*)*3);
	vet_equips[0] = preset_equips(1);
	vet_equips[1] = preset_equips(2);
	vet_equips[2] = preset_equips(3);
	qty_equips = 3;	
	
}

void loop()
{
	keypad_input = customKeypad.getKey();
	password_refresh(keypad_input, password);
	
	if(keypad_input != NULL || !mfrc522.PICC_IsNewCardPresent())
	{
		u8g.firstPage();
		do {
			draw(u8g, tela, password, keypad_input);
		} while( u8g.nextPage() );
	}
	
	delay_tela(tela);
	
	digitalWrite(A2, LOW);
	tela = password_check(vet_users, qty_users, keypad_input, password, user_atual);
	
	if (tela==1)
	{
		tela = RFID_check(mfrc522, vet_users, qty_users, user_atual);
	}
	
	peso_atual = balanca_check();
	balanca_update_equip (vet_equips, qty_equips, user_atual, peso_atual);
	
// 	Serial.print(peso_atual);
// 	Serial.print(" g ");
// 	Serial.print(   user_atual);
// 	Serial.println();
}
