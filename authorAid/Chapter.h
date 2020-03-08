#pragma once
#include "Scene.h"
#include <string>
#include <vector>
class Chapter 
{
private:
	int chapterNumber = - 1;
	std::vector <Scene> scenes;

public:
	Chapter();
	void setChapterNumber(int chapterNumber);
	int getChapterNumber() { return chapterNumber; };

	void setScenes(Scene scenes);
	std::vector<Scene> getSceneList();
};

