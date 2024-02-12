#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

string nazwaPlikuZUzytkownikami = "ZarejestrowaniUzytkownicy.txt";
string nazwaPlikuZAdresatami = "KsiazkaAdresowa.txt";

struct Uzytkownik {
    int idUzytkownika = 0;
    string nazwa = "", haslo = "";
};

struct Adresat
{
    int idAdresata = 0;
    int idUzytkownikaZPliku;
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

bool czyNazwaUzytkownikaIstnieje(const vector<Uzytkownik>& uzytkownicy, const string& nazwa)
{
    for (const auto& uzytkownik : uzytkownicy)
    {
        if (uzytkownik.nazwa == nazwa)
        {
            return true;
        }
    }
    return false;
}

Uzytkownik pobierzDaneUzytkownika(string daneUzytkownikaOddzielonePionowymiKreskami)
{
    Uzytkownik uzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int numerPojedynczejDanejUzytkownika = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneUzytkownikaOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaUzytkownika += daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejUzytkownika)
            {
            case 1:
                uzytkownik.idUzytkownika = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                uzytkownik.nazwa = pojedynczaDanaUzytkownika;
                break;
            case 3:
                uzytkownik.haslo = pojedynczaDanaUzytkownika;
                break;
            }
            pojedynczaDanaUzytkownika = "";
            numerPojedynczejDanejUzytkownika++;
        }
    }
    return uzytkownik;
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
                adresat.idAdresata = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                adresat.idUzytkownikaZPliku = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 3:
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.email = pojedynczaDanaAdresata;
                break;
            case 7:
                adresat.adres = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

void wczytajUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy, int& iloscUzytkownikow)
{
    Uzytkownik uzytkownik;
    string daneJednegoUzytkownikaOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZUzytkownikami.c_str(), ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoUzytkownikaOddzielonePionowymiKreskami))
        {
            uzytkownik = pobierzDaneUzytkownika(daneJednegoUzytkownikaOddzielonePionowymiKreskami);

            uzytkownicy.push_back(uzytkownik);
        }
        plikTekstowy.close();
        iloscUzytkownikow = uzytkownicy.size();
    }
}

void wczytajAdresatowZPliku(vector<Adresat> &adresaci)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZAdresatami.c_str(), ios::in);

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

void wypiszWszystkichAdresatow(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    system("cls");
    if (!adresaci.empty())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->idUzytkownikaZPliku == idZalogowanegoUzytkownika)
            {
            cout << "Id:                 " << itr->idAdresata << endl;
            cout << "Imie:               " << itr->imie << endl;
            cout << "Nazwisko:           " << itr->nazwisko << endl;
            cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
            cout << "Email:              " << itr->email << endl;
            cout << "Adres:              " << itr->adres << endl << endl;
            }
        }
        cout << endl;
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

