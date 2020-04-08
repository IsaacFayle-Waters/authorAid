#pragma once
#ifndef  CHARACTER_H
#define CHARACTER_H
#include "World.h"
#include <string>
#include <vector>
#include <sstream>

class Character: public World
{
private: 
	int age = - 1;
	std::string motive = "Unknown Motive";
	std::string gender = "Unknown Gender";
	
public:	
	Character();
	~Character();
	Character(std::string name, int age, std::string description, 
				std::string motive, std::string gender);

	void setCharacterAge(int age);
	int getCharacterAge() { return age; };

	void setMotive(std::string motive);
	std::string getMotive() { return motive; };

	void setGender(std::string gender);
	std::string getGender() { return gender; };
		
	void setCharacterFromDb(std::vector <std::string> dbreturn);
};

#endif