#include "Episode.h"
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;


Episode::Episode()
	:number(""), germanTitle(""),englishTitle(""), description("")
{
}


Episode::Episode(std::string nr, std::string ger, std::string eng, std::string des, const vector<std::string>& c )
	:number(nr), germanTitle(ger), englishTitle(eng), description(des), characters(c)
{
}


string Episode::getFlashback() const {

	string border1 = "<FLASHBACK> ";
	string border2 = "</FLASHBACK>";
	string temp = "";
	int  firstindex = 0, secondindex = 0;

	while (( firstindex = description.find(border1, firstindex)) != string::npos && 
		(secondindex = description.find(border2, secondindex)) != string::npos) {

		int length = secondindex - firstindex;

		temp += description.substr(firstindex + border1.length(), length - border2.length()) + "\n\n";

		firstindex += border1.length() ;
		secondindex += border2.length();

	}

	return temp;
}

string Episode::getFrequentWords() const {
	stringstream flashback( getFlashback());
	vector< pair<int, string> > words;
	
	string word;
	while (flashback >> word) {
		vector<pair<int, string> >::iterator i;

		if ((i = find_if(words.begin(), words.end(), [ &word ](const pair<int, string> & p ) {
			return word == p.second;
			})) != words.end()){

				++i->first;
		}
		else {
			words.push_back(pair<int, string> (1, word));
		}
	}

	sort(words.begin(), words.end(), [](const pair<int, string>& p1, const pair<int, string>& p2) {
		if (p1.first == p2.first) {
			return  p1.second > p2.second;
		}
		else{
			return p1.first > p2.first;
		}
		});

	stringstream out;
	vector<pair<int, string> >::iterator i = words.begin();

	for (i; i < words.begin() + 15; i++) {
		out << i->first << " " << i->second << endl;
	}

	out << endl;

	return out.str();

}


string Episode::getMainCharacters() const {
	string flashback = getFlashback();
	vector<string> main_characters;

	for (auto& person : characters) {
		int index = 0;
		int number = 0;

		while ((index = flashback.find(person, index)) != string::npos) {
			number++;
			index += person.length();
			if (number == 5) {
				main_characters.push_back(person);
				break;
			}
		}
	}

		stringstream out;

		out << setw(10) << left << number << setw(25) << germanTitle;

		if (main_characters.empty()) {
			out << "keine spezielle";
		}
		else {
			for (size_t i = 0; i < main_characters.size(); i++) {
				out << main_characters[i];
				if (i < main_characters.size() - 1) out << ", ";
			}
		}

		out << endl;

		return out.str();

}