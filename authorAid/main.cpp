//The aim is to build a flexible app that alows a user to freely keep track of their written creations. For example,
//a user may just feel like jotting down some details about a character, but not know their name, age, 
//or what story the character belongs to yet. Similarly a scene may be imagined without characters, etc.
//
//On the other had the user should have a sturdy framework to work with if they so choose.
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <sqlite3.h>

#include "Scene.h"
#include "Character.h"
#include "narativeGeneralInfo.h"
#include "Chapter.h"
#include "dbInteract.h"
#include "Location.h"

void printSceneInfo(Scene scene, bool charInfoOn);
void printCharacterInfo(Character character);
void printChapterInfo(Chapter chapter);
void printNarativeGeneralInfo(NarativeGeneralInfo ngi);
int callback(void* data, int argc, char** argv, char** azColName);
void displayAndError(int exit, bool display);
int dbTest(struct sqlite3 &db, int exit);
int inputInt();
std::string inputChtrChoice(std::string message);
std::string data("CALLBACK FUNCTION");

//Return strings from db (identifyThis possibly redundant)
std::vector <std::string> returnThis;
std::vector <std::string> identifyThis;
//GLOBAL CHARACTER COUNT, CURRENTLY DRAWN FROM CALLBACK FUNCTION, BUT MUST CHANGE TO DB.
int chaCount = 0;
//Used in a display function. Possibly redundent
int idCount = 0;
//save error messages. Possibly only used in test functions.
char* errMsg = 0;
//Testing from manually set values on/off
int visTest = 0;
int updateTest = 1;
int testUI = 1;

//TODO include "exists" into relevent tables and sqlite queries.
//TODO Set "chaCount" to be provided by World table, instead of callback function. Remove the counter from callback.
//TODO GUI

