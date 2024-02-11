// KSIAZKA ADRESOWA
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

string nazwaPliku = "KsiazkaAdresowa.txt";

struct Adresat
{
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

string wczytajLinie()
{
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak  = {0};

    while (true)
    {
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

int wczytajLiczbeCalkowita()
{
    string wejscie = "";
    int liczba = 0;

    while (true)
    {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return liczba;
}

string konwerjsaIntNaString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst)
{
    if (!tekst.empty())
    {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.id = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case 3:
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.email = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.adres = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

void wczytajAdresatowZPliku(vector<Adresat> &adresaci)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPliku.c_str(), ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);

            adresaci.push_back(adresat);
        }
        plikTekstowy.close();
    }
}

void wypiszWszystkichAdresatow(vector<Adresat> &adresaci)
{
    system("cls");
    if (!adresaci.empty())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            cout << "Id:                 " << itr->id << endl;
            cout << "Imie:               " << itr->imie << endl;
            cout << "Nazwisko:           " << itr->nazwisko << endl;
            cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
            cout << "Email:              " << itr->email << endl;
            cout << "Adres:              " << itr->adres << endl << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}

void dopiszAdresataDoPliku(Adresat adresat)
{
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPliku.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << adresat.id << '|';
        plikTekstowy << adresat.imie << '|';
        plikTekstowy << adresat.nazwisko << '|';
        plikTekstowy << adresat.numerTelefonu << '|';
        plikTekstowy << adresat.email << '|';
        plikTekstowy << adresat.adres << '|' << endl;
        plikTekstowy.close();

        cout << endl << "Adresat zostal dodany" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void zapiszWszystkichAdresatowDoPlikuTekstowego(vector<Adresat> &adresaci)
{
    fstream plikTekstowy;
    string liniaZDanymiAdresata = "";

    plikTekstowy.open(nazwaPliku.c_str(), ios::out);
    if (plikTekstowy.good())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            liniaZDanymiAdresata += konwerjsaIntNaString(itr->id) + '|';
            liniaZDanymiAdresata += itr->imie + '|';
            liniaZDanymiAdresata += itr->nazwisko + '|';
            liniaZDanymiAdresata += itr->numerTelefonu + '|';
            liniaZDanymiAdresata += itr->email + '|';
            liniaZDanymiAdresata += itr->adres + '|';

            plikTekstowy << liniaZDanymiAdresata << endl;
            liniaZDanymiAdresata = "";
        }
        plikTekstowy.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku KsiazkaAdresowa.txt" << endl;
    }
}

void wyszukajAdresatowPoImieniu(vector<Adresat> &adresaci)
{
    string imiePoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE ADRESATOW O IMIENIU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o imieniu: ";
        imiePoszukiwanegoAdresata = wczytajLinie();

        imiePoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imiePoszukiwanegoAdresata);

        for (vector<Adresat>::iterator  itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->imie == imiePoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:                 " << itr->id << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z imieniem: >>> " << imiePoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void wyszukajAdresatowPoNazwisku(vector<Adresat> &adresaci)
{
    string nazwiskoPoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE ADRESATOW O NAZWISKU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o nazwisku: ";
        nazwiskoPoszukiwanegoAdresata = wczytajLinie();
        nazwiskoPoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoPoszukiwanegoAdresata);

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->nazwisko == nazwiskoPoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:                 " << itr->id << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym nazwiskiem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z nazwiskiem: >>> " << nazwiskoPoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void dodajAdresata(vector<Adresat> &adresaci)
{
    Adresat adresat;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;

    if (adresaci.empty() == true)
    {
       adresat.id = 1;
    }
    else
    {
       adresat.id = adresaci.back().id + 1;
    }

    cout << "Podaj imie: ";
    adresat.imie = wczytajLinie();
    adresat.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.imie);

    cout << "Podaj nazwisko: ";
    adresat.nazwisko  = wczytajLinie();
    adresat.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.nazwisko);

    cout << "Podaj numer telefonu: ";
    adresat.numerTelefonu = wczytajLinie();

    cout << "Podaj email: ";
    adresat.email = wczytajLinie();

    cout << "Podaj adres: ";
    adresat.adres = wczytajLinie();

    adresaci.push_back(adresat);

    dopiszAdresataDoPliku(adresat);
}

