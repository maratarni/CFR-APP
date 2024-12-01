#include "Calatorii.h"

//aici imi creez vectorul d eoperatori
void vector_operatori(ifstream& file, Operator o[], int &nr_operatori)
{
    nr_operatori = 0;

    while (file.good())
    {
        char nume[20];
        char parola[30];
        file >> nume>> parola;
        file.ignore();
        nume[strlen(nume)-1] = '\0';
        //cout << nume << "\n\n\n";
        o[nr_operatori].set_name(nume);
        o[nr_operatori].set_password(parola);
        nr_operatori++;
    }
}
//verific daca imi afiseaza bine
void afisare_operatori(Operator o[], int& nr_operatori)
{
    int i;
    for (i = 0; i < nr_operatori; i++)
    {
        cout << o[i].get_name()<<' ';
        cout << o[i].get_password() << endl;
    }
}


//utilizatori
void vector_utilizatori(ifstream& file, Utilizator u[], int& nr_utilizatori)
{
    nr_utilizatori = 0;

    while (file.good())
    {
        char email[30];
        char parola[30];
        file >> email >> parola;
        file.ignore();
        email[strlen(email) - 1] = '\0';
        //cout << nume << "\n\n\n";
        u[nr_utilizatori].set_email(email);
        u[nr_utilizatori].set_password(parola);
        nr_utilizatori++;
    }
}
//verific daca imi afiseaza bine
void afisare_utilizatori(Utilizator u[], int& nr_utilizatori)
{
    int i;
    for (i = 0; i < nr_utilizatori; i++)
    {
        cout << u[i].get_email() <<' ';
        cout << u[i].get_password() << endl;
    }
}
void scriere_fisier_utilizatori(ofstream &file, Utilizator u[], int& nr_utilizatori)
{
    int i;
    for (i = 0; i < nr_utilizatori;i++)
    {
        file << u[i].get_email() << ", " << u[i].get_password();
        if (i != nr_utilizatori - 1)
        {
            file << endl;
        }
    }
}
//formarea de vector de calatorii
void vector_calatorii(ifstream& file, Calatorii c[], int& nr_calatorii)
{
    nr_calatorii = 0;
    char linie[100];
    while (file.getline(linie, sizeof(linie)))
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
        c[nr_calatorii].set_all(oras_citit, data_citita, ora_citita, nr_loc_clasa1, nr_loc_clasa2);
        nr_calatorii++;
    }
}
//verific daca imi afiseaza bine
void afisare_calatorii_utilizatori(Calatorii c[], int& nr_calatorii)
{
    int i;
    for (i = 0; i < nr_calatorii; i++)
    {
        cout << c[i].get_nume_oras() << ' ';
        cout << c[i].get_data() << ' ';
        cout << c[i].get_ora() << ' ';
        cout << endl;
    }
}

int main() {
    cout << "Buna ziua!";
    cout << "Sunteti utilizator sau operator?\n";
    cout << "Functie: ";
    char pozitie[20];
    cin >> pozitie;
    while (1)
    {
        if (strcmp(pozitie, "operator") == 0 || strcmp(pozitie, "Operator")==0 || strcmp(pozitie, "OPERATOR")==0)
        {
            ifstream ioperatori("operatori.csv");
            int nr_operatori;

            Operator o[20];

            vector_operatori(ioperatori, o, nr_operatori);
            //afisare_operatori(o, nr_operatori);

            cout << "Introduceti username-ul si parola\n";
            cout << "USERNAME:";
            char new_name[20];
            cin >> new_name;
            cout << "PAROLA:";
            char new_password[20];
            cin >> new_password;

            Operator new_operator;

            new_operator.set_name(new_name);
            new_operator.set_password(new_password);
            new_operator.login_operator(o, nr_operatori);
            break;

        }
        else
            if (strcmp(pozitie, "utilizator") == 0 || strcmp(pozitie, "Utilizator") == 0|| strcmp(pozitie, "UTILIZATOR") == 0)
            {
                ifstream iutilizatori("utilzatori.csv");
                int nr_utilizatori;

                Utilizator u[20];

                vector_utilizatori(iutilizatori, u, nr_utilizatori);
                //afisare_utilizatori(u, nr_utilizatori);
                cout << "Logati-va cu e-mail si parola\n";
                cout << "EMAIL:";
                char new_email[30];
                cin >> new_email;
                cout << "PAROLA:";
                char new_password[30];
                cin >> new_password;

                Utilizator new_utilizator;

                new_utilizator.set_email(new_email);
                new_utilizator.set_password(new_password);
                new_utilizator.login_utilizator(u, nr_utilizatori);

                Calatorii c[20];
                ifstream icalatorii("calatorii.csv");

                int nr_calatorii;
                vector_calatorii(icalatorii, c, nr_calatorii);
                icalatorii.close();

                cout << "Acestea sunt calatoriile! Puteti rezerva o cursa distre acestea!\n";
                afisare_calatorii_utilizatori(c, nr_calatorii);
                new_utilizator.rezervare_loc();

                ofstream outilizatori("utilzatori.csv");
                scriere_fisier_utilizatori(outilizatori, u, nr_utilizatori);
                break;
            }
            else
            {
                cout << "Nu exista functia pe care ati introdus-o. Incercati din nou: ";
                cin >> pozitie;
            }
    }
    return 0;
}
