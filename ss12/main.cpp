#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include "Episode.h"

using namespace std;

int main() {

	setlocale(LC_ALL, "");
	ifstream inLostEpisode("Lost_Staffel_1.txt", ios::in);
	ifstream inCharacters("Hauptpersonen.txt", ios::in);

	if (!inLostEpisode) {
		cerr << "Datei kann nicht geoeffnet werden." << endl;
		exit(EXIT_FAILURE);
	}

	if (!inCharacters) {
		cerr << "Datei kann nicht geoeffnet werden." << endl;
		exit(EXIT_FAILURE);
	}

	vector<string> characters;
	string line;
	while (getline(inCharacters, line)) {
		characters.push_back(line);

	}
	inCharacters.close();


	map<string, Episode> episode;
	getline(inLostEpisode, line); //erste Zeile ignorieren
	while (!inLostEpisode.eof()) {
		string number, germanTitle, englishTitle, description;

		getline(inLostEpisode, number);
		number.erase(0, number.find(' ') + 1);  // nur Zahlen nehmen ohne "EPISODE"

		getline(inLostEpisode, germanTitle, '(');
		getline(inLostEpisode, englishTitle, ')');
		getline(inLostEpisode, description, '*');

		episode[number] = Episode(number, germanTitle, englishTitle, description, characters);
		getline(inLostEpisode, line); 
	}
	inLostEpisode.close();
	

	char menu;
	do {
		cout << "[1] Englische Episodentitel und Inhalt einer beliebigen Episode ausgeben" << endl
			 << "[2] Nur R�ckblicke einer beliebigen Episode ausgeben" << endl
			 << "[3] Die 15 h�ufigsten W�rter der R�ckblicke einer Episode ausgeben" << endl
			 << "[4] Hauptpersonen aller Episoden ausgeben" << endl << endl
			 << "[9] Programm beenden" << endl
			 << "Ihre Wahl: ";

		cin >> menu;
		string ep;

		switch (menu) {
		case '1':

			for (auto ep:episode) {
				cout << ep.second.getNumber() << "\t" << ep.second.getEnglishtitle() << endl;
			}
			do{
				cout << "Welche Episode m�chten Sie sehen? (1.01 - 1.25) " << endl;
				cin >> ep;

				if (episode.find(ep) == episode.end()) {
					cerr << "Episode existiert nicht. Bitte Eingabe wiederholen." << endl << endl;
				}
				else {
					cout << "Episode Nummer: " << episode[ep].getNumber() << endl
						<< "Deutscher Titel: " << episode[ep].getGermantitle() << endl
						<< "Englischer Titel: " << episode[ep].getEnglishtitle() << endl
						<< "Inhalt: " << episode[ep].getDescription() << endl;
				}
			} while (ep == "9");

			break;
		case '2':
			cout << " **** Nur R�ckblicke einer Episode ausgeben ****" << endl
				<< "Von welcher Episode sollen die R�ckblicke ausgegeben werden: ";
			cin >> ep;
			cout << endl << episode[ep].getFlashback();

			break;
		case '3':
			cout << " **** Die 15 h�ufigsten W�rter ausgeben ****" << endl
				<< "Von welcher Episode sollen die 15 h�ufigsten W�rter ausgegeben werden: ";
			cin >> ep;
			cout << endl << episode[ep].getFrequentWords();
			break;

		case '4':
			cout << " **** Hauptpersonen aller Episoden ausgeben ****" << endl
				<< setw(10)  << left << "Episode" << setw(25) << "Titel" << "Hauptperson (en)"
				<< endl;

			for (auto epi : episode) {
				cout << epi.second.getMainCharacters();
				 }

			break;
		case '9':
			break;

		default:
			cout << "Falsche Eingabe. Bitte noch einmal eingeben." << endl << endl;
			break;
		}

	} while (menu != '9');

	return 0;
}