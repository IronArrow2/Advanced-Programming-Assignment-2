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
		if (switchManager->atriumKeepDoorOpen == true)
		{
			cout << genericNarrationStack->accessSpecificNode(0) << endl;
			return;
		}
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
		cout << genericNarrationStack->accessSpecificNode(10) << endl;
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
		if (switchManager->keepPaintingsTakenDown == true)
		{
			cout << genericNarrationStack->accessSpecificNode(0) << endl;
			return;
		}
		switchManager->keepPaintingsTakenDown = true;
		printNarration(6);
		return;
	}
	else if (s == "OPEN CHEST")
	{
		if (switchManager->southTowerKeyTaken == false)
		{
			cout << genericNarrationStack->accessSpecificNode(9) << endl;
			return;
		}
		else if (switchManager->keepChestUnlocked == true)
		{
			cout << genericNarrationStack->accessSpecificNode(0) << endl;
			return;
		}
		else
		{
			switchManager->keepChestUnlocked = true;
			printNarration(7);
		}
	}
	else if (s == "PULL LEVER")
	{
		if (switchManager->keepPaintingsTakenDown == false)
		{
			cout << genericNarrationStack->accessSpecificNode(9) << endl;
			return;
		}
		else if (switchManager->northTowerLeverRevealed == true)
		{
			cout << genericNarrationStack->accessSpecificNode(0) << endl;
			return;
		}
		else
		{
			switchManager->northTowerLeverRevealed = true;
			cout << genericNarrationStack->accessSpecificNode(2) << endl;
		}
	}
	else if (s == "TAKE KEY")
	{
		if (switchManager->keepChestUnlocked == false)
		{
			cout << genericNarrationStack->accessSpecificNode(9) << endl;
			return;
		}
		else if (switchManager->keepKeyTaken == true)
		{
			cout << genericNarrationStack->accessSpecificNode(0) << endl;
			return;
		}
		else
		{
			switchManager->keepKeyTaken = true;
			cout << genericNarrationStack->accessSpecificNode(3) << endl;
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
		cout << genericNarrationStack->accessSpecificNode(10) << endl;
		return;
	}

	//print starting narration
	if (switchManager->keepChestUnlocked == false && switchManager->keepPaintingsTakenDown == false && switchManager->cellarKeepDoorOpen == false)
	{
		printNarration(9);
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
		printNarration(5);
	}
	else if (switchManager->keepChestUnlocked == false && switchManager->keepPaintingsTakenDown == false && switchManager->cellarKeepDoorOpen == true)
	{

	}
}

void RoomManager::processNorthTower(string s)
{
	if (s == "PULL LEVER")
	{
		if (switchManager->northTowerLeverRevealed == false)
		{
			cout << genericNarrationStack->accessSpecificNode(10) << endl;
			return;
		}
		else if (switchManager->atriumDoorOpen == true)
		{
			cout << genericNarrationStack->accessSpecificNode(0) << endl;
			return;
		}
		else
		{
			switchManager->atriumDoorOpen = true;
			cout << genericNarrationStack->accessSpecificNode(2) << endl;
		}
	}
	else if (s == "TAKE KEY")
	{
		if (switchManager->northTowerKeyTaken == true)
		{
			cout << genericNarrationStack->accessSpecificNode(0) << endl;
			return;
		}
		else
		{
			switchManager->northTowerKeyTaken = true;
			cout << genericNarrationStack->accessSpecificNode(3) << endl;
		}
	}
	else if (s == "TAKE WEAPON")
	{
		printNarration(4);
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
		cout << genericNarrationStack->accessSpecificNode(10) << endl;
		return;
	}

	//print starting narration
	if (switchManager->northTowerKeyTaken == false)
	{
		if (switchManager->northTowerLeverRevealed == false)
		{
			printNarration(3);
		}
		else
		{
			printNarration(2);
		}
	}
	else
	{
		if (switchManager->northTowerLeverRevealed == false)
		{
			printNarration(1);
		}
		else
		{
			printNarration(0);
		}
	}
}

void RoomManager::processSouthTower(string s)
{
	if (s == "INSPECT ROOM")
	{
		printNarration(4);
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
		cout << genericNarrationStack->accessSpecificNode(10) << endl;
		return;
	}

	//print starting narration
	if (switchManager->southTowerKeyTaken == false)
	{

	}
	else
	{

	}
}

void RoomManager::processCellar(string s)
{
	if (s == "INSPECT ROOM")
	{
		//printNarration(4);
	}
	else if (s == "EXIT" || s == "EXIT GAME")
	{
		return;
	}
	else if (s == "LEAVE ROOM" || s == "EXIT ROOM")
	{
		return;
	}
}
