#include "World.h"
#include <vector>

void World::setName(std::string name)
{
	this->name = name;
}

void World::setDescription(std::string description)
{
	this->description = description;
}

void World::setNotes(std::string notes)
{
	this->notes = notes;
}

void World::setExistence()
{
	if (exists == false) {
		this->exists = true;
		std::cout << "Existence set to true" << std::endl;
	}
	else {
		std::cout << "Existence already true" << std::endl;
	}
}
void World::setRemovalID(int rem)
{
	this->removalID = rem;
}
/*void World::removeElementFromVector(std::vector <class cl> vec,int remSelect)
{
	vec().erase(remSelect);
}*/
;
