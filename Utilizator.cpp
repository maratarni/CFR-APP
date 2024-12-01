#include "Utilizator.h"

char* Utilizator::get_email()
{
	return this->email;
}

char* Utilizator::get_password()
{
	return this->password;
}

char* Utilizator::password_strength(char* password)
{
	//o sa mi creez eu regulile daca o parola e week, ok, good.
	int nr_cifre = 0, nr_litere_mari = 0, nr_caractere_speciale = 0, nr_litere_mici = 0, lungime = 0;
	int i;
	char returnat[20]="";
	try {
		if (!password) 
		{
			throw invalid_argument("Parola nu poate fi null!");
		}
		lungime = strlen(password);
		for (i = 0; i < lungime; i++)
		{
			if (password[i] >= '0' && password[i] <= '9')
				nr_cifre++;
			else if (password[i] >= 'a' && password[i] <= 'z')
				nr_litere_mici++;
			else if (password[i] >= 'A' && password[i] <= 'Z')
				nr_litere_mari++;
			else
				nr_caractere_speciale++;
		}

		if (nr_caractere_speciale != 0 && nr_cifre != 0 && nr_litere_mari != 0 && nr_litere_mici != 0 && lungime >= 8)
			strcpy(returnat, "good");
		else
			if ((nr_caractere_speciale == 0 && nr_cifre != 0 && nr_litere_mari != 0 && nr_litere_mici != 0 && lungime >= 8) ||
				(nr_caractere_speciale != 0 && nr_cifre != 0 && nr_litere_mari == 0 && nr_litere_mici != 0 && lungime >= 8))//trebuie lucrat!!!!!!
				strcpy(returnat, "ok");
			else
				strcpy(returnat, "weak");
	}
	catch (...)
	{
		cout << "A aparut o eroare!\n";
		return nullptr;
	}
	return returnat;
}

void Utilizator::set_email(char email[])
{
	strcpy(this->email, email);
}

void Utilizator::set_password(char password[])
{
	strcpy(this->password, password);
}
//verificarea daca emailu e bun
bool Utilizator::good_email(char email[])
{
	int email_length = strlen(email);
	if (!(email[0] >= 'a' && email[0] <= 'z') || (email[0] >= 'A' && email[0] <= 'Z'))
	{
		return 0;
	}
	int At = -1, Dot = -1;
	for (int i = 0; i < email_length; i++)
	{
		if (email[i] == '@') {

			At = i;
		}

		else if (email[i] == '.') {

			Dot = i;
		}
	}
	if (At == -1 || Dot == -1)
		return 0;
	if (At > Dot)
		return 0;
	return !(Dot >= (email_length - 1));
}
//cam lunga functia asta
void Utilizator::login_utilizator(Utilizator u[], int& nr_utilizatori)
{
	int i, ok = 0;
	for (i = 0; i < nr_utilizatori; i++)
	{
		if (strcmp(u[i].get_email(), this->email) == 0)
		{	
			while (strcmp(u[i].get_password(), this->codif_password()))
			{
				cout << "Ati gresit parola, incercati din nou!\n";
				char new_password[20];
				cin >> new_password;
				this->set_password(new_password);
			}
			ok = 1;
			cout << "Autentificare reusita!\n";
		}
	}
	//asta e pt cazul in care am cont
	//stai sa vad daca merge
	//merge:)
	if (ok == 0)
	{
		cout << "Nu aveti cont\n";
		cout << "Doriti sa va faceti cont?\n";
		cout << "Raspuns: ";
		char raspuns[3];
		cin >> raspuns;
		if (strcmp(raspuns, "da") == 0 || strcmp(raspuns, "Da") == 0 || strcmp(raspuns, "DA") == 0)
		{
			cout << "Introduceti emailul: ";
			char email_plus[30];

			cin >> email_plus;//verificare
			while (1)
			{
				if (this->good_email(email_plus) == 1)
				{
					this->set_email(email_plus);
					break;
				}
				else
				{
					cout << "Nu ai introdus bine email-ul. Ai gresit sintaxa .Introdu-l inca o data si ai grija sa contina @ si .\n";
					cout << "Introduceti emailul: ";
					cin >> email_plus;
				}

			}
		//	this->set_email(email_plus);aici trebuie sa fac verificarea daca e email vbun formatat gen cu @

			char password_plus[30];
			cout << "Introduceti parola: ";
			cin >> password_plus;
			while (1)
			{
				if (strcmp(this->password_strength(password_plus),"good")==0)
				{
					this->set_password(password_plus);
					this->codif_password();

					u[nr_utilizatori].set_email(this->email);
					u[nr_utilizatori].set_password(this->password);
					nr_utilizatori++;
					cout << "Ati fost adaugat cu succes in baza noastra de date!\n";
					break;
				}
				else if (strcmp(this->password_strength(password_plus), "ok")==0)
				{
					this->set_password(password_plus);
					this->codif_password();

					u[nr_utilizatori].set_email(this->email);
					u[nr_utilizatori].set_password(this->password);
					nr_utilizatori++;
					cout << "Ati fost adaugat cu succes in baza noastra de date!\n";
					break;
				}
				else
				{
					cout << "introduceti o parola puternica!";
					cin >> password_plus;
				}

			}
		}
	}
}

