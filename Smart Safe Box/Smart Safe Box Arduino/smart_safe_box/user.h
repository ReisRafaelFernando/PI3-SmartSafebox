/*
 * user.h
 *
 * Created: 9/12/2018 4:03:03 PM
 *  Author: Rafael Fernando Reis
 */ 


#ifndef USER_H_
#define USER_H_

typedef struct user user_t;

user_t* user_new(char user_id[], char* user_name, int user_password[], int user_permission);

void user_delete(user_t* user);

char* user_get_id(user_t* user);
void user_set_id(user_t* user, char id[]);

char* user_get_name(user_t* user);
void user_set_name(user_t* user, char* user_name);

int* user_get_password(user_t* user);
void user_set_password(user_t* user, int password[]);

int user_get_permission(user_t* user);
void user_set_permission(user_t* user, int permission);

void perror(char const * s);


user_t* preset_users(int preset_user);

#endif /* USER_H_ */