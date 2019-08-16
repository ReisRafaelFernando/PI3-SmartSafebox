/*
 * menu.h
 *
 * Created: 11/5/2018 8:47:51 PM
 *  Author: rfr_9
 */ 
#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include "user.h"
#include "RFID/MFRC522.h"
#include "RFID/SPI.h"

void password_refresh(char keypad_input, int password[6]);
int password_check(user_t** vet_users, int qty_users, int keypad_input, int password[6], char *user_atual);
int RFID_check(MFRC522 mfrc522, user_t** vet_users, int qty_users, char *user_atual);

#endif /* MENU_H_ */