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
	else if (s == "GO OUTSIDE")
	{
		if (switchManager->atriumDoorOpen == false)
		{
			cout << genericNarrationStack->accessSpecificNode(16) << endl;
			return;
		}
		else
		{
			cout << genericNarrationStack->accessSpecificNode(17) << endl;
			exit(0);
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
		printNarration(0);
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
			printNarration(1);
			return;
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
			return;
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
			return;
		}
	}
	else if (s == "INSPECT ROOM")
	{
		printNarration(2);
		return;
	}
	else if (s == "UNLOCK DOOR" || s == "OPEN DOOR")
	{
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
	if (switchManager->keepChestUnlocked == false)
	{
		if (switchManager->keepPaintingsTakenDown == false)
		{
			printNarration(10);
		}
		else
		{
			printNarration(9);
		}
	}
	else
	{
		if (switchManager->keepPaintingsTakenDown == false)
		{
			if (switchManager->northTowerKeepDoorOpen == false)
			{
				printNarration(8);
			}
			else
			{
				if (switchManager->cellarKeepDoorOpen == false)
				{
					printNarration(6);
				}
				else
				{
					printNarration(4);
				}
			}
		}
		else
		{
			if (switchManager->northTowerKeepDoorOpen == false)
			{
				printNarration(7);
			}
			else
			{
				if (switchManager->cellarKeepDoorOpen == false)
				{
					printNarration(5);
				}
				else
				{
					printNarration(3);
				}
			}
		}
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
			return;
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
			return;
		}
	}
	else if (s == "TAKE WEAPON")
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
			printNarration(0);
		}
		else
		{
			printNarration(1);
		}
	}
}

void RoomManager::processSouthTower(string s)
{
	if (s == "INSPECT ROOM")
	{
		printNarration(5);
		return;
	}
	else if(s == "SLOT CRYSTAL" && switchManager->secretPassageOpen == false)
	{
		printNarration(6);
		return;
	}
	else if(s == "RED SLOT" && switchManager->secretPassageOpen == false)
	{
		printNarration(4);
		return;
	}
	else if (s == "GREEN SLOT" && switchManager->secretPassageOpen == false)
	{
		printNarration(3);
		return;
	}
	else if (s == "BLUE SLOT" && switchManager->secretPassageOpen == false)
	{
		switchManager->secretPassageOpen = true;
		printNarration(2);
		return;
	}
	else if (s == "PULL BOOKS")
	{
		if (switchManager->southTowerCellarPassageOpen == true)
		{
			cout << genericNarrationStack->accessSpecificNode(0);
			return;
		}
		else
		{
			switchManager->southTowerCellarPassageOpen = true;
			printNarration(0);
			return;
		}
	}
	else if (s == "TAKE CRYSTAL")
	{
		printNarration(1);
		return;
	}
	else if (s == "TAKE KEY")
	{
		if (switchManager->southTowerKeyTaken == true)
		{
			cout << genericNarrationStack->accessSpecificNode(0) << endl;
			return;
		}
		else
		{
			switchManager->southTowerKeyTaken = true;
			cout << genericNarrationStack->accessSpecificNode(3) << endl;
			return;
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
	if (switchManager->southTowerKeyTaken == false)
	{
		if (switchManager->southTowerCellarPassageOpen == false)
		{
			if (switchManager->secretPassageOpen == false)
			{
				printNarration(14);
			}
			else
			{
				printNarration(8);
			}
		}
		else
		{
			if (switchManager->secretPassageOpen == false)
			{
				printNarration(9);
			}
			else
			{
				printNarration(7);
			}
		}
	}
	else
	{
		if (switchManager->southTowerCellarPassageOpen == false)
		{
			if (switchManager->secretPassageOpen == false)
			{
				printNarration(13);
			}
			else
			{
				printNarration(11);
			}
		}
		else
		{
			if (switchManager->secretPassageOpen == false)
			{
				printNarration(12);
			}
			else
			{
				printNarration(10);
			}
		}
	}
}

void RoomManager::processCellar(string s)
{
	if (s == "INSPECT ROOM")
	{
		//printNarration(4);
		return;
	}
	else if (s == "GO OUTSIDE")
	{
		if (switchManager->secretPassageOpen == false)
		{
			cout << genericNarrationStack->accessSpecificNode(16) << endl;
			return;
		}
		else
		{
			cout << genericNarrationStack->accessSpecificNode(17) << endl;
			exit(0);
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

	//print starting narration
	if (switchManager->secretPassageOpen == false)
	{
		if (switchManager->southTowerCellarPassageOpen == false)
		{
			printNarration(3);
		}
		else
		{
			printNarration(0);
		}
	}
	else
	{
		if (switchManager->southTowerCellarPassageOpen == false)
		{
			printNarration(2);
		}
		else
		{
			printNarration(1);
		}
	}
}
