#pragma once
#include<iostream>
#include<fstream>
#include "Game.h"

class ResFileInput {
	std::string f;
public:
	ResFileInput(std::string f);
	void writeInFile(Game* game);
};