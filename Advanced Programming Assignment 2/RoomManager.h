#pragma once
#include <iostream>
#include <string>
#include "DynTempStack.h"
#include "SwitchManager.h"

class RoomManager
{
private:
	DynTempStack<string> *roomNarrationStack, *genericNarrationStack, *commandsStack;
	SwitchManager *switchManager;
	void printNarration(int num);
public:
	RoomManager(DynTempStack<string>* rns, DynTempStack<string>* gns, DynTempStack<string>* cs, SwitchManager* sm);
	void changeNarrationStack(DynTempStack<string> * rns);
	void processAtrium(string s);
	void processKeep(string s);
	void processNorthTower(string s);
	void processSouthTower(string s);
	void processCellar(string s);
};