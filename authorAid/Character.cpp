#include "Character.h"

Character::Character() = default;


Character::Character(std::string name = "Unknown")
{
	setCharacterName(name);
};
void Character::setCharacterName(std::string name)
{
	this->name = name;
};

std::string Character::getName()
{
	return name;
};
