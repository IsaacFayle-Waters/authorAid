//The aim is to build a flexible app that alows a user to freely keep track of their creations. For example,
//a user may just feel like jotting down some details about a character, but not know their name, age, 
//or what story the character belongs to yet. Similarly a scene may be imagine, without characters, etc. 
#include <iostream>
#include "Scene.h"
#include "Character.h"
#include "narativeGeneralInfo.h"
#include "Chapter.h"
#include <string>
#include <vector>


//TODO SORT OUT Db OR JSON EARLY; CURRENT GETTERS AND SETTER RELY ON A METHOD THAT
//WON'T BE USED LATER. Causes issues.

//TODO some test functions
int main() {
	//Create Characters
	Character c1;
	Character c2;
	Character c3;
	Character Tom;
	//Set Their Names
	c1.setCharacterName("Mark");
	c2.setCharacterName("Babdoo");
	c3.setCharacterName("Dr.Bamboo");
	//Tom.setCharacterName("Tom");

	Tom.setCharacterAge(44);
	//std::cout << Tom.getCharacterAge();
	
	//Create a scene (Uh oh!)//
	Scene sceneOne;
	Scene sceneTwo;
	Scene sceneThree;
	sceneOne.setLocation("Nans House");
	sceneOne.setSceneName("Dr. Bamboo kills two people.");
	sceneOne.setTimeAndOrDate("A Wednesday");
	sceneOne.setSceneNumber(1);
	//Link characters to the scene
	sceneOne.setCharacters(c1);
	sceneOne.setCharacters(c2);
	sceneOne.setCharacters(c3);
	sceneOne.setCharacters(Tom);
	
	//temp test
	std::cout << "Initial description: "<<sceneOne.getGeneralDescription() << std::endl;
	sceneOne.setGenralDescription("Really quite an awful scene. Loads of bad acting and needless violence");
	std::cout << sceneOne.getGeneralDescription() << std::endl;

	//Temp test
	std::cout << Tom.getDescription() << std::endl;
	Tom.setDescription("Eager to please, but rarely does");
	std::cout << "Tom: " << Tom.getDescription() << std::endl;

	//Temp test
	std::cout << Tom.getMotive() << std::endl;
	Tom.setMotive("To avoid Dr.Bamboo");
	std::cout << "Tom: " << Tom.getMotive() << std::endl;
	
	//General Scene output
	std::cout << 
		"Scene/chapter: " << sceneOne.getSceneNumber() << std::endl <<
		"Location: " << sceneOne.getLocation() << std::endl << 
		"Name of scene: " << sceneOne.getSceneName() << std::endl <<
	    "Time/date/etc: " << sceneOne.getTimeAndOrDate() << std::endl;
	//Characters displayed following being Linked to a scene
	int numCharacters = sceneOne.getCharacterList().size();
	for (int i = 0; i < numCharacters; i++) {
		std::cout << 
			"Name of Character " << i + 1 << ". " <<
			sceneOne.getCharacterList().at(i).getName() << 
			" Aged: " << sceneOne.getCharacterList().at(i).getCharacterAge() << 
			std::endl;
	}
	
	std::cout << std::endl << std::endl;

	NarativeGeneralInfo nar1;
	std::cout << std::endl << nar1.getTitle();
	std::cout << std::endl << nar1.getSetting();
	std::cout << std::endl << nar1.getGeneralDescription();

	nar1.setTitle("Bad day at Nan's");
	nar1.setSetting("Nan's and Her Basement");
	nar1.setGeneralDescription("Book about a murder spree by a bad Dr.");

	std::cout << std::endl << nar1.getTitle();
	std::cout << std::endl << nar1.getSetting();
	std::cout << std::endl << nar1.getGeneralDescription();
	std::cout << std::endl;

	Chapter chap1;
	chap1.setScenes(sceneOne);
	chap1.setScenes(sceneTwo);
	chap1.setScenes(sceneThree);

	int chapSize = chap1.getSceneList().size();
	for (int i = 0; i < chapSize; i++) {
		std::cout << chap1.getSceneList().at(i).getSceneName() << std::endl;
	}
	//Access first character name, from first scene in Chapter.
	std::cout << chap1.getSceneList().at(0).getCharacterList().at(0).getName();

return 0;
}