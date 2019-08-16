/*
 * telas.cpp
 *
 * Created: 10/30/2018 6:10:55 PM
 *  Author: rfr_9
 */ 
#include <Arduino.h>
#include "U8glib.h"
#include "telas.h"
#include "imagens/img_cadeado.h"

void u8g_prepare(U8GLIB_ST7920_128X64_1X u8g)
{
	u8g.setFont(u8g_font_6x10);
	u8g.setFontRefHeightExtendedText();
	u8g.setDefaultForegroundColor();
	u8g.setFontPosTop();
}

void u8g_Tela1(U8GLIB_ST7920_128X64_1X u8g, char keypad_input)
{
	static int index_asterisk = 0;
	static char old_keypad_input;
	
	u8g.drawBitmapP( 0, 0, 16, 64, cadeado_bitmap);
	
	u8g.setFont(u8g_font_5x8);
	u8g.drawStr( 0, 10, "Digite a Senha:");
	
	if(  keypad_input!= NULL && keypad_input > 47 && keypad_input < 58 && keypad_input != old_keypad_input)
	{
		//Serial.print(index_asterisk);
		
		index_asterisk++;
	}
	
	old_keypad_input = keypad_input;
	
	for(int i=0; i < index_asterisk; i++)
	{
		u8g.drawStr(i*5, 20, "*");
	}
	if (index_asterisk >5)
		index_asterisk = 0;
	

}

void u8g_Tela2(U8GLIB_ST7920_128X64_1X u8g) //Tela 2 - Moldura e relógio
{
	u8g.drawBitmapP( 0, 0, 16, 64, cadeado_aberto_bitmap);
	
	u8g.setFont(u8g_font_5x8);
	u8g.drawStr( 0, 10, "Digite a Senha:");
	u8g.drawStr(0, 20, "******");
	u8g.drawStr(0, 50, "ACESSO LIBERADO");
	
}

void u8g_Tela3(U8GLIB_ST7920_128X64_1X u8g) //Tela 3 - Caracteres Ascii - Pag. 1
{

}

void u8g_Tela4(U8GLIB_ST7920_128X64_1X u8g, int password[6])  //Tela 3 - Caracteres Ascii - Pag. 2
{
	u8g.setFont(u8g_font_5x8);
	
	char buf[9];
	sprintf (buf, "%d%d%d%d%d%d", password[0],password[1],password[2],password[3],password[4],password[5]);
	u8g.drawStr(0, 19, buf);
}

void draw(U8GLIB_ST7920_128X64_1X u8g, int tela, int password[6], char keypad_input) //Rotina Desenho
{
	switch(tela) //Carrega a tela correspondente
	{
		case 1:
		u8g_Tela1(u8g, keypad_input);
		break;
		case 2:
		u8g_Tela2(u8g);
		break;
		case 3:
		u8g_Tela3(u8g);
		break;
		case 4:
		u8g_Tela4(u8g, password);
		break;
	}
}

void loop_telas_teste(U8GLIB_ST7920_128X64_1X u8g)
{
	for (int display =1; display < 5; display++) //Carrega as telas de 1 a 4
	{
		u8g.firstPage();
		do
		{
			//draw(u8g, display);
		}
		while( u8g.nextPage() );
		delay(1000);  //Pausa de 1 segundos e reinicia o processo
	}
}

void print_debug_variable(U8GLIB_ST7920_128X64_1X u8g, uint8_t variable)
{
	u8g.firstPage();
	do {
		u8g.setFont(u8g_font_5x8);
		//u8g.drawStr(8, 30, "Eeee");

		char buf[9];
		sprintf (buf, "%c", variable);
		u8g.drawStr(0, 30, buf);

	} while( u8g.nextPage() );
}

void print_img_test(U8GLIB_ST7920_128X64_1X u8g, int password[6])
{
	u8g.firstPage();
	do {
		u8g.drawBitmapP( 0, 0, 16, 64, cadeado_bitmap);
		
		u8g.setFont(u8g_font_5x8);
		u8g.drawStr( 0, 10, "Digite a Senha:");
		
		char buf[9];
		sprintf (buf, "%d%d%d%d%d%d", password[0],password[1],password[2],password[3],password[4],password[5]);
		u8g.drawStr(0, 19, buf);
		
	} while( u8g.nextPage() );

}

void delay_tela(int tela)
{
	if(tela == 2)
	{
		delay(3000);
	}
	
}