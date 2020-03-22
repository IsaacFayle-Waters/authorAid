//The aim is to build a flexible app that alows a user to freely keep track of their written creations. For example,
//a user may just feel like jotting down some details about a character, but not know their name, age, 
//or what story the character belongs to yet. Similarly a scene may be imagined without characters, etc.
//
//On the other had the user should have a sturdy framework to work with if they so choose.
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sqlite3.h>

#include "Scene.h"
#include "Character.h"
#include "narativeGeneralInfo.h"
#include "Chapter.h"
#include "dbInteract.h"

void printSceneInfo(Scene scene, bool charInfoOn);
void printCharacterInfo(Character character);
void printChapterInfo(Chapter chapter);
void printNarativeGeneralInfo(NarativeGeneralInfo ngi);
int callback(void* data, int argc, char** argv, char** azColName);
void displayAndError(int exit);
int dbTest(struct sqlite3 &db, int exit);

//Return strings from db (identifyThis possibly redundant)
std::vector <std::string> returnThis;
std::vector <std::string> identifyThis;
//save error messages
char* errMsg = 0;
//Visual testing from manually set values on/off
int visTest = 0;

//TODO SORT OUT Db. Connected, now need to write to and then read from it.
//Use example data to effect writing via sqlite. 
//TODO finish creating tables
//TODO GUI

int main(int argc, char** argv) {
	
	//UPDATE COMPANY SET ADDRESS = 'Texas' WHERE ID = 6
	std::string test = updateDb("CHARACTER","MOTIVE","Get out of bed", 3);
	std::cout << test << std::endl;
    //Create db instance
	sqlite3 *db;
	//exit deals with sqlite read and write	
	int exit = 0;
	std::string data("CALLBACK FUNCTION");
	//Open db
	exit = sqlite3_open("example.db", &db);
	//Test Connection
	dbTest(*db,exit);
	
	//TEMP UI
	int ui = 1;
	while (ui) {
		std::string input;
		std::cout << "Enter a command "; 
		std::getline(std::cin, input);
		std::cout << input << std::endl;

		if (input == "exit") {
			ui = 0;
		}
		else if (input == "character") {
			Character *temp = new Character();
			int idIs;
			std::cout << "Character id is? ";
			std::cin >> idIs;
			std::string sql(selectFrom("NAME, AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, idIs));
			exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
			temp->setCharacterFromDb(returnThis);//.setCharacterFromDb(returnThis);
			displayAndError(exit);
			
			std::cout << temp->getName() << std::endl;
		}	
	}

	if (visTest) {
		//Create Characters
		Character c1;
		Character c2;
		Character c3; // ("Dr.Bamboo", 77, "A nice old doctor, retired now. Enjoys tending to his garden.",
			//"Execution of ingrates", "Man");
		std::string sql(selectFrom("NAME, AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, 2));
		exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
		c3.setCharacterFromDb(returnThis);
		displayAndError(exit);
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

		/*std::string sql(insertCharacter(c1,1));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
					 sql =(insertCharacter(c2, 2));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		 sql = (insertCharacter(c3, 3));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		 sql = (insertCharacter(Tom, 4));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		 sql = (insertCharacter(a1, 5));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		 sql = (insertCharacter(a2, 6));
		exit = exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
		*/

		sqlite3_close(db);
		//END DB STUFF

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
		Chapter chap1(1, "Etchings of FEAR!");
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

		printSceneInfo(sceneOne, false);
		printSceneInfo(sceneTwo, true);
		printSceneInfo(sceneThree, false);

		printChapterInfo(chap2);
		printSceneInfo(sceneFour, false);
		printSceneInfo(sceneFive, true);

		printCharacterInfo(c3);
		//Example of value passing through classes
		printNarativeGeneralInfo(ngi2);

	}
	sqlite3_close(db);
return 0;
}
//Return from database
int callback(void* data, int argc, char** argv, char** azColName) { 
	
	int i;
	std::string toReturn;
	fprintf(stderr, "%s: ", (const char*)data);
	//Recieve data
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		//Return to global
		returnThis.push_back(argv[i]);
		identifyThis.push_back(azColName[i]);
	}

	printf("\n");
	
	return 0; }

void displayAndError(int exit)
{
	for (size_t retList = 0; retList < returnThis.size(); retList++) {
		std::cout << "Output from db= " << returnThis.at(retList) <<
			" Identity= " << identifyThis.at(retList) << std::endl;
	}
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(errMsg);
	}

}
//Possibly not right? Need to research pointers more.
int dbTest(struct sqlite3 &db, int exit)
{
	if (exit) {
		std::cerr << "Error open db" << sqlite3_errmsg(&db) << std::endl;
		return(-1);
	}
	else {
		std::cout << "Opened Database Successfully!" << std::endl;
	}
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

