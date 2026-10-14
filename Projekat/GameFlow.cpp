#include<iostream>
#include"GameFlow.h"

GameFlow::GameFlow(Game* game):game(game){}
GameFlow::~GameFlow() {
	delete game;
	game = nullptr;
}
bool GameFlow::Move(){
	bool gameOn = true;
	if (game->getItem() == NULL) {
		gameOn=game->moveR();
		if (!gameOn) {
			return false;
		}
		game->moveM();
		game->getMaze().mazeState();
	}
	else {
		if (game->getItem()->getName() == "Sword") {
			gameOn=(*game).moveRSword();
			if (!gameOn) {
				return false;
			}
			game->getItem()->decreaseItemDuration();
			if (game->getEnd() == true) {
				std::cout << "Kraj";
				return false;
			}
			(*game).moveMSword();
			game->getMaze().mazeState();
		}
		else if (game->getItem()->getName() == "Fog of War") {
			gameOn=game->moveR();
			if (!gameOn) {
				return false;
			}
			game->getItem()->decreaseItemDuration();
			game->moveM();
			(*game).mazeStateFogOfWar();
		}
		else if (game->getItem()->getName() == "Shield") {
			gameOn=game->moveR();
			if (!gameOn) {
				return false;
			}
			game->getItem()->decreaseItemDuration();
			(*game).moveMShield();
			game->getMaze().mazeState();
		}
		else if (game->getItem()->getName() == "Hammer") {
			gameOn= (*game).moveRHammer();
			if (!gameOn) {
				return false;
			}
			game->getItem()->decreaseItemDuration();
			game->moveM();
			game->getMaze().mazeState();
		}
		if (game->getItem()->getItemDuration() <= 0) {
			game->nullItem();
		}
	}
	if (game->getItem() != NULL) {
		std::cout << "Aktivan item: " << game->getItem()->getName() << std::endl;
	}
	if (game->getEnd() == true || game->getMaze()[game->getIEnd() - 1][game->getJEnd()].getCellType() == 'R') {
		return false;
	}
	return true;

	
}