#pragma once
#ifndef  CHARACTER_H
#define CHARACTER_H
#include <string>


class Character
{
private: 
	std::string name = "Unknown";
public:
	Character();
	Character(std::string name);
	void setCharacterName(std::string name = "Unknown");
	std::string getName();

};

#endif