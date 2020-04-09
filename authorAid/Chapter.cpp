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

/*void Chapter::setChapterName(std::string chapterName)
{
	this->name = chapterName;
};*/

void Chapter::setScenes(Scene scenes)
{
	this->scenes.push_back(scenes);
	this->numberOfScenes += 1;
};
std::vector<Scene> Chapter::getSceneList()
{
	return scenes;
};
/*void Chapter::setNotes(std::string notes)
{
	this->notes = notes;
}*/
;


