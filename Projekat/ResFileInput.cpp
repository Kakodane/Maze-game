
#include "ResFileInput.h"

ResFileInput::ResFileInput(std::string f) : f(f) {}
void ResFileInput::writeInFile(Game* game) {
	Maze maze = game->getMaze();
	std::ofstream fileRes(f);
	bool rAlive = false, mAlive = false;
	for (int i = 0;i < game->getMaze().getRowNum();i++) {
		for (int j = 0;j < game->getMaze().getColNum();j++) {
			fileRes << maze[i][j].getCellType();
			if (maze[i][j].getCellType() == 'R')
			{
				rAlive = true;
			}
			else if (maze[i][j].getCellType() == 'M') {
				mAlive = true;
			}
		}
		fileRes << "\n";
	}
	if (rAlive && mAlive && maze[game->getIEnd() - 1][game->getJEnd()].getCellType() == 'R') {
		fileRes << "\n";
		fileRes << "Robot je pobedio";
	}
	else if (rAlive && mAlive) {
		fileRes << "Igra je prekinuta";
	}
	else if (rAlive) {
		fileRes << "\n";
		fileRes << "Robot je pobedio";
	}
	else if (mAlive) {
		fileRes << "\n";
		fileRes << "Minotaur je pobedio";
	}
	
	fileRes.close();
}