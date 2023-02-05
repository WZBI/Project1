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
	transform(output.begin(), output.end(), output.begin(), ::tolower);             //zamiana wielkiej litery na ma³a
	output[0] = toupper(output[0]);
	return output;
}

int main()
{



	string wybur;
	while (true) {
		cout << "1.Podroz\n";
		cout << "2.Budowa drogi\n";
		cout << "3.Wybudowane drogi\n";
		cin >> wybur;
		if (wybur == "1") {
			system("cls");
			string Miastowy, Miastodo, line3, line4;

			cout << "Do ktorego miasta chcesz sie udac: ";
			Miastodo = zamianawielkosciliter(Miastodo);
			cin >> Miastodo;
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
					if (line3.find(Miastowy) != string::npos) {             //Sprawdzanie czy s³owo wpisane jest w pliku(dla miasta 1)
						cout << line3 << endl;
						czywybudowane = true;
						break;
					}
				}
				if (!czywybudowane) {
					cout << "Brak polaczenia drogowego miedzy miastami." << endl;
				}
			}
			
			
		}
		if (wybur == "2") {
			system("cls");
			string line, line2, Miasto1, Miasto2;

			ifstream inputFile("B:\\visual\\Project\\Plikród³owy.csv");
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
					if (line.find(Miasto1) != string::npos) {             //Sprawdzanie czy s³owo wpisane jest w pliku(dla miasta 1)
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
			while (getline(dublezawarte, temp, ' ')) {               //wpisywanie numerów przy s³owie do tablic(dla miasta 1)
				stringstream zamiana(temp);
				int num;
				zamiana >> num;
				if (num > 0)
				{

					auto it = find(numery.begin(), numery.end(), num);          //usówanie zdublowanych cyfr(dla miasta 1)
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
				inputFile.clear();                                           // zaczyna odpocz¹tku czytaæ plik   
				inputFile.seekg(0, ios::beg);

				while (getline(inputFile, line2)) {
					if (line2.find(Miasto2) != string::npos) {             //Sprawdzanie czy s³owo wpisane jest w pliku(dla miasta 2)
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
			while (getline(dublezawarte2, temp2, ' ')) {               //wpisywanie numerów przy s³owie do tablic(dla miasta 2)
				stringstream zamiana2(temp2);
				int num2;
				zamiana2 >> num2;
				if (num2 > 0)
				{

					auto it2 = find(numery2.begin(), numery2.end(), num2);          //usówanie zdublowanych cyfr(dla miasta 2)
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
			for (int i = 0; i < 2; i++) {                                   //odejmowanie wspó³¿êdnych geograficznych
				int ró¿nica = numery[i] - numery2[i];
				int kwadrat = pow(ró¿nica, 2);                                          //potêgowanie 
				suma += kwadrat;

			}
			int odleg³oœæ = sqrt(suma);
			cout << "Koszt budowy drogi z miasta " << Miasto1 << " do miasta " << Miasto2 << " wyniesie: " << odleg³oœæ << endl;
			cout << "Czy chcesz zbudowac droge? ";
			string Taklubnie;
			cin >> Taklubnie;
			Taklubnie = zamianawielkosciliter(Taklubnie);
			if (Taklubnie == "Tak") {
				cout << "Droga zostala zbudowana i zapisana." << endl; 
				ofstream plikzapisu;
				plikzapisu.open("plikzaspizu.cvs");
				plikzapisu << Miasto1 << " " << Miasto2 << " " << odleg³oœæ << endl;// nadpisuje linijki
				plikzapisu.close();
			}
			else {
				return 0;
			}
			



		}
		//if (wybur == "3") {
			//wczytaj z pliku wybudowane drogi
		//}
		
























		}
	}