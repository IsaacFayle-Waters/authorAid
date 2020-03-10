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

void printSceneInfo(Scene scene, bool charInfoOn);
void printCharacterInfo(Character character);
void printChapterInfo(Chapter chapter);
void printNarativeGeneralInfo(NarativeGeneralInfo ngi);

//TODO SORT OUT Db, sql, JSON EARLY.
//TODO GUI
//Note possibly better to handle all of thisl with a matrix of some sort? 0,1?

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

	//Evidence 'notes' working.
	a1.setNotes("Always, he gets into the fighting on tarmac over beer.\n"
		"'Why are you like this?' is the sort of thing his wife asks.\n"
		"'My Dyspraxia drives me to it, NOW LEAVE ME!' would be a typical reply.");
	
	//Creating scenes (Uh oh!)
	Scene sceneOne;
	Scene sceneTwo("Nan's car", "A bit later", "Escape.", "Dr.Bamboo legs it", 2);
	Scene sceneThree("Nan's Garden", "Thursday", "Conclusions in RED!", "Only one person died", 3);
	Scene sceneFour("Hell", "No!", "Dr Dr Dr", "dsgGGGGGfyes", 4);
	Scene sceneFive("Nan's House", "Friday", "End now", "Nan is watching TV, in her chair", 5);
	sceneFive.setCharacters(a2);
	sceneFive.setCharacters(c1);
	sceneFive.setNotes("Nan is pleased with her week. Everything went as she had hoped, and now the one show is on.");
	sceneThree.setNotes("This is not the end.");
	sceneOne.setLocation("Nan's House");
	sceneOne.setSceneName("Dr. Bamboo kills two people.");
	sceneOne.setTimeAndOrDate("A Wednesday");
	sceneOne.setSceneNumber(1);

	//Link characters to the scenes
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

	//Chapters 
	Chapter chap1(1,"Etchings of FEAR!");
	Chapter chap2(2, "Epilogue... OF FEAR!");
	chap1.setScenes(sceneOne);
	chap1.setScenes(sceneTwo);
	chap1.setScenes(sceneThree);
	chap2.setScenes(sceneFour);
	chap2.setScenes(sceneFive);

	//Set Narrative General Info
	NarativeGeneralInfo ngi1;
	NarativeGeneralInfo ngi2;
	ngi1.setTitle("Bad day at Nan's");
	ngi1.setSetting("Nan's house, car, and garden");
	ngi1.setGenre("Romance");
	ngi1.setGeneralDescription("Book about a murder spree by a bad Dr.");

	//Include chapters
	ngi1.setChapter(chap1);
	ngi1.setChapter(chap2);

	//Display Narrative info, Chapters, Scenes, and a character.
	printNarativeGeneralInfo(ngi1);

	printChapterInfo(chap1);

	printSceneInfo(sceneOne,false);
	printSceneInfo(sceneTwo,true);
	printSceneInfo(sceneThree,false);

	printChapterInfo(chap2);
	printSceneInfo(sceneFour, false);
	printSceneInfo(sceneFive, true);
	
	printCharacterInfo(a1);
	//Example of value passing through classes
	printNarativeGeneralInfo(ngi2);
	

	
return 0;
}

void printSceneInfo(Scene scene, bool charInfoOn)
{
	//General information about the scene, from Scene.
	std::cout <<
		"Scene: " << scene.getSceneNumber() << std::endl <<
		"Location: " << scene.getLocation() << std::endl <<
		"Number of Characters: " << scene.getNumberOfCharacters() << std::endl <<
		"Name of scene: " << scene.getSceneName() << std::endl <<
		"Time/date/etc: " << scene.getTimeAndOrDate() << std::endl <<
		"What happened?: " << scene.getGeneralDescription() << std::endl <<
		"Notes: " << scene.getNotes() << std::endl << std::endl;
	//Characters displayed following being Linked to a scene
	if (charInfoOn == true) {
		std::cout << "Characters who apeer in this scene:\n\n";
		int numCharacters = scene.getCharacterList().size();
		if (numCharacters != 0) {
			for (int i = 0; i < numCharacters; i++) {
				std::cout <<
					"Name of Character " << i + 1 << ": " <<
					scene.getCharacterList().at(i).getName() <<
					" Aged: " << scene.getCharacterList().at(i).getCharacterAge() << std::endl <<
					"\nWho can be described as: " << scene.getCharacterList().at(i).getDescription() << std::endl <<
					"Who's motive seems to be: " << scene.getCharacterList().at(i).getMotive() << std::endl <<
					scene.getCharacterList().at(i).getName() << " is a " << scene.getCharacterList().at(i).getGender() <<
					std::endl << std::endl;
			}
		}
		else {
			std::cout << "No characters in this Scene." << std::endl << std::endl;
		} 
	}
	else { /*nothing*/ }
}

void printCharacterInfo(Character character)
{
	std::cout << character.getName() << "'s details." << std::endl <<
		"Age: " << character.getCharacterAge() << std::endl <<
		"Description:  " << character.getDescription() << std::endl <<
		"Motive: " << character.getMotive() << std::endl <<
		"Gender: " << character.getGender() << std::endl << 
		"Notes: " << character.getNotes() << std::endl << std::endl;
}

void printChapterInfo(Chapter chapter)
{   //Number of scenes
	std::cout << "Chapter No: " << chapter.getChapterNumber() << std::endl;
	std::cout << "Scenes in Chapter: " << chapter.getNumberOfScenes() << std::endl;
	int chapSize = chapter.getSceneList().size();
	if (chapSize != 0) {
		for (int i = 0; i < chapSize; i++) {
			std::cout << i + 1 << ": ";
			std::cout << chapter.getSceneList().at(i).getSceneName() << std::endl;
		}
		std::cout << std::endl;
		//Access first character name, from first scene in Chapter.
		if (chapter.getSceneList().at(0).getCharacterList().size() != 0) {
			std::cout << "The name of the first character from the first scene is "
				<< chapter.getSceneList().at(0).getCharacterList().at(0).getName() <<
				", taken from character class via scene class." << std::endl;
		}
		else {/*Do nothing*/ }
	}
	else { std::cout << "No Scenes to display"; }
	std::cout << std::endl;
}

void printNarativeGeneralInfo(NarativeGeneralInfo ngi)
{
	std::cout << "Title: ";
	std::cout << ngi.getTitle() << std::endl;
	std::cout << "Setting: ";
	std::cout << ngi.getSetting() << std::endl;
	std::cout << "Description: ";
	std::cout << ngi.getGeneralDescription() << std::endl;
	std::cout << "Number of Chapters: ";
	std::cout << ngi.getNumberOfChapters();
	std::cout << std::endl << std::endl;
	//Display Chapter Names and Numbers
	int narSize = ngi.getChapters().size();
	if (narSize != 0) {
		for (int k = 0; k < narSize; k++) {
			if (ngi.getChapters().at(k).getChapterName() != "") {
				std::cout << "Chapter ";
				std::cout << ngi.getChapters().at(k).getChapterNumber() << " :";
				std::cout << ngi.getChapters().at(k).getChapterName() << std::endl;
			}
			else{/*Do Nothing*/ }
		}
		std::cout << std::endl;
	}
	else { std::cout << "No chapters to display" << std::endl; }
}

