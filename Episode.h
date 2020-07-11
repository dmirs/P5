#pragma once
#include <string>
#include <vector>

class Episode
{
public:
	Episode();
	Episode(std::string, std::string, std::string, std::string, const std::vector<std::string> & );
	std::string getGermantitle() const { return germanTitle; };
	std::string getEnglishtitle() const { return englishTitle; };
	std::string getNumber() const { return number; };
	std::string getDescription() const { return description;  };
	std::string getFlashback() const;
	std::string getFrequentWords()const;
	std::string getMainCharacters()const;

private:
	std::string germanTitle;
	std::string englishTitle;
	std::string number;
	std::string description;
	std::vector<std::string> characters;
};

