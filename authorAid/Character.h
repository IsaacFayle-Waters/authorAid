#pragma once
#ifndef  CHARACTER_H
#define CHARACTER_H
#include <string>

class Character
{
private: 
	std::string name = "Unknown Name";
	int age = - 1;
	std::string description = "Unknown Character Description";
	std::string motive = "Unknown Motive";
public:	
	Character();
	Character(std::string name, int age);
	
	void setCharacterName(std::string name);
	std::string getName() { return name; };

	void setCharacterAge(int age);
	int getCharacterAge() { return age; };

	void setDescription(std::string description);
	std::string getDescription() { return description; };

	void setMotive(std::string motive);
	std::string getMotive() { return motive; };
};

#endif