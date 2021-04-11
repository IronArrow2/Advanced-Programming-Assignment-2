#include "RoomManager.h"

RoomManager::RoomManager(DynTempStack<string>* rns, DynTempStack<string>* gns, DynTempStack<string>* cs, SwitchManager* sm)
{
	roomNarrationStack = rns;
	genericNarrationStack = gns;
	commandsStack = cs;
	switchManager = sm;
}

void RoomManager::changeNarrationStack(DynTempStack<string>* rns)
{
	roomNarrationStack = rns;
}

void RoomManager::printNarration(int num)
{
	cout << roomNarrationStack->accessSpecificNode(num) << endl;
}

void RoomManager::processAtrium(string s)
{
	if (s == "INSPECT ROOM")
	{
		printNarration(3);
		return;
	}
	else if (s == "PULL TORCH")
	{
		switchManager->atriumKeepDoorOpen = true;
		printNarration(2);
		return;
	}
	else if (s == "EXIT" || s == "EXIT GAME")
	{
		return;
	}
	else if (s == "LEAVE ROOM" || s == "EXIT ROOM")
	{
		return;
	}
	else if (s != "")
	{
		cout << "Hmm. Looks like you can't do that here." << endl;
		return;
	}

	//print starting narration
	if (switchManager->atriumKeepDoorOpen == false)
	{
		printNarration(4);
	}
	else if (switchManager->atriumKeepDoorOpen == true && switchManager->atriumDoorOpen == false)
	{
		printNarration(1);
	}
	else if (switchManager->atriumDoorOpen == true)
	{
		printNarration(0);
	}
}

void RoomManager::processKeep(string s)
{
	if (s == "REMOVE PAINTING" || s == "REMOVE PAINTINGS")
	{
		switchManager->keepPaintingsTakenDown = true;
		printNarration(4);
		return;
	}
	else if (s == "OPEN CHEST")
	{
		if (switchManager->southTowerKeyTaken == false)
		{
			cout << genericNarrationStack->accessSpecificNode(9);
			return;
		}
		else
		{
			printNarration(5);
		}
	}
	else if (s == "EXIT" || s == "EXIT GAME")
	{
		return;
	}
	else if (s == "LEAVE ROOM" || s == "EXIT ROOM")
	{
		return;
	}
	else if (s != "")
	{
		cout << "Hmm. Looks like you can't do that here." << endl;
		return;
	}

	//print starting narration
	if (switchManager->keepChestUnlocked == false && switchManager->keepPaintingsTakenDown == false && switchManager->cellarKeepDoorOpen == false)
	{
		printNarration(7);
	}
	else if(switchManager->keepChestUnlocked == true && switchManager->keepPaintingsTakenDown == false && switchManager->cellarKeepDoorOpen == false)
	{
		printNarration(2);
	}
	else if (switchManager->keepChestUnlocked == true && switchManager->keepPaintingsTakenDown == true && switchManager->cellarKeepDoorOpen == false)
	{

	}
	else if (switchManager->keepChestUnlocked == true && switchManager->keepPaintingsTakenDown == true && switchManager->cellarKeepDoorOpen == true)
	{

	}
	else if (switchManager->keepChestUnlocked == true && switchManager->keepPaintingsTakenDown == false && switchManager->cellarKeepDoorOpen == true)
	{

	}
	else if (switchManager->keepChestUnlocked == false && switchManager->keepPaintingsTakenDown == true && switchManager->cellarKeepDoorOpen == true)
	{

	}
	else if (switchManager->keepChestUnlocked == false && switchManager->keepPaintingsTakenDown == true && switchManager->cellarKeepDoorOpen == false)
	{
		printNarration(3);
	}
	else if (switchManager->keepChestUnlocked == false && switchManager->keepPaintingsTakenDown == false && switchManager->cellarKeepDoorOpen == true)
	{

	}
}

void RoomManager::processNorthTower(string s)
{
}

void RoomManager::processSouthTower(string s)
{
}

void RoomManager::processCellar(string s)
{
}
