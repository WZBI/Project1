#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include<list>
#include<map>
#include<vector>
#include<sstream>



using namespace std;
string zamianawielkosciliter(string input) {
	string output = input;
	transform(output.begin(), output.end(), output.begin(), ::tolower);             //zamiana wielkiej litery na ma≥a
	output[0] = toupper(output[0]);
	return output;
}


int main()	
{
	int powrot;
	poczatek:
	string wybor;
	system("cls");
	while (true) {
		cout << "1.Podroz\n";
		cout << "2.Budowa drogi\n";
		cout << "3.Wybudowane drogi\n";
		cout << "4.Wyburz wszystkie drogi.\n";
		cout << "5.Zakoncz program\n";
		cin >> wybor;
		if (wybor == "1") {
			system("cls");
			string Miastowy, Miastodo, line3;

			cout << "Do ktorego miasta chcesz sie udac: ";
			cin >> Miastodo;
			Miastodo = zamianawielkosciliter(Miastodo);
			ifstream plikzapisu;
			plikzapisu.open("plikzaspizu.cvs");
			if (!plikzapisu.is_open()) {
				cout << "Brak wybudowanych drug.";
				return 0;
			}

			bool czywybudowane = false;
			while (!czywybudowane && (getline(plikzapisu, line3))) {
				cout << "Z jakiego miasta wyruszasz: ";
				cin >> Miastowy;
				Miastowy = zamianawielkosciliter(Miastowy);
				if (Miastowy.find_first_not_of("0123456789") == string::npos) {
					cout << "Nie mozesz wprowadzic liczby jako nazwy miasta." << endl;
					continue;
				}
				plikzapisu.clear();
				plikzapisu.seekg(0, ios::beg);

				while (getline(plikzapisu, line3)) {
					if (line3.find(Miastowy + " " + Miastodo) != string::npos || line3.find(Miastodo + " " + Miastowy) != string::npos) {		//sprawdzanie czy po≥πczenie istnieje
						czywybudowane = true;
						cout << "Podroz udana." << endl;
						break;
					}

				}
				if (!czywybudowane) {
					cout << "Brak polaczenia drogowego miedzy miastami." << endl;
				}
			}
			cout << "Aby powrocic do menu nacisnij 5.";
			cin >> powrot;
			if (powrot == 5) {
				goto poczatek;
			}
			if (powrot != 5)//naprwaiÊ zapÍtlanie siÍ dla litter
			{
				while (true) {
					cout << "Zakonczyc program mozesz z menu." << endl;

					cout << "Aby powrocic do menu nacisnij 5.";
					cin >> powrot;
					if (powrot == 5) {
						goto poczatek;
					}
				}

			}


		}
		if (wybor == "2") {
			system("cls");
			string line, line2, Miasto1, Miasto2;

			ifstream inputFile("PlikèrÛd≥owy.csv");
			bool found = false;


			while (!found) {
				cout << "Wprowadz miasto z ktorego budujesz droge: ";
				getline(cin, Miasto1);
				Miasto1 = zamianawielkosciliter(Miasto1);

				if (Miasto1.find_first_not_of("0123456789") == string::npos) {
					cout << "Nie mozesz wprowadzic liczby jako nazwy miasta." << endl;
					continue;
				}
				inputFile.clear();
				inputFile.seekg(0, ios::beg);

				while (getline(inputFile, line)) {
					if (line.find(Miasto1) != string::npos) {             //Sprawdzanie czy s≥owo wpisane jest w pliku(dla miasta 1)
						cout << line << endl;
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Blad nazwy miasta." << endl;
				}
			}

			stringstream dublezawarte(line);
			string temp;
			vector<int> numery;
			while (getline(dublezawarte, temp, ' ')) {               //wpisywanie numerÛw przy s≥owie do tablic(dla miasta 1)
				stringstream zamiana(temp);
				int num;
				zamiana >> num;
				if (num > 0)
				{

					auto it = find(numery.begin(), numery.end(), num);          //usÛwanie zdublowanych cyfr(dla miasta 1)
					if (it == numery.end()) {
						numery.insert(it, num);
					}
				}
			}
			for (int i : numery) {
				cout << i << endl;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			bool found2 = false;
			while (!found2) {
				cout << "Wprowadz miasto do ktorego budujesz droge: ";
				getline(cin, Miasto2);
				Miasto2 = zamianawielkosciliter(Miasto2);

				if (Miasto2.find_first_not_of("0123456789") == string::npos) {
					cout << "Nie mozesz wprowadzic liczby jako nazwy miasta" << endl;
					continue;
				}
				inputFile.clear();                                           // zaczyna odpoczπtku czytaÊ plik   
				inputFile.seekg(0, ios::beg);

				while (getline(inputFile, line2)) {
					if (line2.find(Miasto2) != string::npos) {             //Sprawdzanie czy s≥owo wpisane jest w pliku(dla miasta 2)
						cout << line2 << endl;
						found2 = true;
						break;
					}
				}
				if (!found2) {
					cout << "Blad nazwy miasta." << endl;
				}
			}

			stringstream dublezawarte2(line2);
			string temp2;
			vector<int> numery2;
			while (getline(dublezawarte2, temp2, ' ')) {               //wpisywanie numerÛw przy s≥owie do tablic(dla miasta 2)
				stringstream zamiana2(temp2);
				int num2;
				zamiana2 >> num2;
				if (num2 > 0)
				{

					auto it2 = find(numery2.begin(), numery2.end(), num2);          //usÛwanie zdublowanych cyfr(dla miasta 2)
					if (it2 == numery2.end()) {
						numery2.insert(it2, num2);
					}
				}
			}
			for (int i : numery2) {
				cout << i << endl;
			}
			inputFile.close();




			//////
			int suma = 0;
			for (int i = 0; i < 2; i++) {                                   //odejmowanie wspÛ≥øÍdnych geograficznych
				int rÛønica = numery[i] - numery2[i];
				int kwadrat = pow(rÛønica, 2);                                          //potÍgowanie 
				suma += kwadrat;

			}
			int odleg≥oúÊ = sqrt(suma);
			cout << "Koszt budowy drogi z miasta " << Miasto1 << " do miasta " << Miasto2 << " wyniesie: " << odleg≥oúÊ << endl;
			cout << "Czy chcesz zbudowac droge? ";
			string Taklubnie;
			cin >> Taklubnie;
			Taklubnie = zamianawielkosciliter(Taklubnie);
			if (Taklubnie == "Tak") {
				string szukanielini;
				bool czyistnieje = false;
				ifstream plikzapisu("plikzaspizu.cvs");
				while (getline(plikzapisu, szukanielini)) {
					if (szukanielini.find(Miasto1 + " " + Miasto2) != string::npos || szukanielini.find(Miasto2 + " " + Miasto1) != string::npos) {
						czyistnieje = true;
						cout << "Polaczenie juz istnieje." << endl;
						break;
					}

				}
				plikzapisu.close();
				if (!czyistnieje) {
					cout << "Droga zostala zbudowana i zapisana." << endl;
					ofstream plikzapisu;
					plikzapisu.open("plikzaspizu.cvs", ios::out | ios::app);
					plikzapisu << Miasto1 << " " << Miasto2 << " " << odleg≥oúÊ << endl;// nadpisuje linijki
					plikzapisu.close();
				}





			}
			cout << "Aby powrocic do menu nacisnij 5.";
			cin >> powrot;
			if (powrot == 5) {
				goto poczatek;
			}
			if (powrot != 5)//naprwaiÊ zapÍtlanie siÍ dla litter
			{
				while (true) {
					cout << "Zakonczyc program mozesz z menu." << endl;

					cout << "Aby powrocic do menu nacisnij 5.";
					cin >> powrot;
					if (powrot == 5) {
						goto poczatek;
					}
				}

			}




		}
		if (wybor == "3") {
			system("cls");
			string linia4;
			ifstream plikzapisu("plikzaspizu.cvs");
			if (plikzapisu.is_open()) {
				while (getline(plikzapisu, linia4))
				{
					int bezliczb = linia4.find_first_of("0123456789");
					if (bezliczb != string::npos)
					{
						linia4 = linia4.substr(0, bezliczb);
					}
					cout << linia4 << endl;
				}
			}
			if (!plikzapisu.is_open())
			{
				cout << "Nie mozna otworzyc pliku." << endl;
			}
			plikzapisu.close();
			cout << "Aby powrocic do menu nacisnij 5.";
			cin >> powrot;
			if (powrot == 5) {
				goto poczatek;
			}
			if(powrot!=5)//naprwaiÊ zapÍtlanie siÍ dla litter
			{
				while (true) {
					cout << "Zakonczyc program mozesz z menu." << endl;

					cout << "Aby powrocic do menu nacisnij 5.";
					cin >> powrot;
					if (powrot == 5) {
						goto poczatek;
					}
				}
				
			}
		}
		if (wybor == "4") {
			ofstream plikzapisu("plikzaspizu.cvs", ofstream::out | ofstream::trunc);//czyúci plik z trasami
			if (plikzapisu.is_open()) {
				plikzapisu.close();
			}
			else {
				cout << "Nie moøna otworzyÊ pliku.";
			}
			cout << "Aby powrocic do menu nacisnij 5.";
			cin >> powrot;
			if (powrot == 5) {
				goto poczatek;
			}
			if (powrot != 5)//naprwaiÊ zapÍtlanie siÍ dla litter
			{
				while (true) {
					cout << "Zakonczyc program mozesz z menu." << endl;

					cout << "Aby powrocic do menu nacisnij 5.";
					cin >> powrot;
					if (powrot == 5) {
						goto poczatek;
					}
				}

			}
		}
		if (wybor == "5") {
			return 0;
		}
		else {
			goto poczatek;
		}
		

















	}







		
}