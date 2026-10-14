#pragma once
#include<iostream>
#include "Maze.h"
#include "Item.h"
#include<vector>

class Game {
	bool end;
	Maze* maze;
	std::vector<Item*> items;
	Item* activeItem;
	unsigned int iPos, jPos, iMPos,jMPos,iEnd,jEnd;
	char lastPosCharR, lastPosCharM;

public:
	Game(unsigned int rowCount, unsigned int colCount, unsigned int itemCount);
	~Game();
	Maze& getMaze();
	bool moveR();
	void moveM();
	bool getEnd();
	Item* getItem();
	void nullItem();
	unsigned int getIEnd();
	unsigned int getJEnd();
	void generateItem();
	bool moveRSword();
	void moveMSword();
	void mazeStateFogOfWar();
	void moveMShield();
	bool moveRHammer();
};

