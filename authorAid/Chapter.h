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
	//std::string notes = "No notes";

public:
	Chapter();
	~Chapter();
	Chapter(int chapterNumber, std::string chapterName="");

	void setChapterNumber(int chapterNumber);
	int getChapterNumber() { return chapterNumber; };

	//void setChapterName(std::string chapterName);
	//std::string getChapterName() { return name; };

	void setScenes(Scene scenes);
	std::vector<Scene> getSceneList();

	int getNumberOfScenes() { return numberOfScenes; };
	
	//void setNotes(std::string notes);
	//std::string getNotes() { return notes; };
};

