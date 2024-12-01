#pragma once
#include "Utilizator.h"

class Operator
{
	char name[50], password[30];
public:
	void set_name(char name[]);
	void set_password(char password[]);
	char* get_name();
	char* get_password();
	void login_operator(Operator o[], int& nr_operatori);
	bool valid_date(char date[]);
	bool isPresentOrFutureDate(char date[]);
	bool validCity(string oras);

};

