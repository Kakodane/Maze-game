
#include<iostream>
#include<fstream>
#include "Game.h"
#include "ResFileInput.h"
#include "GameFlow.h"

bool params(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "Broj argumenata nije dobar!" << std::endl;
		return false;
	}
	try {
		int firstParam = atoi(argv[1]);
		if (firstParam <= 15) {
			std::cout << "Prvi parametar mora biti veci od 15" << std::endl;
			return false;
		}
		int secondParam = atoi(argv[2]);
		if (secondParam <= 15) {
			std::cout << "Drugi parametar mora biti veci od 15" << std::endl;
			return false;
		}
		int thirdParam = atoi(argv[3]);
		if (thirdParam <= 3) {
			std::cout << "Treci parametar mora biti veci od 3" << std::endl;
			return false;
		}
	}
	catch(...){
		std::cout << "Argumenti moraj da budu brojevi" << std::endl;
		return false;
	}
	return true;
	
	
}

int main(int argc, char* argv[]) {
	if (!params(argc, argv)) {
		std::cout << "Pokusajte ponovo" << std::endl;
		return 1;
	}
	int param1 = atoi(argv[1]);
	int param2 = atoi(argv[2]);
	int param3 = atoi(argv[3]);
	Game *game=new Game(param1,param2,param3);
	game->getMaze().mazeState();
	ResFileInput* resInput = new ResFileInput("Rezultat igre.txt");
	GameFlow *gf = new GameFlow(game);
	bool move = true;
	while (move) {
		move = gf->Move();
	}
	std::cout << "Kraj";
	resInput->writeInFile(game);


	return 0;
}