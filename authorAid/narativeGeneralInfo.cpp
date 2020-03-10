#include "narativeGeneralInfo.h"

void NarativeGeneralInfo::setTitle(std::string title)
{
	this->title = title;
}
void NarativeGeneralInfo::setSetting(std::string setting)
{
	this->setting = setting;
}
void NarativeGeneralInfo::setGenre(std::string genre)
{
	this->genre = genre;
}
void NarativeGeneralInfo::setGeneralDescription(std::string generalDescription)
{
	this->genralDescription = generalDescription;
}
void NarativeGeneralInfo::setChapter(Chapter chapter)
{
	this->chapter.push_back(chapter);
}
std::vector<Chapter> NarativeGeneralInfo::getChapters()
{
	return chapter;
}
;
