//General Character functions
#include "Character.h"

Character::Character() = default;

Character::~Character()
{
}

Character::Character(std::string name, int age, std::string description,
	std::string motive, std::string gender)
{
	setName(name);
	setCharacterAge(age);
	setDescription(description);
	setMotive(motive);
	setGender(gender);
	
};
/*void Character::setCharacterName(std::string name)
{
	this->name = name;
};*/
void Character::setCharacterAge(int age)
{
	this->age = age;
};
/*void Character::setDescription(std::string description)
{
	this->description = description;
};*/
void Character::setMotive(std::string motive)
{
	this->motive = motive;
};
void Character::setGender(std::string gender)
{
	this->gender = gender;
};
/*void Character::setNotes(std::string notes)
{
	this->notes = notes;
};*/
void Character::setCharacterFromDb(std::vector<std::string> dbreturn)
{
	setName(dbreturn.at(1));
	if (dbreturn.at(2) != "NULL") {
		int id;
		std::string input = dbreturn.at(2);
		std::stringstream myStream(input);
		myStream >> id;
		
		int ageDb = id;//std::stoi(dbreturn.at(1));
		setCharacterAge(ageDb);
	}
	setDescription(dbreturn.at(3));
	setMotive(dbreturn.at(4));
	setGender(dbreturn.at(5));
	setNotes(dbreturn.at(6));
}
;
