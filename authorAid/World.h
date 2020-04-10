#pragma once
#include <iostream>
#include <string>
#include <sstream>
//In depth look at the world the narrative takes place in.  
//TODO
class World
{

private:
	int characterCount = 0;
	int locationCount = 0;
	int sceneCount = 0;

	std::string name = "No Name";
	std::string description = "No Description";
	std::string notes = "No Notes";

	bool exists = false;
	

public:
	void setName(std::string name);
	std::string getName() { return name; };

	void setDescription(std::string description);
	std::string getDescription() { return description; };

	void setNotes(std::string notes);
	std::string getNotes() { return notes; };

	void setExistence();
	bool getExistence() { return exists; };

	int convertToInt(std::string convert);
	
};
//General information about Places
	//List of places (Subplaces?)
//What sort of universe or environment does the story take place?


//matrix of characters, their relations with eachother
	//their relations to groups within the World,
	//Group relations with eachother
	//
	// MATRIX: Individual relations 
	//     ind1 ind2 ind3 ind4 
	//ind1 XXX  Rel  Rel  Rel  
	//ind2 Rel  XXX  Rel  Rel
	//ind3 Rel  Rel  XXX  Rel
	//ind4 Rel  Rel  Rel  XXX
	//
	//Two seperate fields for two people is ok. (col 4 row 1, col 1, row 4 )
	//ind1 might love ind4, but ind4 might hate ind1)
	//
	//MATRIX: Individuals to groups
	//     ind1 ind2 ind3 ind4 
	//GRP1 Rel  Rel  Rel  Rel
	//GRP2 Rel  Rel  Rel  Rel
	//GRP3 Rel  Rel  Rel  Rel
	//GRP4 Rel  Rel  Rel  Rel
	//
	// MATRIX: Group relations
	//     GRP1 GRP2 GRP3 GRP4 
	//GRP1 XXX  Rel  Rel  Rel
	//GRP2 Rel  XXX  Rel  Rel
	//GRP3 Rel  Rel  XXX  Rel
	//GRP4 Rel  Rel  Rel  XXX
	


  
   
