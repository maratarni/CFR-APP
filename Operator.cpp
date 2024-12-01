#include "Operator.h"
void Operator::set_name(char name[])
{
	strcpy(this->name, name);
}

void Operator::set_password(char password[])
{
	strcpy(this->password, password);
}

char* Operator::get_name()
{
	return this->name;
}

char* Operator::get_password()
{
	return this->password;
}

void Operator::login_operator(Operator o[], int& nr_operatori)
{
	int i, ok = 0;
	for (i = 0; i < nr_operatori; i++)
	{
		if (strcmp(o[i].name, this->name) == 0)
		{
			while (strcmp(o[i].password, this->password))
			{
				cout << "Ati gresit parola, incercati din nou!\n";
				char new_password[20];
				cin >> new_password;
				this->set_password(new_password);
			}
			ok = 1;
			cout << "Autentificare reusita!\n";
			cout << "Ce doriti sa faceti?\n";
			cout << "Pentru adaugare curse apasati 1, pentru stergere curse apasati 2\n";
			int alegere;
			cin >> alegere;
			while (1)
			{
				if (alegere == 1)//sa adauge curse
				{
					string oras;
					char ora[20], data[30];
					int nr_locuri_disponibile_clasa1;
					int nr_locuri_disponibile_clasa2;
					ofstream ocalatorii("calatorii.csv", ios::app);
					cout << "Introduceti destinatia: ";
					cin.ignore();
					getline(cin, oras);
					bool ok3 = validCity(oras);
					while (1)
					{
						if (ok3 == false)
						{
							cout << "Nu exista acest oras, incercati din nou!\n";
							getline(cin, oras);
							ok3 = validCity(oras);
						}
						else
							break;
					}
					cout << "Data:";
					cin >> data;
					char data_aux1[30], data_aux2[30];
					strcpy(data_aux1, data);
					strcpy(data_aux2, data);
					bool ok1 = valid_date(data_aux1);
					bool ok2 = isPresentOrFutureDate(data_aux2);
					while (1)
					{
						if (ok1 == false || ok2 == false)
						{
							cout << "Ati introdus o data din trecut sau o data nevalida!\n";
							cin >> data;
							strcpy(data_aux1, data);
							strcpy(data_aux2, data);
							ok1 = valid_date(data_aux1);
							ok2 = isPresentOrFutureDate(data_aux2);
						}
						else
							break;
					}
					cout << "Ora: ";
					cin >> ora;
					cout << "Numarul de locuri_disponibile la clasa 1: ";
					cin >> nr_locuri_disponibile_clasa1;
					cout << "Numarul de locuri_disponibile la clasa 2: ";
					cin >> nr_locuri_disponibile_clasa2;
					ocalatorii << endl << oras << ", " << data << ", " << ora << ", " << nr_locuri_disponibile_clasa1 << ", " << nr_locuri_disponibile_clasa2;
					cout << "A fost introdusa cu succes cursa!";
					ocalatorii.close();
					break;
				}
				else if (alegere == 2)//sa stearga curse
				{
					string oras;
					char ora[20], data[30];
					char nr_locuri_disponibile_clasa1[10], nr_locuri_disponibile_clasa2[10];
					cout << "Introduceti datele calatoriei pe care vreti sa o stergeti \n";
					cout << "Introduceti destinatia: ";
					cin.ignore();
					getline(cin, oras);
					cout << "Data:";
					cin >> data;
					cout << "Ora: ";
					cin >> ora;
					cout << "Numarul de locuri_disponibile de la clasa 1: ";
					cin >> nr_locuri_disponibile_clasa1;
					cout << "Numarul de locuri_disponibile de la clasa 2: ";
					cin >> nr_locuri_disponibile_clasa2;
					char line[100];
					strcpy(line, oras.c_str());
					strcat(line, ", ");
					strcat(line, data);
					strcat(line, ", ");
					strcat(line, ora);
					strcat(line, ", ");
					strcat(line, nr_locuri_disponibile_clasa1);
					strcat(line, ", ");
					strcat(line, nr_locuri_disponibile_clasa2);
					//deschid fisierul , citesc ce vreau sa sterg, si citesc linie cu linie si compar si ddaca da , sterg din fisier adica fac un fisier nou si il redenumesc
					//sau bag in vector sterg si suprascriu
					ifstream icalatorii("calatorii.csv");
					ofstream ocalatorii("calatoriinou.csv");
					char line_read[101];
					int nr = 0;
					int ok = 0;
					while (icalatorii.getline(line_read, sizeof(line_read)))
					{
						if (strcmp(line_read, line))
						{
							if (nr)
							{
								ocalatorii << '\n' << line_read;
							}
							else
							{
								ocalatorii << line_read;
							}
							nr++;
						}
						ok++;
					}
					if (nr==ok)
					{
						cout << "Nu exista calatoria pe care ati introdus-o!\n";
					}
					else
					{
						cout << "Ati eliminat calatoria cu succes!";
					}
					icalatorii.close();
					ocalatorii.close();
					remove("calatorii.csv");
					if (rename("calatoriinou.csv", "calatorii.csv"))
					{
						cout << "ERROR";
					}
					break;
				}
				cout << "Nu ati ales o varianta valida!Iroduceti din nou 1 sau 2!\n";
				cin >> alegere;
			}
		}
	}
	if (ok == 0)
		cout << "Nu figurati ca operator! La revedere! \n";
}

bool Operator::valid_date(char date[])
{
	int day=0, month=0, year=0;
	char* p = strtok(date,".");
	if (p)
	{
		day = atoi(p);
		p = strtok(nullptr, ".");
	}
	if (p)
	{
		month = atoi(p);
		p = strtok(nullptr, ".");
	}
	if (p)
	{
		year = atoi(p);
		p = strtok(nullptr, ".");
	}

	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;


	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;

		if (month == 2) {
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
				if (day > 29)
					return false;
			}
			else {
				if (day > 28)
					return false;
			}
		}
		return true;
	}

bool Operator::isPresentOrFutureDate(char date[])
{
	int day=0, month=0, year=0;
	char* p = strtok(date, ".");
	if (p)
	{
		day = atoi(p);
		p = strtok(nullptr, ".");
	}
	if (p)
	{
		month = atoi(p);
		p = strtok(nullptr, ".");
	}
	if (p)
	{
		year = atoi(p);
		p = strtok(nullptr, ".");
	}

	time_t t = time(0); 
	tm* now = localtime(&t);

	int current_year = now->tm_year + 1900;
	int current_month = now->tm_mon + 1;
	int current_day = now->tm_mday;

	if (year > current_year) return true;
	if (year == current_year && month > current_month) return true;
	if (year == current_year && month == current_month && day >= current_day) return true;

	return false;
}

bool Operator::validCity(string oras)
{
	for (int j = 0; j < oras.length(); j++)
		if(!((oras[j]>='a'&&oras[j]<='z')|| (oras[j] >= 'A' && oras[j] <= 'Z') || oras[j]==' '))
		return false;
	return true;
}
