/*
 * gestao.h
 *
 * Created: 11/11/2018 6:49:36 PM
 *  Author: rfr_9
 */ 


#ifndef GESTAO_H_
#define GESTAO_H_

typedef struct equip equip_t;

equip_t* equip_new(int equip_id, char* equip_name, char* equip_description, int equip_weight, char* equip_local);
equip_t* preset_equips(int equip);
int equip_get_weight(equip_t* equip);
void equip_set_local(equip_t* equip, char *nome);
char* equip_get_local(equip_t* equip);
char* equip_get_name(equip_t* equip);

#endif /* GESTAO_H_ */