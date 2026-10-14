#pragma once
#include "Maze.h"
#include<iostream>
#include<random>
#include<vector>
Cell::Cell() {}
Cell::Cell(unsigned int x, unsigned int y, char type) :x(x), y(y), cellType(type) {}
Cell& Cell:: operator=(char type) {
	this->cellType = type;
	return *this;
}
Cell& Cell:: operator=(const Cell& cell) {
	this->cellType = cell.cellType;
	this->x = cell.x;
	this->y = cell.y;
	return *this;
}

unsigned int Cell::getX() {
	return this->x;
}
unsigned int Cell::getY() {
	return this->y;
}
void Cell::setX(unsigned int x) {
	this->x = x;
}
void Cell::setY(unsigned int y) {
	this->y= y;
}
char Cell::getCellType() {
	return this->cellType;
}
void Cell::setCellType(char type) {
	this->cellType = type;
}
//Maze& Maze::operator=(Maze& maze2) {
//	this->x = maze2.x;
//	this->y = maze2.y;
//	this->itemNum = maze2.itemNum;
//	this->maze = new Cell * [x];
//	for (int i = 0;i < x;i++) {
//		maze[i] = new Cell[y];
//	}
//	for (int i = 0;i < x;i++) {
//		for (int j = 0;j < y;j++) {
//			(*this)[i][j] = maze2.maze[i][j];
//		}
//	}
//	return *this;
//}
Maze::Maze(unsigned int x, unsigned int y,unsigned int items) {
	this->x = x;
	this->y = y;
	this->itemNum = items;
	this->maze = new Cell* [x];
	for (int i = 0;i < x;i++) {
		maze[i] = new Cell[y];
	}
}

void Maze::dodajElement(Cell& cell) {
	maze[cell.getX()][cell.getY()] = cell;
}

