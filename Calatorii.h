#pragma once
#include "Operator.h"

class Calatorii
{
	char nume_oras[100];
	char data[12];
	char ora[10];
	int nr_locuri_clasa1, nr_locuri_clasa2;
public:
	char* get_nume_oras();
	char* get_data();
	char* get_ora();
	int get_nr_locuri_clasa1();
	int get_nr_locuri_clasa2();
	void set_all(char nume_oras[], char data[], char ora[], int nr_locuri_clasa1, int nr_locuri_clasa2);
};

