#include "Chapter.h"

Chapter::Chapter() = default;

Chapter::~Chapter()
{
};

Chapter::Chapter(int chapterNumber, std::string chapterName)
{
	setChapterNumber(chapterNumber);
	setName(chapterName);
};

void Chapter::setChapterNumber(int chapterNumber)
{
	this->chapterNumber = chapterNumber;
};

void Chapter::setScenes(Scene scenes)
{
	this->scenes.push_back(scenes);
	this->numberOfScenes += 1;
}
void Chapter::removeSceneFromList(int elementIndex)
{
	this->scenes.erase(scenes.begin() + elementIndex);
}
;
std::vector<Scene> Chapter::getSceneList()
{
	return scenes;
};
void Chapter::setChapterFromDb(std::vector<std::string> dbreturn)
{
//CHPTR_NUM, CHPTR_NAME, NUM_SCENES, GEN_DSCRPT, NOTES, EXISTS_BOOL
	std::string chaptNum = dbreturn.at(0), numScenes = dbreturn.at(2);
	
	setChapterNumber(convertToInt(chaptNum));
	setName(dbreturn.at(1));
	//???//
	this->numberOfScenes = convertToInt(numScenes);
	//???//
	setDescription(dbreturn.at(3));
	setNotes(dbreturn.at(4));
	setExistence();
};

;


