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
	std::string location;
	std::string timeAndOrDate;
	std::string sceneName;
	int sceneNumber;
	std::vector <Character> characters;
	/*void setLocation(std::string location);
	void setTimeAndOrDate(std::string timeAndOrDate);
	void setSceneName(std::string sceneName);
	void setSceneNumber(std::string sceneNumber);
	*/
public:
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

};
#endif