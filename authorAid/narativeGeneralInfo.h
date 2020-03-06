#pragma once
#ifndef NARATIVE_GEN_INFO_H
#define NARATIVE_GEN_INFO_H
#include <string>
class NarativeGeneralInfo
{
private:
    std::string title = "Unkown Title";
    std::string setting = "Unkown Setting";
    std::string genralDescription = "Unkown Narative Description";

public:
    void setTitle(std::string title);
    std::string getTitle() { return title; };
    
    void setSetting(std::string setting);
    std::string getSetting() { return setting; };

    void setGeneralDescription(std::string generalDescription);
    std::string getGeneralDescription() { return genralDescription; };

};

#endif