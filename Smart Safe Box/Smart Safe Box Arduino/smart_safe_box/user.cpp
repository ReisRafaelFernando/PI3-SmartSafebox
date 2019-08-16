/*
 * user.c
 *
 * Created: 9/12/2018 4:02:53 PM
 *  Author: Rafael Fernando Reis
 */ 
#include <Arduino.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

struct user {
	
	char user_id[12];
	char* user_name;
	int user_password[6];
	int user_permission;
};

user_t* user_new(char user_id[], char* user_name, int user_password[], int user_permission)
{
	
	user_t* user = (user_t*)malloc(sizeof(user_t));
	if(user == NULL)
	{
		//perror("ERROR: at new_user");
		exit(EXIT_FAILURE);
	}
	
	//------------------------------------------------------------------------------
	
	for(int i = 0; i<12; i++)
	{
		user->user_id[i] = user_id[i];
	}
	
	//------------------------------------------------------------------------------
	
	user->user_name = (char*)malloc(strlen((char*)user_name)+1);
	if(user->user_name == NULL)
	{
		//perror("ERROR: at new_user");
		exit(EXIT_FAILURE);
	}
	strncpy((char*)user->user_name, (char*)user_name,strlen((char*)user_name)+1);
	
	//-------------------------------------------------------------------------------
	
	
	
	if(user->user_password == NULL)
	{
		//perror("ERROR: at new_password");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i<6; i++)
	{
		user->user_password[i] = user_password[i];
	}
	
	
		
	//-------------------------------------------------------------------------------
	
	
	user->user_permission = user_permission;
	
	
	return user;
}

void user_delete(user_t* user)
{
	if(user == NULL)
	{
		//perror("Error at user_delete - user is null");
		exit(EXIT_FAILURE);
	}
	
	free(user->user_name);
	free(user->user_password);
	free(user);
}

char* user_get_id(user_t* user)
{
	if(user == NULL)
	{
		//perror("ERROR at user_get_id");
		exit(EXIT_FAILURE);
	}
	return user->user_id;
}

void user_set_id(user_t* user, char id[])
{
	if(user == NULL)
	{
		//perror("ERROR at user_set_id");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i<12; i++)
	{
		user->user_id[i] = id[i];
	}
	
	return;
}

char* user_get_name(user_t* user)
{
	if(user == NULL)
	{
		//perror("ERROR at user_get_name");
		exit(EXIT_FAILURE);
	}
	return user->user_name;
}
void user_set_name(user_t* user, char* user_name)
{
	if(user == NULL)
	{
		//perror("ERROR at user_set_name");
		exit(EXIT_FAILURE);
	}
	free(user->user_name);
	
	user->user_name = (char*)malloc(strlen((char*)user_name)+1);
	
	if(user->user_name == NULL)
	{
		//perror("ERROR: at user_set_password");
		exit(EXIT_FAILURE);
	}
	
	strncpy((char*)user->user_name, (char*)user_name,strlen((char*)user_name)+1);
	
}

int* user_get_password(user_t* user)
{
	if(user == NULL)
	{
		//perror("ERROR at user_get_password");
		exit(EXIT_FAILURE);
	}	
	return user->user_password;
}

void user_set_password(user_t* user, int* password)
{
	if(user == NULL)
	{
		//perror("ERROR at user_set_password");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i<6; i++)
	{
		user->user_password[i] = password[i];
	}
	
	return;
}


int user_get_permission(user_t* user)
{
	if(user == NULL)
	{
		//perror("ERROR at user_get_permission");
		exit(EXIT_FAILURE);
	}
	return user->user_permission;
}

void user_set_permission(user_t* user, int permission)
{
	if(user == NULL)
	{
		//perror("ERROR at user_set_permission");
		exit(EXIT_FAILURE);
	}
	
	user->user_permission = permission;
	
	return;
	
}

user_t* preset_users(int preset_user)
{

	switch(preset_user)
	{
		case 1:
		{
		char id0[12] = "1A FE 93 79";
		char name0[] = "Rafael";
		int password0[6] = {0,1,2,3,4,5};
		int permission0 = 9;
		user_t* user0 = user_new(id0, name0, password0, permission0);
				
		return user0;
		break;
		}
		
		case 2:
		{
		char id1[12] = "43 91 88 2E";
		char name1[] = "Joao";
		int password1[6] = {5,5,5,5,5,5};
		int permission1 = 1;
		user_t* user1 = user_new(id1, name1, password1, permission1);
		return user1;
		break;
		}
		
		case 3:
		{
		char id2[12] = "FD D5 79 25";
		char name2[] = "Felipe";
		int password2[6] = {9,8,7,6,5,4};
		int permission2 = 3;
		user_t* user2 = user_new(id2, name2, password2, permission2);
		
		return user2;
		break;
		}
	}
	
	
}
