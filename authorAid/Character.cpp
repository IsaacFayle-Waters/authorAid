//General Character functions
#include "Character.h"

Character::Character() = default;
//Charcater name intitially unknown
Character::Character(std::string name = "Unknown", int age = NULL)
{
	setCharacterName(name);
	setCharacterAge(age);
};
void Character::setCharacterName(std::string name)
{
	this->name = name;
};

std::string Character::getName()
{
	return name;
}
void Character::setCharacterAge(int age)
{
	this->age = age;
}
int Character::getCharacterAge()
{
	return age;
}
;
