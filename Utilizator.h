#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

class Utilizator
{
	char email[30], password[30];
public:
	char* get_email();
	char* get_password();
	char* password_strength(char* password);
	void set_email(char email[]);
	void set_password(char password[]);
	bool good_email(char email[]);
	void login_utilizator(Utilizator u[], int& nr_utilizatori);
	char* codif_password();
	void rezervare_loc();
};