void edytujAdresata(vector<Adresat> &adresaci)
{
    int idWybranegoAdresata = 0;
    char wybor;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> EDYCJA WYBRANEGO ADRESATA <<<" << endl << endl;
        cout << "Podaj numer ID adresata u ktorego chcesz zmienic dane: ";
        idWybranegoAdresata = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->id == idWybranegoAdresata)
            {
                czyIstniejeAdresat = true;

                cout << endl << "Ktore dane zaktualizowac: " << endl;
                cout << "1 - Imie" << endl;
                cout << "2 - Nazwisko" << endl;
                cout << "3 - Numer telefonu" << endl;
                cout << "4 - Email" << endl;
                cout << "5 - Adres" << endl;
                cout << "6 - Powrot " << endl;
                cout << endl << "Wybierz 1-6: ";
                wybor = wczytajZnak();

                switch (wybor)
                {
                case '1':
                    cout << "Podaj nowe imie: ";
                    itr->imie = wczytajLinie();
                    itr->imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->imie);
                    cout << endl << "Imie zostalo zmienione" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    itr->nazwisko = wczytajLinie();
                    itr->nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->nazwisko);
                    cout << endl << "Nazwisko zostalo zmienione" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    itr->numerTelefonu = wczytajLinie();
                    cout << endl << "Numer telefonu zostal zmieniony" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
                    break;
                case '4':
                    cout << "Podaj nowy email: ";
                    itr->email = wczytajLinie();
                    cout << endl << "Email zostal zmieniony" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
                    break;
                case '5':
                    cout << "Podaj nowy adres zamieszkania: ";
                    itr->adres = wczytajLinie();
                    cout << endl << "Adres zostal zmieniony" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
                    break;
                case '6':
                    cout << endl << "Powrot do menu glownego" << endl << endl;
                    break;
                default:
                    cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false)
        {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

 void usunAdresata(vector<Adresat> &adresaci)
{
    int idUsuwanegoAdresata = 0;
    char znak;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> USUWANIE WYBRANEJ OSOBY <<<" << endl << endl;
        cout << "Podaj numer ID adresata ktorego chcesz USUNAC: ";
        idUsuwanegoAdresata = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->id == idUsuwanegoAdresata)
            {
                czyIstniejeAdresat = true;
                cout << endl << endl << "Potwierdz naciskajac klawisz 't': ";
                znak = wczytajZnak();
                if (znak == 't')
                {
                    adresaci.erase(itr);
                    cout << endl << endl << "Szukany adresat zostal USUNIETY" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
                    break;
                }
                else
                {
                    cout << endl << endl << "Wybrany adresat NIE zostal usuniety" << endl << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false)
        {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }

    system("pause");
}


void zakonczProgram()
{
    cout << endl << "Koniec programu." << endl;
    exit(0);
}

int main()
{
    vector<Adresat> adresaci;
    char wybor;

    wczytajAdresatowZPliku(adresaci);

    while (true)
    {
        system("cls");
        cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl << endl;
        cout << "Twoj wybor: ";
        wybor = wczytajZnak();

        switch(wybor)
        {
        case '1':
            dodajAdresata(adresaci);
            break;
        case '2':
            wyszukajAdresatowPoImieniu(adresaci);
            break;
        case '3':
            wyszukajAdresatowPoNazwisku(adresaci);
            break;
        case '4':
            wypiszWszystkichAdresatow(adresaci);
            break;
        case '5':
            usunAdresata(adresaci);
            break;
        case '6':
            edytujAdresata(adresaci);
            break;
        case '9':
            zakonczProgram();
            break;
        }
    }
    return 0;
}
