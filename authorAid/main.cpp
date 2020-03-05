#include <iostream>
#include "Scene.h"
#include "Character.h"
#include <string>
#include <vector>
int main() {
	Character c1;
	Character c2;
	Character c3;
	
	c1.setCharacterName("Mark");
	c2.setCharacterName("babdoo");
	c3.setCharacterName("Dr.Bamboo");

	Scene sceneOne;
	sceneOne.setLocation("Nans House");
	sceneOne.setSceneName("Dr. Bamboo kills two people.");
	sceneOne.setTimeAndOrDate("A Wednesday");
	sceneOne.setSceneNumber(1);
	
	sceneOne.setCharacters(c1);
	sceneOne.setCharacters(c2);
	sceneOne.setCharacters(c3);

	std::cout << 
		"Scene/chapter: " << sceneOne.getSceneNumber() << std::endl <<
		"Location: " << sceneOne.getLocation() << std::endl << 
		"Name of scene: " << sceneOne.getSceneName() << std::endl <<
	    "Time/date/etc: " << sceneOne.getTimeAndOrDate() << std::endl;
	
	int numCharacters = sceneOne.getCharacterList().size();
	for (int i = 0; i < numCharacters; i++) {

		std::cout << "Name of Character " << i + 1 << ". " <<
			sceneOne.getCharacterList().at(i).getName() << std::endl;
	}
	//Hmm

return 0;
}