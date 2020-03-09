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

void printSceneInfo(Scene scene);
void printCharacterInfo(Character character);

//TODO SORT OUT Db OR JSON EARLY; CURRENT GETTERS AND SETTER RELY ON A METHOD THAT
//WON'T BE USED LATER. Causes issues.
//Note possibly better to handle all of thisl with a matrix of some sort? 0,1?

//TODO some test functions
int main() {
	//Create Characters
	Character c1;
	Character c2;
	Character c3("Dr.Bamboo", 77, "A nice old doctor, retired now. Enjoys tending to his garden.",
		"Execution of ingrates", "Man");
	Character Tom("Tom", 44, "Beer beast", "Create new beery world order", "bloke");
	Character a1("Mick", 55, "Nice enough, but... ", "Stealing and love", "Chromeman");
	Character a2("Nan", 700, "An old nan", "Getting blood out of the carpet", "Serpent");
	//Set Some Names and ages
	c1.setCharacterName("Mark");
	c1.setCharacterAge(6);
	c1.setGender("Boy");
	c1.setMotive("Chrisps");

	c2.setCharacterName("Babdoo");
	c2.setCharacterAge(13);
	c2.setGender("Female");
	c2.setDescription("Teenage girl");

	
	//Create a scene (Uh oh!)//
	Scene sceneOne;
	Scene sceneTwo("Nan's car", "A bit later", "Escape.", "Dr.Bamboo legs it", 2);
	Scene sceneThree("Nan's Garden", "Thursday", "Conclusions in RED!", "Only one person died", 3);
	sceneOne.setLocation("Nan's House");
	sceneOne.setSceneName("Dr. Bamboo kills two people.");
	sceneOne.setTimeAndOrDate("A Wednesday");
	sceneOne.setSceneNumber(1);

	//Link characters to the scene
	sceneOne.setCharacters(c1);
	sceneOne.setCharacters(c2);
	sceneOne.setCharacters(c3);
	sceneOne.setCharacters(Tom);
	sceneOne.setCharacters(a1);
	
	sceneTwo.setCharacters(c3);
	
	sceneThree.setCharacters(a2);
	sceneThree.setCharacters(c1);
	sceneThree.setCharacters(c2);
	sceneThree.setCharacters(Tom);

	
	printCharacterInfo(Tom);
	printSceneInfo(sceneOne);
	printSceneInfo(sceneTwo);
	printSceneInfo(sceneThree);
	
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

void printSceneInfo(Scene scene)
{
	//General information about the scene, from Scene.
	std::cout <<
		"Scene: " << scene.getSceneNumber() << std::endl <<
		"Location: " << scene.getLocation() << std::endl <<
		"Name of scene: " << scene.getSceneName() << std::endl <<
		"Time/date/etc: " << scene.getTimeAndOrDate() << std::endl <<
		"What happened?: " << scene.getGeneralDescription() << std::endl;
	
	//Characters displayed following being Linked to a scene
	std::cout << "\nCharacters who apear in this scene:\n\n";
	int numCharacters = scene.getCharacterList().size();
	if (numCharacters != 0) {
		for (int i = 0; i < numCharacters; i++) {
			std::cout <<
				"Name of Character " << i + 1 << ": " <<
				scene.getCharacterList().at(i).getName() <<
				" Aged: " << scene.getCharacterList().at(i).getCharacterAge() << std::endl <<
				"\nWho can be described as: " << scene.getCharacterList().at(i).getDescription() << std::endl <<
				"Who's motive seems to be: " <<scene.getCharacterList().at(i).getMotive() << std::endl <<
				scene.getCharacterList().at(i).getName() << " is a " << scene.getCharacterList().at(i).getGender() <<
				std::endl << std::endl;
		}
	}
	else {
		std::cout << "No characters in this Scene." << std::endl;
	}
}

void printCharacterInfo(Character character)
{
	std::cout << character.getName() << "'s details." << std::endl <<
		"Age: " << character.getCharacterAge() << std::endl <<
		"Description:  " << character.getDescription() << std::endl <<
		"Motive: " << character.getMotive() << std::endl <<
		"Gender: " << character.getGender() << std::endl << std::endl;
}

