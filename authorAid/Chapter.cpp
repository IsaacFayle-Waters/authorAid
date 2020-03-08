#include "Chapter.h"

Chapter::Chapter() = default;


void Chapter::setChapterNumber(int chapterNumber)
{
	this->chapterNumber = chapterNumber;
}

void Chapter::setScenes(Scene scenes)
{
	this->scenes.push_back(scenes);
}
std::vector<Scene> Chapter::getSceneList()
{
	return scenes;
}
;


