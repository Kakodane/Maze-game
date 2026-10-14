#pragma once
#include "Game.h"

class GameFlow {
	Game* game;

public:
	GameFlow(Game* game);
	bool Move();
	~GameFlow();
};