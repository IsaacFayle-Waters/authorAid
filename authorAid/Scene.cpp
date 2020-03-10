//General functions relating to the scene. Getters/setters.
#include "Scene.h"

Scene::Scene() = default;
Scene::Scene(std::string location, std::string timeAndOrDate,
	std::string sceneName, std::string genralDescription,
	int sceneNumber)
{
	setLocation(location);
	setTimeAndOrDate(timeAndOrDate);
	setSceneName(sceneName);
	setGenralDescription(genralDescription);
	setSceneNumber(sceneNumber);
	
};

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

void Scene::setNotes(std::string notes)
{
	this->notes = notes;
}

void Scene::setSceneNumber(int sceneNumber)
{
	this->sceneNumber = sceneNumber;
}
void Scene::setCharacters(Character character)
{
	this->characters.push_back(character);
	this->numberOfCharacters += 1;
};
std::vector<Character> Scene::getCharacterList()
{	
	return characters;
}
void Scene::setGenralDescription(std::string genralDescription)
{
	this->generalDescription = genralDescription;
};