Cell* Maze::operator[](unsigned int x) {
	return maze[x];
}
void Maze::mazeState() {
	for (int i = 0;i < x;i++) {
		for (int j = 0;j < y;j++) {
			std::cout << maze[i][j].getCellType();
		}
		std::cout << std::endl;
	}
}
Maze::~Maze() {
	for (unsigned int i = 0; i < x; i++) {
		delete[] maze[i];
	}
	delete[] maze;
}
unsigned int Maze::getRowNum() {
	return x;
}
unsigned int Maze::getColNum() {
	return y;
}
bool Maze::makeMaze() {
	int minBlocks = 2 * (x + y);
	int maxDots = x * y - 2 * x - 2 * (y - 2) - minBlocks;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> columns(1, y - 2);
	/*std::cout << "Random number: " << distr(gen) << std::endl;*/

	for (unsigned int i = 0;i < this->x;i++) {
		for (unsigned int j = 0;j < this->y;j++) {
			Cell c(i, j, ' ');
			this->dodajElement(c);
			if (i == 0 || i == x - 1 || j == 0 || j == y - 1) {
				(*this)[i][j] = '#';
			}
		}
	}

	int randFirstRowCol = columns(gen);
	int randLastRowCol = columns(gen);
	(*this)[0][randFirstRowCol] = 'U';
	(*this)[x - 1][randLastRowCol] = 'I';
	(*this)[1][randFirstRowCol] = 'R';

	int toTheLeft = 0;
	int toTheRight = 0;
	int res = randFirstRowCol - randLastRowCol;
	if (res < 0) {
		toTheRight = res;
	}
	else if (res > 0) {
		toTheLeft = res;
	}
	int i = 1, j = randFirstRowCol;
	int dotNum = 0;
	if (toTheLeft != 0 || toTheRight != 0) {
		std::string moveRL = "";
		if (toTheRight != 0) {
			moveRL = "right";
		}
		else if (toTheLeft != 0) {
			moveRL = "left";
		}

		std::uniform_int_distribution<> randDown(0, 1);//random dok se ne izravnaju ulaz i izlaz
		while (true) {
			if (i == x - 2) {
				if (moveRL == "right" && toTheRight != 0) {//slucaj kada je od pocetka isao samo dole i nije skrenuo dovoljno puta levo ili desno
					while (toTheRight != 0) {
						j++;
						(*this)[i][j] = '.';
						dotNum++;
						toTheRight++;
					}
					break;

				}
				else if (moveRL == "left" && toTheLeft != 0) {
					while (toTheLeft != 0) {
						j--;
						(*this)[i][j] = '.';
						dotNum++;
						toTheLeft--;
					}
					break;
				}
				else {
					break;
				}
			}
			else if (toTheLeft == 0 && toTheRight == 0) {
				break;
			}
			int move = randDown(gen);
			if (move == 0) {
				i++;
			}
			else if (move == 1) {
				if (moveRL == "right") {
					j++;
					toTheRight++;
					if (j >= y - 1) {
						j--;
						i++;
						toTheRight--;
					}
				}
				else if (moveRL == "left") {
					j--;
					toTheLeft--;
					if (j <= 0) {
						j++;
						i++;
						toTheLeft++;
					}
				}
			}
			(*this)[i][j] = '.';
			dotNum++;
		}
	}
	this->mazeState();
	if (i != x - 2) {
		int left = 0, right = 0;

		int move = 0;
		std::uniform_int_distribution<> randDLR(0, 2);
		while (true) {
			if (i == x - 2) {
				if (right > 0) {
					while (right != 0) {
						j++;
						(*this)[i][j] = '.';
						dotNum++;
						right--;
					}
				}
				else if (left > 0) {
					while (left != 0) {
						j--;
						(*this)[i][j] = '.';
						dotNum++;
						left--;
					}
				}
				break;
			}
			move = randDLR(gen);

			if (move == 0) {
				i++;
			}
			else if (move == 1) {
				j--;
				right++; //ako ode levo mora isto toliko desno
				left--;
				if (j <= 0) {
					j++;
					i++;
					right--;
					left++;
				}
			}
			else if (move == 2) {
				j++;
				left++;
				right--;
				if (j >= y - 1) {
					j--;
					i++;
					left--;
					right++;
				}
			}

			else
			{
				break;
			}
			(*this)[i][j] = '.';
			dotNum++;
		}
	}
	(*this)[1][randFirstRowCol] = 'R';//ako se poklope ulaz i izlaz i u prvom redu krenu da setaju tacke
	std::cout << dotNum << std::endl;

	std::vector<Cell>indexs;
	for (int i = 5;i < x-1;i++) {
		for (int j = 1;j < y-1;j++) {
			if ((*this)[i][j].getCellType() == '.') {
				indexs.push_back((*this)[i][j]);
			}
		}
	}
	this->mazeState();
	std::vector<std::string> positions = { "up","down","left","right" };
	std::uniform_int_distribution<> randPosition(0, positions.size() - 1);
	std::uniform_int_distribution<> randIndexs(0, indexs.size() - 1);
	int randIndex = randIndexs(gen);
	i = indexs[randIndex].getX();
	j = indexs[randIndex].getY();
	int indexPos = randPosition(gen);

	int iMinotaur = -1;
	int jMinotaur = -1;
	while (true) {
		if (positions[indexPos] == "up") {
			if (i - 2 > 0) {
				if ((*this)[i - 1][j].getCellType() == ' ') {
					(*this)[i - 1][j] = '.';
					(*this)[i - 2][j] = 'M';
					iMinotaur = i - 2;
					jMinotaur = j;
					dotNum++;
					break;
				}
			}
		}
		else if (positions[indexPos] == "down") {
			if (i + 2 <= x - 2) {
				if ((*this)[i + 1][j].getCellType() == ' ') {
					(*this)[i + 1][j] = '.';
					(*this)[i + 2][j] = 'M';
					iMinotaur = i + 2;
					jMinotaur = j;
					dotNum++;
					break;
				}
			}
		}
		else if (positions[indexPos] == "left") {
			if (j - 2 > 0) {
				if ((*this)[i][j - 1].getCellType() == ' ') {
					(*this)[i][j - 1] = '.';
					(*this)[i][j - 2] = 'M';
					iMinotaur = i;
					jMinotaur = j - 2;
					dotNum++;
					break;
				}
			}
		}
		else if (positions[indexPos] == "right") {
			if (j + 2 <= y - 2) {
				if ((*this)[i][j + 1].getCellType() == ' ') {
					(*this)[i][j + 1] = '.';
					(*this)[i][j + 2] = 'M';
					iMinotaur = i;
					jMinotaur = j + 2;
					dotNum++;
					break;
				}
			}
		}
		randIndex = randIndexs(gen);
		i = indexs[randIndex].getX();
		j = indexs[randIndex].getY();
		indexPos = randPosition(gen);
	}

	if (iMinotaur - 2 > 0) {
		if ((*this)[iMinotaur - 2][jMinotaur].getCellType() == ' ') {
			(*this)[iMinotaur - 2][jMinotaur] = '.';
			dotNum++;
		}
	}
	if (iMinotaur - 2 > 0 && jMinotaur - 2 > 0) {
		if ((*this)[iMinotaur - 2][jMinotaur - 2].getCellType() == ' ') {
			(*this)[iMinotaur - 2][jMinotaur - 2] = '.';
			dotNum++;
		}
	}
	if (iMinotaur - 2 > 0 && jMinotaur - 1 > 0) {
		if ((*this)[iMinotaur - 2][jMinotaur - 1].getCellType() == ' ') {
			(*this)[iMinotaur - 2][jMinotaur - 1] = '.';
			dotNum++;
		}
	}
	if (iMinotaur - 2 > 0 && jMinotaur + 2 <= y - 2) {
		if ((*this)[iMinotaur - 2][jMinotaur + 2].getCellType() == ' ') {
			(*this)[iMinotaur - 2][jMinotaur + 2] = '.';
			dotNum++;
		}
	}
	if (iMinotaur - 2 > 0 && jMinotaur + 1 <= y - 2) {
		if ((*this)[iMinotaur - 2][jMinotaur + 1].getCellType() == ' ') {
			(*this)[iMinotaur - 2][jMinotaur + 1] = '.';
			dotNum++;
		}
	}
	if (iMinotaur - 1 > 0) {
		if ((*this)[iMinotaur - 1][jMinotaur].getCellType() == ' ') {
			(*this)[iMinotaur - 1][jMinotaur] = '.';
			dotNum++;
		}
	}
	if (iMinotaur - 1 > 0 && jMinotaur - 1 > 0) {
		if ((*this)[iMinotaur - 1][jMinotaur - 1].getCellType() == ' ') {
			(*this)[iMinotaur - 1][jMinotaur - 1] = '.';
			dotNum++;
		}
	}
	if (iMinotaur - 1 > 0 && jMinotaur - 2 > 0) {
		if ((*this)[iMinotaur - 1][jMinotaur - 2].getCellType() == ' ') {
			(*this)[iMinotaur - 1][jMinotaur - 2] = '.';
			dotNum++;
		}
	}
	if (iMinotaur - 1 > 0 && jMinotaur + 1 <= y - 2) {
		if ((*this)[iMinotaur - 1][jMinotaur + 1].getCellType() == ' ') {
			(*this)[iMinotaur - 1][jMinotaur + 1] = '.';
			dotNum++;
		}
	}
	if (iMinotaur - 1 > 0 && jMinotaur + 2 <= y - 2) {
		if ((*this)[iMinotaur - 1][jMinotaur + 2].getCellType() == ' ') {
			(*this)[iMinotaur - 1][jMinotaur + 2] = '.';
			dotNum++;
		}
	}
	if (jMinotaur - 2 > 0) {
		if ((*this)[iMinotaur][jMinotaur - 2].getCellType() == ' ') {
			(*this)[iMinotaur][jMinotaur - 2] = '.';
			dotNum++;
		}
	}
	if (jMinotaur - 1 > 0) {
		if ((*this)[iMinotaur][jMinotaur - 1].getCellType() == ' ') {
			(*this)[iMinotaur][jMinotaur - 1] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 2 <= x - 2) {
		if ((*this)[iMinotaur + 2][jMinotaur].getCellType() == ' ') {
			(*this)[iMinotaur + 2][jMinotaur] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 2 <= x - 2 && jMinotaur - 2 > 0) {
		if ((*this)[iMinotaur + 2][jMinotaur - 2].getCellType() == ' ') {
			(*this)[iMinotaur + 2][jMinotaur - 2] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 2 <= x - 2 && jMinotaur - 1 > 0) {
		if ((*this)[iMinotaur + 2][jMinotaur - 1].getCellType() == ' ') {
			(*this)[iMinotaur + 2][jMinotaur - 1] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 2 <= x - 2 && jMinotaur + 2 <= y - 2) {
		if ((*this)[iMinotaur + 2][jMinotaur + 2].getCellType() == ' ') {
			(*this)[iMinotaur + 2][jMinotaur + 2] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 2 <= x - 2 && jMinotaur + 1 <= y - 2) {
		if ((*this)[iMinotaur + 2][jMinotaur + 1].getCellType() == ' ') {
			(*this)[iMinotaur + 2][jMinotaur + 1] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 1 <= x - 2) {
		if ((*this)[iMinotaur + 1][jMinotaur].getCellType() == ' ') {
			(*this)[iMinotaur + 1][jMinotaur] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 1 <= x - 2 && jMinotaur - 1 > 0) {
		if ((*this)[iMinotaur + 1][jMinotaur - 1].getCellType() == ' ') {
			(*this)[iMinotaur + 1][jMinotaur - 1] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 1 <= x - 2 && jMinotaur - 2 > 0) {
		if ((*this)[iMinotaur + 1][jMinotaur - 2].getCellType() == ' ') {
			(*this)[iMinotaur + 1][jMinotaur - 2] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 1 <= x - 2 && jMinotaur + 1 <= y - 2) {
		if ((*this)[iMinotaur + 1][jMinotaur + 1].getCellType() == ' ') {
			(*this)[iMinotaur + 1][jMinotaur + 1] = '.';
			dotNum++;
		}
	}
	if (iMinotaur + 1 <= x - 2 && jMinotaur + 2 <= y - 2) {
		if ((*this)[iMinotaur + 1][jMinotaur + 2].getCellType() == ' ') {
			(*this)[iMinotaur + 1][jMinotaur + 2] = '.';
			dotNum++;
		}
	}
	if (jMinotaur + 2 <= y - 2) {
		if ((*this)[iMinotaur][jMinotaur + 2].getCellType() == ' ') {
			(*this)[iMinotaur][jMinotaur + 2] = '.';
			dotNum++;
		}
	}
	if (jMinotaur + 2 <= y - 2) {
		if ((*this)[iMinotaur][jMinotaur + 1].getCellType() == ' ') {
			(*this)[iMinotaur][jMinotaur + 1] = '.';
			dotNum++;
		}
	}





	this->mazeState();


	std::cout << "Tren: " << dotNum << std::endl;
	std::cout << "Maks: " << maxDots << std::endl;
	if (dotNum > maxDots) {
		return false;
	}
	std::vector<Cell> empty;

	for (int i = 0;i < x;i++) {
		for (int j = 0;j < y;j++) {
			if ((*this)[i][j].getCellType() == ' ') {
				empty.push_back((*this)[i][j]);
			}
		}
	}
	
	int emptyIndex;
	for (int g = 0;g < minBlocks;g++) {
		std::uniform_int_distribution<> randEmptySpace(0, empty.size() - 1);
		emptyIndex = randEmptySpace(gen);
		i = empty[emptyIndex].getX();
		j = empty[emptyIndex].getY();
		(*this)[i][j] = '#';
		empty.erase(empty.begin()+emptyIndex);
	}
	this->mazeState();
	std::vector<Cell> itemCell;
	for (int i = 0;i < x;i++) {
		for (int j = 0;j < y;j++) {
			if ((*this)[i][j].getCellType() == ' ') {
				(*this)[i][j] = '.';
			}
			if ((*this)[i][j].getCellType() == '.') {
				itemCell.push_back((*this)[i][j]);
			}
		}
	}
	std::uniform_int_distribution<> randItemPos(0, itemCell.size() - 1);
	for (int i = 0;i < itemNum;i++) {
		int randIndexItem = randItemPos(gen);
		(*this)[itemCell[randIndexItem].getX()][itemCell[randIndexItem].getY()] = 'P';
	}
	return true;

	/*std::vector<Cell>indexs;
	for (int i = 0;i < x;i++) {
		for (int j = 0;j < y;j++) {
			if ((*this)[i][j].getCellType() == '.') {
				indexs.push_back((*this)[i][j]);
			}
		}
	}
	int dotsLeft = maxDots - dotNum;

	std::vector<std::string> positions = {"up","down","left","right"};
	std::uniform_int_distribution<> randPosition(0, positions.size() - 1);
	i = -1;
	j = -1;
	while (dotsLeft != 0) {
		std::uniform_int_distribution<> randIndexs(0, indexs.size() - 1);
		int randIndex = randIndexs(gen);
		i = indexs[randIndex].getX();
		j = indexs[randIndex].getY();
		int indexPos = randPosition(gen);
		if (positions[indexPos] == "up") {
			if (i - 1 > 0) {
				if ((*this)[i - 1][j].getCellType()==' ') {
					(*this)[i - 1][j] = '.';
					dotsLeft--;
					indexs.push_back((*this)[i -1][j]);
				}
			}
		}
		else if (positions[indexPos] == "down") {
			if (i + 1 <=x-2) {
				if ((*this)[i +1][j].getCellType() == ' ') {
					(*this)[i + 1][j] = '.';
					dotsLeft--;
					indexs.push_back((*this)[i+1][j]);
				}
			}
		}
		else if (positions[indexPos] == "left") {
			if (j- 1 >0) {
				if ((*this)[i][j-1].getCellType() == ' ') {
					(*this)[i][j-1] = '.';
					dotsLeft--;
					indexs.push_back((*this)[i][j - 1]);
				}
			}
		}
		else if (positions[indexPos] == "right") {
			if (j + 1 <=y-2) {
				if ((*this)[i][j +1].getCellType() == ' ') {
					(*this)[i][j + 1] = '.';
					dotsLeft--;
					indexs.push_back((*this)[i][j + 1]);
				}
			}
		}

	}
	this->mazeState();
	if (dotsLeft == 0) {
		for (int i = 0;i < x;i++) {
			for (int j = 0;j < y;j++) {
				if ((*this)[i][j].getCellType() == ' ') {
					(*this)[i][j] = '#';
				}
			}
		}
		return true;
	}*/
}