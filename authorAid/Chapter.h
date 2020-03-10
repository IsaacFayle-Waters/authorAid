#pragma once
#include "Scene.h"
#include <string>
#include <vector>
class Chapter 
{
private:
	int chapterNumber = - 1;
	std::string chapterName = "";
	std::vector <Scene> scenes;
	int numberOfScenes = 0;

public:
	Chapter();
	Chapter(int chapterNumber, std::string chapterName="");

	void setChapterNumber(int chapterNumber);
	int getChapterNumber() { return chapterNumber; };

	void setChapterName(std::string chapterName);
	std::string getChapterName() { return chapterName; };

	void setScenes(Scene scenes);
	std::vector<Scene> getSceneList();

	int getNumberOfScenes() { return numberOfScenes; };
};

