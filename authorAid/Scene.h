#pragma once
#ifndef SCENE_H
#define SCENE_H 

#include <string>
#include <vector>
#include "Character.h"

class Scene
{
	//friend class Character;
private:
	std::string location = "Unkown Location";
	std::string timeAndOrDate = "Unkown Temporal Space";
	std::string sceneName = "Unkown Scene Name";
	std::string generalDescription = "Unkown Scene Description";
	int sceneNumber = -1;
	std::vector <Character> characters;

public:
	Scene();
	//Scene(std::string location, std::string timeAndOrDate, std::string sceneName,
		//std::string genralDescription);
	//TODO:Can be done either way, which is better? decide. Neater, but less maintainable?
	void setLocation(std::string location);
	std::string getLocation() /*{ return location; }*/;

	void setTimeAndOrDate(std::string timeAndOrDate);
	std::string getTimeAndOrDate() { return timeAndOrDate; };

	void setSceneName(std::string sceneName);
	std::string getSceneName() { return sceneName; };

	void setSceneNumber(int sceneNumber);
	int getSceneNumber() { return sceneNumber; };

	void setCharacters(Character character);
	std::vector<Character> getCharacterList();

	void setGenralDescription(std::string genralDescription);
	std::string getGeneralDescription() { return generalDescription; };
	
};
#endif