int main(int argc, char** argv) {

    //Create db instance
	sqlite3 *db;
	//exit deals with sqlite read and write	
	int exit = 0;
	//Open db
	//TESTING PURPOSES DBs
	if (updateTest){ 
		exit = sqlite3_open("exampleUpdateTest.db", &db); 
		dbTest(*db, exit);
	}
	else {
		exit = sqlite3_open("example.db", &db);
		//Test Connection
		dbTest(*db, exit);
	}
	
	//QUERIES AND TABLE SET UP
	std::string create(tableBaseCreate());
	std::string query(queryAllFieldsTable("CHARACTER"));
	returnThis.clear();
	identifyThis.clear();
	//std::string query(removeIDFromTable(5));
	exit = sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
	exit = sqlite3_exec(db, create.c_str(), callback, (void*)data.c_str(), NULL);
	std::cout << "cha count" << chaCount << std::endl << "Id count" << idCount << std::endl;
	//////////////////////
	//TEMP UI OFF OR ON//
	////////////////////
	if (testUI) {
		int ui = 1;
		/////////////////
		//MAIN UI LOOP//
		///////////////
		while (ui) {
			//MAIN INPUT//
			std::string input;
			std::cout << "Enter a command: view chtr, insert chtr, exit. " <<std::endl;
			std::getline(std::cin, input);
			std::cout << input << std::endl;
			//Exit condition//
			if (input == "exit") {
				ui = 0;
			}
			//View Character//
			else if (input == "view chtr") {
				int idIs;
				std::cout << "Character id is? ";
				idIs = inputInt() - 1;
				std::string sql(selectFrom("NAME, AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, idIs));
				exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
				chaCount -= 1;

				displayAndError(exit, false);
				returnThis.clear();
				identifyThis.clear();
			}
			//Update Character. May merge with insert. //OBSOLETE 
			/*else if (input == "update chtr") {
				std::string choice = inputChtrChoice("What value do you want to set? ");
				if (choice == "name") {
					std::string name = inputChtrChoice("Choose a name. ");
					//TEMP
					int id;
					id = inputInt();
					//ENDTEMP
					std::string sql(updateDb("CHARACTER", "NAME", name, id));
					exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
				}
			}*/
			//Insert a charcter, having assigned some or all details (I don't like switch statements)
			else if (input == "insert chtr") {
				//Global character count
				chaCount += 1;
				int hold = chaCount;
				//exit condition
				int exitInsert = 1;
				//Character class temp
				Character tempChtr;
				bool fromLoad = false;
				int tempChaCount = 0;
				//////////////////////////
				//Main insert chtr loop//
				////////////////////////
				while (exitInsert) {
					std::cout << "Character insert: please choose an attribute to insert." << std::endl <<
						"(n)ame, (a)ge, (d)escription, (m)otive,(g)ender,(notes)." << std::endl <<
						"(v)iew Character, (save), (load), Or (exit)." << std::endl;
					//input string
					std::string inputINS;
					std::getline(std::cin, inputINS);
					//check position in db
					std::cout << chaCount << std::endl;
					//Exit Condition
					if (inputINS == "exit") {
						exitInsert = 0;
						tempChtr.~Character();
						break;
					}
					//Enter Name
					else if (inputINS == "n") {
						tempChtr.setName(inputChtrChoice("What name do you want to insert? "));
					}
					//Enter Age
					else if (inputINS == "a") {
						std::cout << "Enter an age: " << std::endl;
						tempChtr.setCharacterAge(inputInt());
					}
					//Enter Description
					else if (inputINS == "d") {
						tempChtr.setDescription(inputChtrChoice("Describe the character: "));
					}
					//Enter Motive
					else if (inputINS == "m") {
						tempChtr.setMotive(inputChtrChoice("What is the character's motive? "));
					}
					//Enter Gender
					else if (inputINS == "g") {
						tempChtr.setGender(inputChtrChoice("Assign a gender? "));
					}
					//Enter Notes
					else if (inputINS == "notes") {
						tempChtr.setNotes(inputChtrChoice("Do you have any notes to make about this character? "));
					}
					//View Character
					else if (inputINS == "v") {
						printCharacterInfo(tempChtr);
					}
					//Save Character's details to table or Update Charcter's details.
					else if (inputINS == "save") {
						if (fromLoad == true) {
							chaCount = tempChaCount;
						}
						if (tempChtr.getExistence() == false) {
							std::string sql(insertCharacter(tempChtr, chaCount,0));
							exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
							tempChtr.setExistence();
						}
						else if (tempChtr.getExistence() == true) {
							std::string sql(insertCharacter(tempChtr, chaCount, 1));
							exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
						}
					}
					//Load Caracter from db To update feilds
					else if (inputINS == "load") {
						///Display all Characters
						std::string sql(selectFrom("ID,NAME", "CHARACTER", chaCount, 0));
						exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
						//Select Character by ID number
						std::cout << "Select Character ID from list: ";
						int idLoadChoice = tempChaCount  = inputInt() - 1;
						
						returnThis.clear();
						sql = (selectFrom("ID,NAME,AGE, DESCRIPTION, MOTIVE, GENDER, NOTES","CHARACTER", 1, idLoadChoice));
						exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
						//Add details to temp instance
						tempChtr.~Character();
						tempChtr.setCharacterFromDb(returnThis);
						//Display loaded character
						printCharacterInfo(tempChtr);
						//clear return
						returnThis.clear();
						//????????????????????//
						tempChtr.setExistence();
						//Confirm that Character is prodeuct of "load"
						fromLoad = true;
					}
					//Error message for insert
					displayAndError(exit, false);
					chaCount = hold;
				}
				chaCount = hold;
			}
		}
	}
	//TEMPORARY EARLY TESTING. WILL BE REMOVED FOLLOWING IMPROVEMENTS
	if (visTest) {
		//Create Characters
		Character c1;
		Character c2;
		Character c3; //("Dr.Bamboo", 77, "A nice old doctor, retired now. Enjoys tending to his garden.",
			//"Execution of ingrates", "Man");
		std::string sql(selectFrom("NAME, AGE, DESCRIPTION, MOTIVE, GENDER, NOTES", "CHARACTER", 1, 2));
		exit = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL);
		//c3.setCharacterFromDb(returnThis);
		//displayAndError(exit);
		Character Tom("Tom", 44, "Beer beast", "Create new beery world order", "bloke");
		Character a1("Mick", 55, "Nice enough, but... ", "Stealing and love", "Chromeman");
		Character a2("Nan", 700, "An old nan", "Getting blood out of the carpet", "Serpent");
		
		//Set Some Names and ages
		c1.setName("Mark");
		c1.setCharacterAge(6);
		c1.setGender("Boy");
		c1.setMotive("Chrisps");
		c2.setName("Babdoo");
		c2.setCharacterAge(13);
		c2.setGender("Female");
		c2.setDescription("Teenage girl");

		//Evidence 'notes' working.
		//a1.setNotes("Always, he gets into the fighting on tarmac over beer.\n"
		//	"'Why are you like this?' is the sort of thing his wife asks.\n"
		//	"'My Dyspraxia drives me to it, NOW LEAVE ME!' would be a typical reply.");

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
		//std::string sql22(insertCharacter(a1, 5));
		//sqlite3_exec(db, sql22.c_str(), callback, 0, &errMsg);
		//sqlite3_close(db);
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
		sceneOne.setName("Dr. Bamboo kills two people.");
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
		ngi1.setDescription("Book about a murder spree by a bad Dr.");

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
	chaCount += 1;
	idCount += 1;
	//Recieve data
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		//Return to global
		if (argv[i]) {
			returnThis.push_back(argv[i]);	
		}
		identifyThis.push_back(azColName[i]);
	}

	printf("\n");
	
	return 0; }

void displayAndError(int exit, bool display)
{
	if (display == true) {
		for (size_t retList = 0; retList < returnThis.size(); retList++) {
			std::cout << "Output from db= " << returnThis.at(retList) <<
				" Identity= " << identifyThis.at(retList) << std::endl;
		}
	}
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
		
	}

}
//DOESN'T WORK!!!! WOW!!!!!!
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
//Safley input integer, and parse.
int inputInt()
{
	std::string input = "";
	int id;
	while (true) {
		std::cout << "Please enter a valid number: ";
		std::getline(std::cin, input);
		// This converts from string to int.
		std::stringstream myStream(input);
		if (myStream >> id)
			break;
		std::cout << "Invalid number, please try again" << std::endl;
	}
	return id;
}
//Return a string. Helper. Mostly for making choices.
std::string inputChtrChoice(std::string message)
{	
	std::string choice;
	std::cout << message;
	std::getline(std::cin, choice);
	return choice; 
}
//Print scenes
void printSceneInfo(Scene scene, bool charInfoOn)
{
	//General information about the scene, from Scene.
	std::cout <<
		"Scene: " << scene.getSceneNumber() << std::endl <<
		"Location: " << scene.getLocation() << std::endl <<
		"Number of Characters: " << scene.getNumberOfCharacters() << std::endl <<
		"Name of scene: " << scene.getName() << std::endl <<
		"Time/date/etc: " << scene.getTimeAndOrDate() << std::endl <<
		"What happened?: " << scene.getDescription() << std::endl <<
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
//Print Characters
void printCharacterInfo(Character character)
{
	std::cout << character.getName() << "'s details." << std::endl <<
		"Age: " << character.getCharacterAge() << std::endl <<
		"Description:  " << character.getDescription() << std::endl <<
		"Motive: " << character.getMotive() << std::endl <<
		"Gender: " << character.getGender() << std::endl << 
		"Notes: " << character.getNotes() << std::endl << std::endl;
}
//Print Chapters
void printChapterInfo(Chapter chapter)
{   //Number of scenes
	std::cout << "Chapter No: " << chapter.getChapterNumber() << std::endl;
	std::cout << "Scenes in Chapter: " << chapter.getNumberOfScenes() << std::endl;
	int chapSize = chapter.getSceneList().size();
	if (chapSize != 0) {
		for (int i = 0; i < chapSize; i++) {
			std::cout << i + 1 << ": ";
			std::cout << chapter.getSceneList().at(i).getName() << std::endl;
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
//Print NGI
void printNarativeGeneralInfo(NarativeGeneralInfo ngi)
{
	std::cout << "Title: ";
	std::cout << ngi.getTitle() << std::endl;
	std::cout << "Setting: ";
	std::cout << ngi.getSetting() << std::endl;
	std::cout << "Description: ";
	std::cout << ngi.getDescription() << std::endl;
	std::cout << "Number of Chapters: ";
	std::cout << ngi.getNumberOfChapters();
	std::cout << std::endl << std::endl;
	//Display Chapter Names and Numbers
	int narSize = ngi.getChapters().size();
	if (narSize != 0) {
		for (int k = 0; k < narSize; k++) {
			if (ngi.getChapters().at(k).getName() != "") {
				std::cout << "Chapter ";
				std::cout << ngi.getChapters().at(k).getChapterNumber() << " :";
				std::cout << ngi.getChapters().at(k).getName() << std::endl;
			}
			else{/*Do Nothing*/ }
		}
		std::cout << std::endl;
	}
	else { std::cout << "No chapters to display" << std::endl; }
}

