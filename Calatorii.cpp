#include "Calatorii.h"

char* Calatorii::get_nume_oras()
{
	return this->nume_oras;
}

char* Calatorii::get_data()
{
	return this->data;
}

char* Calatorii::get_ora()
{
	return this->ora;
}

int Calatorii::get_nr_locuri_clasa1()
{
	return this->nr_locuri_clasa1;
}
int Calatorii::get_nr_locuri_clasa2()
{
	return this->nr_locuri_clasa2;
}
void Calatorii::set_all(char nume_oras[], char data[], char ora[], int nr_locuri_clasa1, int nr_locuri_clasa2)
{
	strcpy(this->nume_oras, nume_oras);
	strcpy(this->data, data);
	strcpy(this->ora, ora);
	this->nr_locuri_clasa1 = nr_locuri_clasa1;
	this->nr_locuri_clasa2 = nr_locuri_clasa2;
}

