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
void Character::setCharacterAge(int age)
{
	this->age = age;
};
void Character::setDescription(std::string description)
{
	this->description = description;
}
void Character::setMotive(std::string motive)
{
	this->motive = motive;
};
