//General functions relating to the scene. Getters/setters.
#include "Scene.h"

Scene::Scene() = default;
Scene::~Scene()
{
};
Scene::Scene(std::string location, std::string timeAndOrDate,
	std::string sceneName, std::string genralDescription,
	int sceneNumber)
{
	setLocation(location);
	setTimeAndOrDate(timeAndOrDate);
	setName(sceneName);
	setDescription(genralDescription);
	setSceneNumber(sceneNumber);
	
};

void Scene::setLocation(std::string location)
{
	this->location = location;
};

void Scene::setTimeAndOrDate(std::string timeAndOrDate)
{
	this->timeAndOrDate = timeAndOrDate;
};

void Scene::setSceneNumber(int sceneNumber)
{
	this->sceneNumber = sceneNumber;
};
void Scene::setCharacters(Character character)
{
	this->characters.push_back(character);
	this->numberOfCharacters += 1;
};
std::vector<Character> Scene::getCharacterList()
{
	return characters;
}

void Scene::removeCharacterFromList(int elementIndex)
{
	
	this->characters.erase(characters.begin() + elementIndex);
}

void Scene::setSceneFromDb(std::vector<std::string> dbreturn)
{   
	try {
		//int sceneNumInt, nChtrInt, existBoolInt;
		std::string sceneNum, nChtr;
		//LOCATION, TIME_DATE, SCENE_NAME, GEN_DSCRPT, NOTES, SCENE_NUM, NUM_CRCTRS, EXISTS_BOOL

		setLocation(dbreturn.at(0));
		setTimeAndOrDate(dbreturn.at(1));
		setName(dbreturn.at(2));
		setDescription(dbreturn.at(3));
		setNotes(dbreturn.at(4));
		sceneNum = dbreturn.at(5);
		setSceneNumber(convertToInt(sceneNum));
		//Below, probably OBSOLETE due to being automatially updated as chtr's are added. Leaving this
		//here just in case it is needed.
		nChtr = dbreturn.at(6);
		//setSceneNumber(convertToInt(nChtr));
		//END OBS
		setExistence();
	}
	catch (std::out_of_range e) {
		std::cout << "Sorry, there has been a problem, please try again." << std::endl;
		dbreturn.clear();
	}
}
int Scene::convertToInt(std::string convert)
{
	int returnInt;
	std::stringstream myStream(convert);
	myStream >> returnInt;
	return returnInt;
};
;

