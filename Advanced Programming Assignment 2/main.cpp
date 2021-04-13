#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DynTempStack.h"
#include "SwitchManager.h"
#include "RoomManager.h"
using namespace std;


void splitToStack(string strToSplit, char delimiter, DynTempStack<string>& splittedStrings)//implementation of c#'s Split function obtained from an online tutorial
{
	stringstream ss(strToSplit);
	string item;
	while (getline(ss, item, delimiter))//loob grabs entries from ss and puts them into item until delimiter/sentinel is found
	{
		splittedStrings.push(item);
	}
}

bool iequals(const string& a, const string& b)
{
	return std::equal(a.begin(), a.end(),
		b.begin(), b.end(),
		[](char a, char b) {
			return tolower(a) == tolower(b);
		});
}

string getInput(DynTempStack<string> commands, RoomManager* roomManager)
{
	string input;
	getline(cin, input);
	for (int i = 0; i < 28; i++)
	{
		if (iequals(input, commands.accessSpecificNode(i)))
		{
			return (commands.accessSpecificNode(i));
		}
		else if (i == 28)
		{
			cout << "Invalid command. Please try again.\n";
			return "";
		}
	}
	return "";
}

int main()
{
	//a bunch more boolean switches contained in a manager depending on how many things might change in the game, probably like 8-10 in total
	//it just gets passed by reference to anything that needs it
	SwitchManager switchManager;

	//a stack that containa every valid command the player can enter, used to determine if a command is valid
	//also some stacks containing narration for each room. maps would work better for this purpose, I think
	DynTempStack<string> commands, atriumNarration, keepNarration, northTowerNarration, southTowerNarration, cellarNarration, genericNarration;
	string input;

	char pipeDelimiter = '|';

	//load the possible commands from a text file into commands
	ifstream file{"narration.txt"};
	if (!file)
	{
		cout << "File one could not be opened.";
		return 1;
	}
	//populate the commands stack
	string temp;
	getline(file, temp);
	splitToStack(temp, pipeDelimiter, commands);
	temp = "";
	getline(file, temp);
	splitToStack(temp, pipeDelimiter, atriumNarration);
	temp = "";
	getline(file, temp);
	splitToStack(temp, pipeDelimiter, keepNarration);
	temp = "";
	getline(file, temp);
	splitToStack(temp, pipeDelimiter, southTowerNarration);
	temp = "";
	getline(file, temp);
	splitToStack(temp, pipeDelimiter, northTowerNarration);
	temp = "";
	getline(file, temp);
	splitToStack(temp, pipeDelimiter, cellarNarration);
	temp = "";
	getline(file, temp);
	splitToStack(temp, pipeDelimiter, genericNarration);
	
	RoomManager *roomManager = new RoomManager(&atriumNarration, &genericNarration, &commands, &switchManager);

	while (switchManager.exitGame == false)
	{
		//print information regarding the current room
		if (switchManager.currentLocation == SwitchManager::GameLocations::atrium)
		{
			roomManager->changeNarrationStack(&atriumNarration);
			roomManager->processAtrium("");

			string temp = getInput(commands, roomManager);
			roomManager->processAtrium(temp);

			//process input and do stuff depending on what the player entered
			if (iequals(temp, "EXIT GAME") || iequals(temp, "EXIT"))
			{
				switchManager.exitGame = true;
			}
			if ((iequals(temp, "LEAVE ROOM") || iequals(temp, "EXIT ROOM")) && switchManager.atriumKeepDoorOpen == true)
			{
				switchManager.currentLocation = SwitchManager::GameLocations::keep;
				cout << genericNarration.accessSpecificNode(8) << endl;
			}
			else if((iequals(temp, "LEAVE ROOM") || iequals(temp, "EXIT ROOM")) && switchManager.atriumKeepDoorOpen == false)
			{
				cout << genericNarration.accessSpecificNode(9) << endl;
			}
		}
		else if (switchManager.currentLocation == SwitchManager::GameLocations::keep)
		{
			roomManager->changeNarrationStack(&keepNarration);
			roomManager->processKeep("");

			string temp = getInput(commands, roomManager);
			roomManager->processKeep(temp);

			if (iequals(temp, "EXIT GAME") || iequals(temp, "EXIT"))
			{
				switchManager.exitGame = true;
			}
			else if (iequals(temp, "LEAVE ROOM") || iequals(temp, "EXIT ROOM"))
			{
				cout << genericNarration.accessSpecificNode(1) << endl;
				string temp = getInput(commands, roomManager);
				if (iequals(temp, "SOUTH TOWER"))
				{
					switchManager.currentLocation = SwitchManager::GameLocations::southTower;
					cout << genericNarration.accessSpecificNode(5) << endl;
				}
				else if (iequals(temp, "ATRIUM"))
				{
					switchManager.currentLocation = SwitchManager::GameLocations::atrium;
					cout << genericNarration.accessSpecificNode(7) << endl;
				}
				else if (iequals(temp, "CELLAR") && switchManager.cellarKeepDoorOpen == true)
				{
					switchManager.currentLocation = SwitchManager::GameLocations::cellar;
					cout << genericNarration.accessSpecificNode(4) << endl;
				}
				else if (iequals(temp, "NORTH TOWER") && switchManager.northTowerKeepDoorOpen == true)
				{
					switchManager.currentLocation = SwitchManager::GameLocations::northTower;
					cout << genericNarration.accessSpecificNode(6) << endl;
				}
				else if (iequals(temp, "NORTH TOWER") || iequals(temp, "CELLAR"))
				{
					cout << genericNarration.accessSpecificNode(12) << endl;
				}
				else if (iequals(temp, "KEEP"))
				{
					cout << genericNarration.accessSpecificNode(11) << endl;
				}
			}
			else if (iequals(temp, "OPEN DOOR") || iequals(temp, "UNLOCK DOOR"))
			{
				cout << genericNarration.accessSpecificNode(13) << endl;
				temp = getInput(commands, roomManager);
				if (iequals(temp, "NORTH TOWER"))
				{
					switchManager.northTowerKeepDoorOpen = true;
					cout << genericNarration.accessSpecificNode(15) << endl;
				}
				else if (iequals(temp, "CELLAR"))
				{
					switchManager.cellarKeepDoorOpen = true;
					cout << genericNarration.accessSpecificNode(14) << endl;
				}
				else
				{
					cout << genericNarration.accessSpecificNode(10) << endl;
				}
			}
		}
		else if (switchManager.currentLocation == SwitchManager::GameLocations::southTower)
		{
			roomManager->changeNarrationStack(&southTowerNarration);
			roomManager->processSouthTower("");

			string temp = getInput(commands, roomManager);
			roomManager->processSouthTower(temp);

			if (iequals(temp, "EXIT GAME") || iequals(temp, "EXIT"))
			{
				switchManager.exitGame = true;
			}
			else if(iequals(temp, "SLOT CRYSTAL") && switchManager.secretPassageOpen == false)
			{
				temp = getInput(commands, roomManager);
				if (temp != "RED SLOT" || (temp != "GREEN SLOT" || (temp != "BLUE SLOT")))
				{
					cout << genericNarration.accessSpecificNode(10) << endl;
				}
				else
				{
					roomManager->processSouthTower(temp);
				}
			}
			else if (iequals(temp, "SLOT CRYSTAL") && switchManager.secretPassageOpen == true)
			{
				cout << genericNarration.accessSpecificNode(10) << endl;
			}
			else if (iequals(temp, "LEAVE ROOM") || iequals(temp, "EXIT ROOM"))
			{
				cout << genericNarration.accessSpecificNode(1) << endl;
				string temp = getInput(commands, roomManager);
				if (iequals(temp, "KEEP"))
				{
					switchManager.currentLocation = SwitchManager::GameLocations::keep;
					cout << genericNarration.accessSpecificNode(8) << endl;
				}
				else if (iequals(temp, "CELLAR") && switchManager.southTowerCellarPassageOpen == true)
				{
					switchManager.currentLocation = SwitchManager::GameLocations::cellar;
					cout << genericNarration.accessSpecificNode(4) << endl;
				}
				else if (iequals(temp, "NORTH TOWER") || iequals(temp, "ATRIUM") || iequals(temp, "CELLAR"))
				{
					cout << genericNarration.accessSpecificNode(12) << endl;
				}
				else if (iequals(temp, "SOUTH TOWER"))
				{
					cout << genericNarration.accessSpecificNode(11) << endl;
				}
			}
		}
		else if (switchManager.currentLocation == SwitchManager::GameLocations::northTower)
		{
			roomManager->changeNarrationStack(&northTowerNarration);
			roomManager->processNorthTower("");

			string temp = getInput(commands, roomManager);
			roomManager->processNorthTower(temp);

			if (iequals(temp, "EXIT GAME") || iequals(temp, "EXIT"))
			{
				switchManager.exitGame = true;
			}
			if (iequals(temp, "LEAVE ROOM") || iequals(temp, "EXIT ROOM"))
			{
				cout << genericNarration.accessSpecificNode(1) << endl;
				string temp = getInput(commands, roomManager);
				if (iequals(temp, "KEEP"))
				{
					switchManager.currentLocation = SwitchManager::GameLocations::keep;
					cout << genericNarration.accessSpecificNode(8) << endl;
				}
				else if (iequals(temp, "SOUTH TOWER") || iequals(temp, "ATRIUM") || iequals(temp, "CELLAR"))
				{
					cout << genericNarration.accessSpecificNode(12) << endl;
				}
				else if (iequals(temp, "NORTH TOWER"))
				{
					cout << genericNarration.accessSpecificNode(11) << endl;
				}
			}
		}
		else if (switchManager.currentLocation == SwitchManager::GameLocations::cellar)
		{
			roomManager->changeNarrationStack(&cellarNarration);
			roomManager->processCellar("");

			string temp = getInput(commands, roomManager);
			roomManager->processCellar(temp);

			if (iequals(temp, "EXIT GAME") || iequals(temp, "EXIT"))
			{
				switchManager.exitGame = true;
			}
			if (iequals(temp, "LEAVE ROOM") || iequals(temp, "EXIT ROOM"))
			{
				cout << genericNarration.accessSpecificNode(1) << endl;
				string temp = getInput(commands, roomManager);
				if (iequals(temp, "KEEP"))
				{
					switchManager.currentLocation = SwitchManager::GameLocations::keep;
					cout << genericNarration.accessSpecificNode(8) << endl;
				}
				else if(iequals(temp, "SOUTH TOWER") && switchManager.southTowerCellarPassageOpen == true)
				{
					switchManager.currentLocation = SwitchManager::GameLocations::southTower;
					cout << genericNarration.accessSpecificNode(5) << endl;
				}
				else if (iequals(temp, "NORTH TOWER") || iequals(temp, "ATRIUM") || iequals(temp, "SOUTH TOWER"))
				{
					cout << genericNarration.accessSpecificNode(12) << endl;
				}
				else if (iequals(temp, "CELLAR"))
				{
					cout << genericNarration.accessSpecificNode(11) << endl;
				}
			}
		}
	}//some input will trigger the exit condition
	
	return 0;
}