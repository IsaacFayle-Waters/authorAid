#include "Chapter.h"

Chapter::Chapter() = default;

Chapter::Chapter(int chapterNumber)
{
	setChapterNumber(chapterNumber);
}


void Chapter::setChapterNumber(int chapterNumber)
{
	this->chapterNumber = chapterNumber;
}

void Chapter::setScenes(Scene scenes)
{
	this->scenes.push_back(scenes);
	this->numberOfScenes += 1;
}
std::vector<Scene> Chapter::getSceneList()
{
	return scenes;
}
;