void dopiszUzytkownikaDoPliku(Uzytkownik uzytkownik)
{
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZUzytkownikami.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << uzytkownik.idUzytkownika << '|';
        plikTekstowy << uzytkownik.nazwa << '|';
        plikTekstowy << uzytkownik.haslo << '|' << endl;
        plikTekstowy.close();

        cout << endl << "Uzytkownik zarejestrowany poprawnie" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void dopiszAdresataDoPliku(Adresat adresat, vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZAdresatami.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << adresat.idAdresata << '|';
        plikTekstowy << idZalogowanegoUzytkownika << '|';
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

    plikTekstowy.open(nazwaPlikuZAdresatami.c_str(), ios::out);
    if (plikTekstowy.good())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            liniaZDanymiAdresata += konwerjsaIntNaString(itr->idAdresata) + '|';
            liniaZDanymiAdresata += konwerjsaIntNaString(itr->idUzytkownikaZPliku) + '|';
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

void wyszukajAdresatowPoImieniu(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    string imiePoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE ADRESATOW O IMIENIU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o imieniu: ";
        cin >> imiePoszukiwanegoAdresata;
        cin.ignore();

        imiePoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imiePoszukiwanegoAdresata);

        for (vector<Adresat>::iterator  itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->imie == imiePoszukiwanegoAdresata & itr->idUzytkownikaZPliku == idZalogowanegoUzytkownika)
            {
                cout << endl;
                cout << "Id:                 " << itr->idAdresata << endl;
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

void wyszukajAdresatowPoNazwisku(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    string nazwiskoPoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE ADRESATOW O NAZWISKU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o nazwisku: ";
        cin >> nazwiskoPoszukiwanegoAdresata;
        cin.ignore();

        nazwiskoPoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoPoszukiwanegoAdresata);

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->nazwisko == nazwiskoPoszukiwanegoAdresata & itr->idUzytkownikaZPliku == idZalogowanegoUzytkownika)
            {
                cout << endl;
                cout << "Id:                 " << itr->idAdresata << endl;
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

void dodajAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    Adresat adresat;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;

    if (adresaci.empty() == true)
    {
       adresat.idAdresata = 1;
    }
    else
    {
       adresat.idAdresata = adresaci.back().idAdresata + 1;
    }

    cout << "Podaj imie: ";
    cin >> adresat.imie;
    cin.ignore();
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
    adresat.adres = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.adres);

    adresaci.push_back(adresat);

    dopiszAdresataDoPliku(adresat, adresaci, idZalogowanegoUzytkownika);
}

 void usunAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    int idUsuwanegoAdresata = 0;
    char znak;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> USUWANIE WYBRANEJ OSOBY <<<" << endl << endl;
        cout << "Podaj numer ID adresata ktorego chcesz USUNAC: ";
        cin >> idUsuwanegoAdresata;
        cin.ignore();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->idAdresata == idUsuwanegoAdresata & itr->idUzytkownikaZPliku == idZalogowanegoUzytkownika)
            {
                czyIstniejeAdresat = true;

                if (itr->idAdresata == idUsuwanegoAdresata )
               {
                cout << endl;
                cout << "Id:                 " << itr->idAdresata << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl;
               }
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
            if (itr->idAdresata == idWybranegoAdresata)
            {
                czyIstniejeAdresat = true;

                if (itr->idAdresata == idWybranegoAdresata)
               {
                cout << endl;
                cout << "Id:                 " << itr->idAdresata << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl << endl;
               }

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

int rejestracjaDodajUzytkownika(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    Uzytkownik uzytkownik;
    string nazwa, haslo;

    system("cls");
    cout << ">>> REJESTRACJA <<<" << endl << endl;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    if (czyNazwaUzytkownikaIstnieje(uzytkownicy, nazwa))
    {
        cout << "Podana nazwa uzytkownika juz istnieje. Wybierz inna nazwe: ";
        cin >> nazwa;
    }

    if (uzytkownicy.empty() == true)
    {
       uzytkownik.idUzytkownika = 1;
    }
    else
    {
       uzytkownik.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
    }

    cout << "Podaj haslo: ";
    cin >> haslo;
    uzytkownik.nazwa = nazwa;
    uzytkownik.haslo = haslo;

    uzytkownicy.push_back(uzytkownik);

    dopiszUzytkownikaDoPliku(uzytkownik);
    iloscUzytkownikow++;
    return iloscUzytkownikow;
}

int logowanie(const vector<Uzytkownik>& uzytkownicy, int iloscUzytkownikow)
{
    string nazwa, haslo;
    int proba = 0;

        cout << "Podaj nazwe uzytkownika: ";
        cin >> nazwa;

     if (!czyNazwaUzytkownikaIstnieje(uzytkownicy, nazwa))
    {
        cout << "Podana nazwa uzytkownika nie istnieje!";
        Sleep (2500);
        return 0;
    }


    while (proba < 3) {
        cout << "Podaj haslo: ";
        cin >> haslo;

        for (const auto& uzytkownik : uzytkownicy) {
            if (uzytkownik.nazwa == nazwa && uzytkownik.haslo == haslo) {
                cout << "Zalogowano pomyslnie!" << endl;
                Sleep (1000);
                return uzytkownik.idUzytkownika;
            }
        }

        proba++;
        if (proba < 3) {
            cout << "Bledne haslo. Pozostalo prob: " << 3 - proba << endl;
        } else {
            cout << "Bledne haslo. Przekroczono limit prob logowania." << endl;
        }
    }

    system("pause");
    exit(0);
}

void zmianaHasla(vector<Uzytkownik>& uzytkownicy, int iloscUzytkownikow, int idZalogowanegoUzytkownika) {
    string noweHaslo;
    cout << "Podaj nowe haslo: ";
    cin >> noweHaslo;

    for (auto& uzytkownik : uzytkownicy) {
        if (uzytkownik.idUzytkownika == idZalogowanegoUzytkownika) {
            uzytkownik.haslo = noweHaslo;
            cout << "Haslo zostalo zmienione" << endl;

            // Aktualizacja pliku z danymi u¿ytkowników
            fstream plikTekstowy;
            plikTekstowy.open(nazwaPlikuZUzytkownikami.c_str(), ios::out);

            if (plikTekstowy.good()) {
                for (const auto& u : uzytkownicy) {
                    plikTekstowy << u.idUzytkownika << '|';
                    plikTekstowy << u.nazwa << '|';
                    plikTekstowy << u.haslo << '|' << endl;
                }

                plikTekstowy.close();
            } else {
                cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
            }

            Sleep(1500);
            return;
        }
    }

    cout << "Nie znaleziono uzytkownika o zadanym ID." << endl;
    Sleep(1500);
}

void zakonczProgram()
{
    cout << endl << "Koniec programu." << endl;
    exit(0);
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;

    char wybor;

    wczytajUzytkownikowZPliku(uzytkownicy, iloscUzytkownikow);

    while(1) {
        if (idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. logowanie" << endl;
            cout << "9. Zakoncz Program" << endl << endl;
            cout << "Twoj wybor: "; cin >> wybor;

            if (wybor == '1') {
                iloscUzytkownikow = rejestracjaDodajUzytkownika(uzytkownicy, iloscUzytkownikow);
            } else if (wybor == '2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
            } else if (wybor == '9') {
                exit(0);
            }
        } else {
            vector <Adresat> adresaci;
            wczytajAdresatowZPliku(adresaci);

            system ("cls");

            cout << ">>> KSIAZKA ADRESOWA | ZALOGOWANY <<<" << endl << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmiana hasla" << endl;
            cout << "8. Wylogowanie" << endl;
            cout << "9. Zakoncz program" << endl << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

        switch(wybor)
        {
        case '1':
            dodajAdresata(adresaci, idZalogowanegoUzytkownika);
            break;
        case '2':
            wyszukajAdresatowPoImieniu(adresaci, idZalogowanegoUzytkownika);
            break;
        case '3':
            wyszukajAdresatowPoNazwisku(adresaci, idZalogowanegoUzytkownika);
            break;
        case '4':
            wypiszWszystkichAdresatow(adresaci, idZalogowanegoUzytkownika);
            break;
        case '5':
            usunAdresata(adresaci, idZalogowanegoUzytkownika);
            break;
        case '6':
            edytujAdresata(adresaci);
            break;
        case '7':
            zmianaHasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
            break;
        case '8':
            idZalogowanegoUzytkownika = 0;
            break;
        case '9':
            zakonczProgram();
            break;
        }
      }
    }
    return 0;
}