//criptare
char * Utilizator::codif_password()
{
	const char key[] = "PROIECTPOO"; // inlocuieste "YOURKEY" cu cheia ta
	char out[30] = { 0 }; //initializare completa cu '\0'

	for (int i = 0, j = 0; i < strlen(this->password); ++i)
	{
		char c = this->password[i];

		// Transforma literele mici în litere mari
		if (c >= 'a' && c <= 'z')
			c = c - 'a' + 'A';

		// Salt peste caractere care nu sunt litere mari
		if (c < 'A' || c > 'Z')
			continue;

		// Aplica algoritmul de cifrare
		out[j] = (c + key[j % strlen(key)] - 2 * 'A') % 26 + 'A';
		++j;
	}

	// Asigura terminatorul '\0'
	out[strlen(out)] = '\0';

	// Salvare rezultat
	strcpy(this->password, out);
	return this->password;
}

void Utilizator::rezervare_loc()
{
	char oras[21];
	char ora[20], data[30];
	int clasa_trenului;
	cout << "\nIntroduceti destinatia: ";
	cin.ignore();
	cin.getline(oras, sizeof(oras));
	cout << "Data:";
	cin >> data;
	cout << "Ora: ";
	cin >> ora;

	ifstream iutilizatori("calatorii.csv");
	char linie[101];
	while (iutilizatori.getline(linie, sizeof(linie)))
	{
		char oras_citit[30];
		char ora_citita[20], data_citita[30];
		int nr_loc_clasa1 = 0;
		int nr_loc_clasa2 = 0;
		char* p = strtok(linie, ", ");
		if (p)
		{
			strncpy(oras_citit, p, sizeof(oras_citit) - 1);
			oras_citit[strlen(p) + 1] = '\0';
		}
		p = strtok(nullptr, ", ");
		if (p)
		{
			strncpy(data_citita, p, sizeof(data_citita) - 1);
			data_citita[strlen(p) + 1] = '\0'; 
		}
		p = strtok(nullptr, ", ");
		if (p)
		{
			strncpy(ora_citita, p, sizeof(ora_citita) - 1);
			ora_citita[strlen(p) + 1] = '\0';
		}
		p = strtok(nullptr, ", ");
		if (p)
		{
			nr_loc_clasa1 = atoi(p);
		}
		p = strtok(nullptr, ", ");
		if (p)
		{
			nr_loc_clasa2 = atoi(p);
		}
		char line[100];
		//cout << oras_citit << "\n\n" << data_citita << "\n\n" << ora_citita << "\n\n" << nr_loc_clasa1 << "\n\n" << nr_loc_clasa2 << "\n\n";
		if (strcmp(oras_citit, oras)==0 && strcmp(ora, ora_citita) == 0 && strcmp(data, data_citita) == 0)
		{
			cout << "La ce clasa vreti sa rezervati un loc?\n";
			cout << "Raspuns: ";
			int raspuns;
			cin >> raspuns;

			//incep cazurile pt alegere
			if (raspuns == 1)
			{
				if (nr_loc_clasa1 != 0)
				{
					cout << "Ati rezervat cu succes un loc la clasa 1!";
					//acum refac linia cu nr_loc_clasa1 mai mic
					strcpy(line, oras_citit);
					strcat(line, ", ");
					strcat(line, data_citita);
					strcat(line, ", ");
					strcat(line, ora_citita);
					strcat(line, ", ");

					char buffer[10];

					sprintf(buffer, "%d", nr_loc_clasa1);
					strcat(line, buffer);
					strcat(line, ", ");
					sprintf(buffer, "%d", nr_loc_clasa2);
					strcat(line, buffer);

					iutilizatori.close();
					ifstream iutilizatori("calatorii.csv");
					ofstream outilizatori("calatoriinou.csv");
					char line_read[101];
					int nr = 0;
					while (iutilizatori.getline(line_read, sizeof(line_read)))
					{
						if (strcmp(line_read, line)==0)
						{
							nr_loc_clasa1--;
							strcpy(line, oras_citit);
							strcat(line, ", ");
							strcat(line, data_citita);
							strcat(line, ", ");
							strcat(line, ora_citita);
							strcat(line, ", ");

							char buffer[10];
							sprintf(buffer, "%d", nr_loc_clasa1);
							strcat(line, buffer);
							strcat(line, ", ");
							sprintf(buffer, "%d", nr_loc_clasa2);
							strcat(line, buffer);
							if (nr)
							{
								outilizatori << '\n' << line;
							}
							else
							{
								outilizatori << line;
							}
							nr++;
						}
						else
						{
							
							if (nr)
							{
								outilizatori << '\n' << line_read;
							}
							else
							{
								outilizatori << line_read;
							}
							nr++;
						}
					}
					iutilizatori.close();
					outilizatori.close();
					remove("calatorii.csv");
					if (rename("calatoriinou.csv", "calatorii.csv"))
					{
						cout << "ERROR";
					}
				}
				else
				{
					cout << "Ne pare rau nu mai sunt locuri la clasa 1!\n" << endl;
				}
			}
			else if (raspuns == 2)
			{
				if (nr_loc_clasa2 != 0)
				{
					cout << "Ati rezervat cu succes un loc la clasa a 2-a!";
					//acum refac linia cu nr_loc_clasa1 mai mic
					strcpy(line, oras_citit);
					strcat(line, ", ");
					strcat(line, data_citita);
					strcat(line, ", ");
					strcat(line, ora_citita);
					strcat(line, ", ");

					char buffer[10];

					sprintf(buffer, "%d", nr_loc_clasa1);
					strcat(line, buffer);
					strcat(line, ", ");
					sprintf(buffer, "%d", nr_loc_clasa2);
					strcat(line, buffer);

					iutilizatori.close();
					ifstream iutilizatori("calatorii.csv");
					ofstream outilizatori("calatoriinou.csv");
					char line_read[101];
					int nr = 0;
					while (iutilizatori.getline(line_read, sizeof(line_read)))
					{
						if (strcmp(line_read, line) == 0)
						{
							nr_loc_clasa2--;
							strcpy(line, oras_citit);
							strcat(line, ", ");
							strcat(line, data_citita);
							strcat(line, ", ");
							strcat(line, ora_citita);
							strcat(line, ", ");

							char buffer[10];
							sprintf(buffer, "%d", nr_loc_clasa1);
							strcat(line, buffer);
							strcat(line, ", ");
							sprintf(buffer, "%d", nr_loc_clasa2);
							strcat(line, buffer);
							if (nr)
							{
								outilizatori << '\n' << line;
							}
							else
							{
								outilizatori << line;
							}
							nr++;
						}
						else
						{

							if (nr)
							{
								outilizatori << '\n' << line_read;
							}
							else
							{
								outilizatori << line_read;
							}
							nr++;
						}
					}
					iutilizatori.close();
					outilizatori.close();
					remove("calatorii.csv");
					if (rename("calatoriinou.csv", "calatorii.csv"))
					{
						cout << "ERROR";
					}
				}
				else
				{
					cout << "Ne pare rau nu mai sunt locuri la clasa a 2-a!" << endl;
				}
			}
		}
	}
}


