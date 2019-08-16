/*
 * celula.cpp
 *
 * Created: 12/12/2018 9:02:23 AM
 *  Author: rfr_9
 */ 

#include "celula.h"

HX711 balanca(A0, A1);

int balanca_check()
{
	static float peso_atual = 0;
	static float peso_anterior_1=0;
	static float peso_anterior_2=0;
	static float peso_anterior_3=0;
	static int cont = 0;
	
// 	Serial.print("Peso: ");                                    // imprime no monitor serial
// 	Serial.print(peso_atual, 2);                      // imprime peso da balança com 3 casas decimais
// 	Serial.print(" kg");
// 	Serial.println();
// 	Serial.print("      Fator de Calibração: ");               // imprime no monitor serial
// 	Serial.println(calibration_factor);                        // imprime fator de calibração
	
	switch (cont)
	{
		case 0:
		peso_anterior_1 = balanca.get_units(),
		cont++;
		break;
		
		case 1:
		peso_anterior_2 = balanca.get_units();
		cont++;
		break;
		
		case 2:
		peso_anterior_3 = balanca.get_units();
		cont =0;
		break;
	}
	
	if(peso_anterior_1<peso_anterior_2+0.01 && peso_anterior_1>peso_anterior_2-0.01 && peso_anterior_1<peso_anterior_3+0.01 && peso_anterior_1>peso_anterior_3-0.01 && peso_anterior_2<peso_anterior_3+0.01 && peso_anterior_2>peso_anterior_3-0.01)
	{
		peso_atual = (peso_anterior_3 + peso_anterior_2 + peso_anterior_1)/3;
	}

	if (Serial.available())                                    // reconhece letra para ajuste do fator de calibração
	{
		char temp = Serial.read();
		if (temp == 't') zeraBalanca ();          // t = zera a Balança
	}
	
	return int(peso_atual*100)*10;
}
void calibra_balanca(void)
{
	float calibration_factor = 20600;     // fator de calibração para teste inicial
	balanca.set_scale(calibration_factor);                     // ajusta fator de calibração
	
}
void zeraBalanca ( )
{
	//Serial.println();                                               // salta uma linha
	balanca.tare();                                                 // zera a Balança
	//Serial.println("Balanca Zerada ");
}
void balanca_update_equip(equip** vet_equips, int qty_equips, char* user_atual, int peso_atual)
{
	
	static int peso_antigo = 0;
	int equip_existe =0;
	if (peso_antigo != peso_atual && peso_antigo != peso_atual+10  && peso_antigo != peso_atual-10 )
	{
		int peso_equip = abs(peso_atual - peso_antigo);
		for (int j; j<qty_equips; j++)
		{
			if (equip_get_weight(vet_equips[j]) == peso_equip || equip_get_weight(vet_equips[j]) == peso_equip+10 || equip_get_weight(vet_equips[j]) == peso_equip-10 || equip_get_weight(vet_equips[j]) == peso_equip+20 || equip_get_weight(vet_equips[j]) == peso_equip-20)
			{
				if (peso_antigo > peso_atual)
				{
					equip_existe =1;
					equip_set_local(vet_equips[j], user_atual);
					Serial.print(user_atual);
					Serial.print(" retirou: ");
					Serial.print(equip_get_name(vet_equips[j]));
					Serial.print(" da SafeBox");
					Serial.println();
				}
				if (peso_antigo < peso_atual)
				{
					equip_existe=1;
					equip_set_local(vet_equips[j], "SafeBox");
					Serial.print(user_atual);
					Serial.print(" Adicionou: ");
					Serial.print(equip_get_name(vet_equips[j]));
					Serial.print(" a SafeBox");
					Serial.println();
				}
				break;
			}		
		}
		if (equip_existe==0)
		{	
			if(peso_antigo > peso_atual)
			{
				Serial.print("Item inexistente retirado, confirme se o equipamento esta completo. ");
				Serial.println();	
			}
			if(peso_antigo<peso_atual)
			{
				Serial.print("Item inexistente inserido, confirme se o equipamento esta completo. ");
				Serial.println();
			}
			
		}
	}	
	peso_antigo = peso_atual;
}