//The aim is to build a flexible app that alows a user to freely keep track of their creations. For example,
//a user may just feel like jotting down some details about a character, but not know their name, age, 
//or what story the character belongs to yet. Similarly a scene may be imagine, without characters, etc. 
#include <iostream>
#include "Scene.h"
#include "Character.h"
#include <string>
#include <vector>
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
	std::cout << Tom.getCharacterAge();
	
	//Create a scene (Uh oh!)//
	Scene sceneOne;
	sceneOne.setLocation("Nans House");
	sceneOne.setSceneName("Dr. Bamboo kills two people.");
	sceneOne.setTimeAndOrDate("A Wednesday");
	sceneOne.setSceneNumber(1);
	//Link characters to the scene
	sceneOne.setCharacters(c1);
	sceneOne.setCharacters(c2);
	sceneOne.setCharacters(c3);
	sceneOne.setCharacters(Tom);
	
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
	

return 0;
}