//Scenes of a chapter, or perhaps simply in and of themselves.
#pragma once
#ifndef SCENE_H
#define SCENE_H 

#include <string>
#include <vector>
#include "Character.h"
#include "World.h"

class Scene: public World
{
	
private:
	std::string location = "Unkown Location";
	std::string timeAndOrDate = "Unkown Temporal Space";
	//std::string sceneName = "Unkown Scene Name";
	//std::string generalDescription = "Unkown Scene Description";
	//std::string notes = "No notes";
	int sceneNumber = -1;
	std::vector <Character> characters;
	int numberOfCharacters = 0;

public:
	Scene();
	~Scene();
	Scene(std::string location, std::string timeAndOrDate, std::string sceneName,
		std::string genralDescription, int sceneNumber);
	void setLocation(std::string location);
	std::string getLocation() { return location; };

	void setTimeAndOrDate(std::string timeAndOrDate);
	std::string getTimeAndOrDate() { return timeAndOrDate; };

	//void setSceneName(std::string sceneName);
	//std::string getSceneName() { return sceneName; };

	//void setNotes(std::string notes);
	//std::string getNotes() { return notes; };

	void setSceneNumber(int sceneNumber);
	int getSceneNumber() { return sceneNumber; };

	void setCharacters(Character character);
	std::vector<Character> getCharacterList();

	//void setGenralDescription(std::string genralDescription);
	//std::string getGeneralDescription() { return generalDescription; };
	
	int getNumberOfCharacters() { return numberOfCharacters; };
};
#endif