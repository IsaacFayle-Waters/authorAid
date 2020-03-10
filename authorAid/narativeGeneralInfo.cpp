#include "narativeGeneralInfo.h"

NarativeGeneralInfo::NarativeGeneralInfo() = default;

NarativeGeneralInfo::NarativeGeneralInfo(std::string title, std::string setting, std::string genre, std::string genralDescription)
{
	setTitle(title);
	setSetting(setting);
	setGenre(genre);
	setGeneralDescription(genralDescription);
}


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
	this->numberOfChapters += 1;
}
std::vector<Chapter> NarativeGeneralInfo::getChapters()
{
	return chapter;
}
;
