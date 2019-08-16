/*
* gestao.c
*
* Created: 11/11/2018 6:49:22 PM
*  Author: rfr_9
*/

#include <Arduino.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestao.h"

struct equip {
	
	int equip_id;
	char* equip_name;
	char* equip_description;
	int equip_weight;
	char* equip_local;
};

equip_t* equip_new(int equip_id, char* equip_name, char* equip_description, int equip_weight, char* equip_local)
{
	equip_t* equip = (equip_t*)malloc(sizeof(equip_t));
	
	if(equip == NULL)
	{
		//perror("ERROR: at new_equip");
		exit(EXIT_FAILURE);
	}
	//----------------------------------------------
	equip->equip_id = equip_id;
	//----------------------------------------------
	
	equip->equip_name = (char*)malloc(strlen((char*)equip_name)+1);
	
	if(equip->equip_name == NULL)
	{
		//perror("ERROR: at new_equip");
		exit(EXIT_FAILURE);
	}
	strncpy((char*)equip->equip_name, (char*)equip_name,strlen((char*)equip_name)+1);
	
	//-----------------------------------------------

	equip->equip_description = (char*)malloc(strlen((char*)equip_description)+1);
	
	if(equip->equip_description == NULL)
	{
		//perror("ERROR: at new_equip");
		exit(EXIT_FAILURE);
	}
	strncpy((char*)equip->equip_description, (char*)equip_description,strlen((char*)equip_description)+1);
	
	//--------------------------------------------------

	equip->equip_weight = equip_weight;
	
	//--------------------------------------------------

	equip->equip_local = (char*)malloc(strlen((char*)equip_local)+1);

	if(equip->equip_local == NULL)
	{
		//perror("ERROR: at new_equip");
		exit(EXIT_FAILURE);
	}
	strncpy((char*)equip->equip_local, (char*)equip_local,strlen((char*)equip_local)+1);

	return equip;

}
int equip_get_weight(equip_t* equip)
{
	return equip->equip_weight;
}
void equip_set_local(equip_t* equip, char* equip_local)
{
	free(equip->equip_local);
	
	equip->equip_local = (char*)malloc(strlen((char*)equip_local)+1);
	
	strncpy((char*)equip->equip_local, (char*)equip_local,strlen((char*)equip_local)+1);
}
char* equip_get_local(equip_t* equip)
{
	return equip->equip_local;
}
char* equip_get_name(equip_t* equip)
{
	return equip->equip_name;
}

equip_t* preset_equips(int equip)
{
	switch(equip)
	{
		case 1:
		{
			int equip_id0 = 0;
			char equip_name0[] = "Multimetro";
			char equip_description0[] = "Osciloscopio digital 1G sample";
			int equip_weight0 = 630;
			char equip_local0[] = "Safebox";
			equip_t* equip0 = equip_new(equip_id0, equip_name0, equip_description0, equip_weight0, equip_local0);
			
			return equip0;
			break;
		}
		
		case 2:
		{
			int equip_id1 = 1;
			char equip_name1[] = "Baldinho";
			char equip_description1[] = "Multimetro digital";
			int equip_weight1 = 870;
			char equip_local1[] = "Safebox";
			equip_t* equip1 = equip_new(equip_id1, equip_name1, equip_description1, equip_weight1, equip_local1);
			
			return equip1;
			break;
		}
		
		case 3:
		{
			int equip_id2 = 2;
			char equip_name2[] = "Alto_falante";
			char equip_description2[] = "Coisa car2a utilizada para teste";
			int equip_weight2 = 110;
			char equip_local2[] = "Safebox";
			equip_t* equip2 = equip_new(equip_id2, equip_name2, equip_description2, equip_weight2, equip_local2);
			
			return equip2;
			break;
		}
	}
}