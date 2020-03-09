#pragma once
//General description of a narrative. 
//Little more that what would be found on Amazon
//for example.
//UNTESTED, BUT SIMPLE.
#ifndef NARATIVE_GEN_INFO_H
#define NARATIVE_GEN_INFO_H
#include <string>
class NarativeGeneralInfo
{
private:
    std::string title = "Unkown Title";
    std::string setting = "Unkown Setting";
    std::string genre = "Unkown Genre";
    std::string genralDescription = "Unkown Narative Description";
    //List of Chapters// so chapter class to?
    //array of Other characters linked to 'this' character. Possibly
public:
    void setTitle(std::string title);
    std::string getTitle() { return title; };
    
    void setSetting(std::string setting);
    std::string getSetting() { return setting; };

    void setGenre(std::string genre);
    std::string getGenre() { return genre; };

    void setGeneralDescription(std::string generalDescription);
    std::string getGeneralDescription() { return genralDescription; };

};

#endif