#include"User.h"

User::User() {}
User::User(char id[], char name[]){
	strcpy_s(m_id, id);
	strcpy_s(m_name, name);
}