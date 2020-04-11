//Acts to bind all chapters in a narrative with a few general details
//Of the story. In this way, it allows more than one story 
//in a particular world.
#pragma once
#ifndef NARATIVE_GEN_INFO_H
#define NARATIVE_GEN_INFO_H
#include <string>
#include <vector>
#include "World.h"
#include "Chapter.h"
class NarativeGeneralInfo: public World
{
private:
    std::string title = "Unknown Title";
    std::string setting = "Unknown Setting";
    std::string genre = "Unknown Genre";
    //std::string genralDescription = "Unknown Narative Description";
    std::vector <Chapter> chapter;
    int numberOfChapters = 0;
    //std::string notes = "No notes";
    //array of Other characters linked to 'this' character. Possibly
public:
    NarativeGeneralInfo();
    ~NarativeGeneralInfo();
    NarativeGeneralInfo(std::string title, std::string setting,
        std::string genre, std::string genralDescription);
    
    void setTitle(std::string title);
    std::string getTitle() { return title; };
    
    void setSetting(std::string setting);
    std::string getSetting() { return setting; };

    void setGenre(std::string genre);
    std::string getGenre() { return genre; };

    void setChapter(Chapter chapter);
    void removeChapterFromList(int elementIndex);
    std::vector<Chapter> getChapters();
    //rem
    int getNumberOfChapters() { return numberOfChapters; };
    void setNGIFromDb(std::vector <std::string> dbreturn);
};

#endif