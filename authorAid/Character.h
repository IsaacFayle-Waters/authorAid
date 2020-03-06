#pragma once
#ifndef  CHARACTER_H
#define CHARACTER_H
#include <string>

class Character
{
private: 
	std::string name = "Unknown";
	int age = -1;
public:
	Character();
	Character(std::string name, int age);
	void setCharacterName(std::string name);
	std::string getName();

	void setCharacterAge(int age);
	int getCharacterAge();

};

#endif