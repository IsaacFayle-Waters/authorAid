//General functions relating to the scene. Getters/setters.
#include "Scene.h"

Scene::Scene() = default;


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
	this->generalDescription = genralDescription;
}
;

std::string Scene::getLocation()
{
	return location;
};
