//General Character functions
#include "Character.h"

Character::Character() = default;
Character::Character(std::string name, int age, std::string description,
	std::string motive, std::string gender)
{
	setCharacterName(name);
	setCharacterAge(age);
	setDescription(description);
	setMotive(motive);
	setGender(gender);
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
}
void Character::setGender(std::string gender)
{
	this->gender = gender;
}
;
