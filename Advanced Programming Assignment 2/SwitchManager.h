#pragma once
//manages the various boolean switches used in the game, in one conveniently public place so that everything can work with it
struct SwitchManager
{
	//what you can access
	bool atriumKeepDoorOpen = false;
	bool keepChestUnlocked = false;
	bool keepPaintingsTakenDown = false;
	bool northTowerKeepDoorOpen = false;
	bool secretPassageOpen = false;
	bool southTowerCellarPassageOpen = false;
	bool cellarKeepDoorOpen = false;
	bool atriumDoorOpen = false;

	//items that you have
	bool southTowerKeyTaken = false;
	bool magicCrystalTaken = false;
	bool keepKeyTaken = false;

	//boolean that determines when to exit the game loop
	bool exitGame = false;

	//enum that containss the possible locations in the game
	enum class GameLocations { atrium, keep, northTower, southTower, cellar };
	//tracks the player's current position
	GameLocations currentLocation = GameLocations::atrium;
};