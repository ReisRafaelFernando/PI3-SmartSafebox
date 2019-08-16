/*
* menu.cpp
*
* Created: 11/5/2018 8:47:41 PM
*  Author: rfr_9
*/

#include "menu.h"

void password_refresh(char keypad_input, int password[6])
{
	static int indice = 0;
	
	if(indice>5)
	{
		indice=0;
		for (int i = 0; i<6; i++)
		{
			password[i] = 0;
		}
	}
	int new_password = keypad_input-48;
	//Serial.println(new_password);
	if( keypad_input!= NULL && keypad_input > 47 && keypad_input < 58 )
	{
		password[indice] = new_password;
		indice++;
	}
}
int password_check(user_t** vet_users, int qty_users, int keypad_input, int password[6], char *user_atual)
{
	int i;
	int j;

	if(  keypad_input!= NULL && keypad_input > 47 && keypad_input < 58)
	{
		for (j=0; j<qty_users; j++)
		{
			int* test_password = user_get_password(vet_users[j]);
			int count = 0;
			
			for (i=0;i<6; i++)
			{
				if(test_password[i]==password[i])
				{
					count++;
				}
			}
			if(count == 6)
			{
				digitalWrite(A2, HIGH);
				char *nome = user_get_name(vet_users[j]);
				strncpy(user_atual, nome,strlen((char*)nome)+1);
				Serial.print("Senha correta, porta liberada - Acesso pelo usuario: ");
				Serial.print(nome);
				Serial.println();
				return 2;
			}
			
		}
	}
	return 1;
}

int RFID_check(MFRC522 mfrc522, user_t** vet_users, int qty_users, char *user_atual)
{
	
	// Look for new cards
	if ( ! mfrc522.PICC_IsNewCardPresent())
	{
		return 1;
	}
	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial())
	{
		return 1;
	}
	//Mostra UID na serial
	Serial.print("UID da tag :");
	String conteudo= "";
	byte letra;
	for (byte i = 0; i < mfrc522.uid.size; i++)
	{
		Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
		Serial.print(mfrc522.uid.uidByte[i], HEX);
		conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
		conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
	}
	Serial.println();
	Serial.print("Mensagem : ");
	conteudo.toUpperCase();
	
	
	for (int j=0; j<qty_users; j++)
	{
		char *test_id = user_get_id(vet_users[j]);
		
		if( conteudo.substring(1) == test_id )
		{
			char *nome = user_get_name(vet_users[j]);
			strncpy(user_atual, nome,strlen((char*)nome)+1);
			
			Serial.print("RFID detectado - Porta liberada - Acesso pelo usuario: ");
			Serial.print(nome);
			digitalWrite(A2, HIGH);
			Serial.println();
			return 2;
		}
	}
	
	return 1;
}