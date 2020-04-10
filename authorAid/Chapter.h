#pragma once
#include "World.h"
#include "Scene.h"
#include <string>
#include <vector>
class Chapter: public World 
{
private:
	int chapterNumber = - 1;
	std::string name = "";
	std::vector <Scene> scenes;
	int numberOfScenes = 0;

public:
	Chapter();
	~Chapter();
	Chapter(int chapterNumber, std::string chapterName="");

	void setChapterNumber(int chapterNumber);
	int getChapterNumber() { return chapterNumber; };
	
	void setScenes(Scene scenes);
	void removeSceneFromList(int elementIndex);
	std::vector<Scene> getSceneList();

	int getNumberOfScenes() { return numberOfScenes; };
	void setChapterFromDb(std::vector <std::string> dbreturn);
};

