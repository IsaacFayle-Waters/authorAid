//General functions relating to the scene. Getters/setters.
#include "Scene.h"

void Scene::setLocation(std::string location)
{
	this->location = location;
};

void Scene::setTimeAndOrDate(std::string timeAndOrDate)
{
	this->timeAndOrDate = timeAndOrDate;
};

void Scene::setSceneName(std::string sceneName)
{
	this->sceneName = sceneName;
};

void Scene::setSceneNumber(int sceneNumber)
{
	this->sceneNumber = sceneNumber;
}
void Scene::setCharacters(Character character)
{
	this->characters.push_back(character);
};
std::vector<Character> Scene::getCharacterList()
{	
	return characters;
}
void Scene::setGenralDescription(std::string genralDescription)
{
	this->genralDescription = genralDescription;
}
;

std::string Scene::getLocation()
{
	return location;
};
