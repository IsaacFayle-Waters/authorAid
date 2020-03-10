//Acts to bind all chapters in a narrative with a few general details
//Of the story. In this way, it allows more than one story 
//in a particular world.
#pragma once
#ifndef NARATIVE_GEN_INFO_H
#define NARATIVE_GEN_INFO_H
#include <string>
#include <vector>
#include "Chapter.h"
class NarativeGeneralInfo
{
private:
    std::string title = "Unkown Title";
    std::string setting = "Unkown Setting";
    std::string genre = "Unkown Genre";
    std::string genralDescription = "Unkown Narative Description";
    std::vector <Chapter> chapter;
    int numberOfChapters = 0;
    //array of Other characters linked to 'this' character. Possibly
public:
    NarativeGeneralInfo();
    NarativeGeneralInfo(std::string title, std::string setting,
        std::string genre, std::string genralDescription);
    
    void setTitle(std::string title);
    std::string getTitle() { return title; };
    
    void setSetting(std::string setting);
    std::string getSetting() { return setting; };

    void setGenre(std::string genre);
    std::string getGenre() { return genre; };

    void setGeneralDescription(std::string generalDescription);
    std::string getGeneralDescription() { return genralDescription; };

    void setChapter(Chapter chapter);
    std::vector<Chapter> getChapters();

    int getNumberOfChapters() { return numberOfChapters; };

};

#endif