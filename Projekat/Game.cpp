
#include "Game.h"
#include<iostream>
#include<random>
#include <chrono>
Game::Game(unsigned int rowCount, unsigned int colCount, unsigned int itemCount) :maze(new Maze(rowCount, colCount, itemCount)), activeItem(NULL), end(false), lastPosCharR('x') , lastPosCharM('x') {
	auto start = std::chrono::high_resolution_clock::now();
	while (true) {
		bool success = (*maze).makeMaze();
		if (success) {
			break;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Vreme pravljenja lavirinta: " << elapsed.count() << std::endl;
	for (int i = 1;i < (*maze).getRowNum()-1;i++) {
		for (int j = 1;j < (*maze).getColNum()-1;j++) {
			if ((*maze)[i][j].getCellType() == 'R') {
				iPos = i;
				jPos = j;
			}
			else if ((*maze)[i][j].getCellType() == 'M') {
				iMPos = i;
				jMPos = j;
			}
		}
	}
	for (int j = 1;j < (*maze).getColNum() - 1;j++) {
		if ((*maze)[(*maze).getRowNum() - 1][j].getCellType() == 'I') {
			iEnd = (*maze).getRowNum() - 1;
			jEnd = j;
			break;

		}
	}
	
	items.push_back(new FogOfWar(3, "Fog of War"));
	items.push_back(new Sword(3, "Sword"));
	items.push_back(new Sword(3, "Shield"));
	items.push_back(new Sword(3, "Hammer"));
}
Maze& Game::getMaze() {
	return *maze;
}
void Game::generateItem() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randItem(0, this->items.size() - 1);
	int randItemIndex = randItem(gen);
	if (this->items[randItemIndex]->getName() == "Fog of War") {
		this->activeItem = new FogOfWar(3, "Fog of War");
	}
	else if (this->items[randItemIndex]->getName() == "Sword") {
		this->activeItem = new Sword(3, "Sword");
	}
	else if (this->items[randItemIndex]->getName() == "Shield") {
		this->activeItem = new Sword(3, "Shield");
	}
	else if (this->items[randItemIndex]->getName() == "Hammer") {
		this->activeItem = new Sword(3, "Hammer");
	}
	
}
Item* Game::getItem() {
	return activeItem;
}
void Game::nullItem() {
	activeItem = NULL;
}
bool Game::moveR() {
	
	char move;
	while (true) {
		std::cout << "Unesite slovo: ";
		std::cin >> move;
		std::cin.ignore(100, '\n');
		if (move != 'w' && move != 'a' && move != 's' && move != 'd' && move !='q') {
			continue;
		}
		if (move == 'q') {
			return false;
		}
		break;
	}
		if (move=='w'&&iPos - 1 > 0) {
			if ((*maze)[iPos - 1][jPos].getCellType() == '.'|| (*maze)[iPos - 1][jPos].getCellType() == 'P') {
				char temp = (*maze)[iPos - 1][jPos].getCellType();
				if (temp == 'P') {
					temp = '.';
					generateItem();
				}
				(*maze)[iPos - 1][jPos] = (*maze)[iPos][jPos].getCellType();
				if (lastPosCharR != 'x')
					(*maze)[iPos][jPos] = lastPosCharR;
				else
					(*maze)[iPos][jPos] = '.';
				lastPosCharR = temp;
				iPos--;
				
			}
		}
		else if (move == 'a' && jPos - 1 > 0) {
			if ((*maze)[iPos][jPos-1].getCellType() == '.' || (*maze)[iPos][jPos-1].getCellType() == 'P') {
				char temp = (*maze)[iPos][jPos-1].getCellType();
				if (temp == 'P') {
					temp = '.';
					generateItem();
				}
				(*maze)[iPos][jPos-1] = (*maze)[iPos][jPos].getCellType();
				if (lastPosCharR != 'x')
					(*maze)[iPos][jPos] = lastPosCharR;
				else
					(*maze)[iPos][jPos] = '.';
				lastPosCharR = temp;
				jPos--;
				
			}
		}else if(move == 's' && iPos + 1 > 0) {
			if ((*maze)[iPos + 1][jPos].getCellType() == '.' || (*maze)[iPos + 1][jPos].getCellType() == 'P') {
				char temp = (*maze)[iPos + 1][jPos].getCellType();
				if (temp == 'P') {
					temp = '.';
					generateItem();
				}
				(*maze)[iPos + 1][jPos] = (*maze)[iPos][jPos].getCellType();
				if (lastPosCharR != 'x')
					(*maze)[iPos][jPos] = lastPosCharR;
				else
					(*maze)[iPos][jPos] = '.';
				lastPosCharR = temp;
				iPos++;
				
			}
		}
		else if (move == 'd' && jPos + 1 > 0) {
			if ((*maze)[iPos][jPos+1].getCellType() == '.' || (*maze)[iPos][jPos+1].getCellType() == 'P') {
				char temp = (*maze)[iPos][jPos+1].getCellType();
				if (temp == 'P') {
					temp = '.';
					generateItem();
				}
				(*maze)[iPos][jPos+1] = (*maze)[iPos][jPos].getCellType();
				if (lastPosCharR != 'x')
					(*maze)[iPos][jPos] = lastPosCharR;
				else
					(*maze)[iPos][jPos] = '.';
				lastPosCharR = temp;
				jPos++;
				
			}
		}
			
		return true;
	
	

}

void Game::moveM() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<std::string> positions = { "up","down","left","right" };
	std::uniform_int_distribution<> randPosition(0, positions.size() - 1);
	char temp;
	if (iMPos - 1 > 0) {
		if ((*maze)[iMPos - 1][jMPos].getCellType() == 'R') {
			temp = (*maze)[iMPos-1][jMPos].getCellType();
			(*maze)[iMPos - 1][jMPos] = (*maze)[iMPos][jMPos].getCellType();
			if (lastPosCharM != 'x') {
				(*maze)[iMPos][jMPos] = lastPosCharM;
			}
			else
				(*maze)[iMPos][jMPos] = '.';
			lastPosCharM = temp;
			iMPos--;
			end = true;
			return;
		}
	}
	if(jMPos - 1 > 0) {
		if ((*maze)[iMPos][jMPos-1].getCellType() == 'R') {
			temp = (*maze)[iMPos][jMPos-1].getCellType();
			(*maze)[iMPos][jMPos-1] = (*maze)[iMPos][jMPos].getCellType();
			if (lastPosCharM != 'x') {
				(*maze)[iMPos][jMPos] = lastPosCharM;
			}
			else
				(*maze)[iMPos][jMPos] = '.';
			lastPosCharM = temp;
			jMPos--;
			end = true;
			return;
		}
	}
	if (iMPos +1 <=(*maze).getRowNum()-1) {
		if ((*maze)[iMPos +1][jMPos].getCellType() == 'R') {
			temp = (*maze)[iMPos + 1][jMPos].getCellType();
			(*maze)[iMPos + 1][jMPos] = (*maze)[iMPos][jMPos].getCellType();
			if (lastPosCharM != 'x') {
				(*maze)[iMPos][jMPos] = lastPosCharM;
			}
			else
				(*maze)[iMPos][jMPos] = '.';
			lastPosCharM = temp;
			iMPos++;
			end = true;
			return;
		}
	}
	if (jMPos + 1 <=(*maze).getColNum()-1) {
		if ((*maze)[iMPos][jMPos + 1].getCellType() == 'R') {
			temp = (*maze)[iMPos][jMPos + 1].getCellType();
			(*maze)[iMPos][jMPos + 1] = (*maze)[iMPos][jMPos].getCellType();
			if (lastPosCharM != 'x') {
				(*maze)[iMPos][jMPos] = lastPosCharM;
			}
			else
				(*maze)[iMPos][jMPos] = '.';
			lastPosCharM = temp;
			jMPos++;
			end = true;
			return;
		}
	}
	while (true) {
		int randMove = randPosition(gen);
		if (positions[randMove] == "up"&& iMPos - 1 > 0) {
				if ((*maze)[iMPos - 1][jMPos].getCellType() == '.'|| (*maze)[iMPos - 1][jMPos].getCellType() == 'P') {
					temp = (*maze)[iMPos - 1][jMPos].getCellType();
					if (temp == 'P') {
						temp = '.';
					}
					(*maze)[iMPos - 1][jMPos] = (*maze)[iMPos][jMPos].getCellType();
					if (lastPosCharM != 'x') {
						(*maze)[iMPos][jMPos] = lastPosCharM;
					}
					else
						(*maze)[iMPos][jMPos] = '.';
					lastPosCharM = temp;
					iMPos--;
					return;
				
				}
		}
		else if (positions[randMove] == "left" && jMPos - 1 > 0) {
			if ((*maze)[iMPos][jMPos - 1].getCellType() == '.' || (*maze)[iMPos][jMPos-1].getCellType() == 'P') {
				temp = (*maze)[iMPos][jMPos - 1].getCellType();
				if (temp == 'P') {
					temp = '.';
				}
				(*maze)[iMPos][jMPos - 1] = (*maze)[iMPos][jMPos].getCellType();
				if (lastPosCharM != 'x') {
					(*maze)[iMPos][jMPos] = lastPosCharM;
				}
				else
					(*maze)[iMPos][jMPos] = '.';
				lastPosCharM = temp;
				jMPos--;
				return;
			}
		}
		else if (positions[randMove] == "down" && iMPos + 1 <= (*maze).getRowNum() - 1) {
			if ((*maze)[iMPos + 1][jMPos].getCellType() == '.' || (*maze)[iMPos + 1][jMPos].getCellType() == 'P') {
				temp = (*maze)[iMPos + 1][jMPos].getCellType();
				if (temp == 'P') {
					temp = '.';
				}
				(*maze)[iMPos + 1][jMPos] = (*maze)[iMPos][jMPos].getCellType();
				if (lastPosCharM != 'x') {
					(*maze)[iMPos][jMPos] = lastPosCharM;
				}
				else
					(*maze)[iMPos][jMPos] = '.';
				lastPosCharM = temp;
				iMPos++;
				return;
			}
		}
		else if (positions[randMove] == "right" && jMPos + 1 <= (*maze).getColNum() - 1) {
			if ((*maze)[iMPos][jMPos + 1].getCellType() == '.' || (*maze)[iMPos][jMPos+1].getCellType() == 'P') {
				temp = (*maze)[iMPos][jMPos + 1].getCellType();
				if (temp == 'P') {
					temp = '.';
				}
				(*maze)[iMPos][jMPos + 1] = (*maze)[iMPos][jMPos].getCellType();
				if (lastPosCharM != 'x') {
					(*maze)[iMPos][jMPos] = lastPosCharM;
				}
				else
					(*maze)[iMPos][jMPos] = '.';
				lastPosCharM = temp;
				jMPos++;
				return;
			}
		}
	}
}

bool Game::getEnd() {
	return end;
}

bool Game::moveRSword() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randItem(0, this->items.size() - 1);
	char move;
	while (true) {
		std::cout << "Unesite slovo: ";
		std::cin >> move;
		if (move != 'w' && move != 'a' && move != 's' && move != 'd' && move != 'q') {
			continue;
		}
		if (move == 'q') {
			return false;
		}
		break;
	}
		if (move == 'w' && this->iPos - 1 > 0) {
			if ((*this->maze)[this->iPos - 1][this->jPos].getCellType() == '.'|| (*this->maze)[this->iPos - 1][this->jPos].getCellType() == 'M' || (*this->maze)[this->iPos - 1][this->jPos].getCellType() == 'P') {
				char temp = (*this->maze)[this->iPos - 1][this->jPos].getCellType();
				if (temp == 'P') {
					temp = '.';
					generateItem();
				}
				else if (temp == 'M') {
					this->end = true;
				}
				(*this->maze)[this->iPos - 1][this->jPos] = (*this->maze)[this->iPos][this->jPos].getCellType();;
				if (this->lastPosCharR != 'x')
					(*this->maze)[this->iPos][this->jPos] = this->lastPosCharR;
				else
					(*this->maze)[this->iPos][this->jPos] = '.';
				this->lastPosCharR = temp;
				this->iPos--;
				
			}
		}
		else if (move == 'a' && this->jPos - 1 > 0) {
			if ((*this->maze)[this->iPos][this->jPos - 1].getCellType() == '.' || (*this->maze)[this->iPos][this->jPos-1].getCellType() == 'M' || (*this->maze)[this->iPos][this->jPos-1].getCellType() == 'P') {
				char temp = (*this->maze)[this->iPos][this->jPos - 1].getCellType();
				if (temp == 'P') {
					temp = '.';
					generateItem();
				}
				else if (temp == 'M') {
					this->end = true;
				}
				(*this->maze)[this->iPos][this->jPos - 1] = (*this->maze)[this->iPos][this->jPos].getCellType();
				if (this->lastPosCharR != 'x')
					(*this->maze)[this->iPos][this->jPos] = this->lastPosCharR;
				else
					(*this->maze)[this->iPos][this->jPos] = '.';
				this->lastPosCharR = temp;
				this->jPos--;
				
			}
		}
		else if (move == 's' && this->iPos + 1 > 0) {
			if ((*this->maze)[this->iPos + 1][this->jPos].getCellType() == '.' || (*this->maze)[this->iPos + 1][this->jPos].getCellType() == 'M' || (*this->maze)[this->iPos + 1][this->jPos].getCellType() == 'P') {
				char temp = (*this->maze)[this->iPos + 1][this->jPos].getCellType();
				if (temp == 'P') {
					temp = '.';
					generateItem();
				}
				else if (temp == 'M') {
					this->end = true;
				}
				(*this->maze)[this->iPos + 1][this->jPos] = (*this->maze)[this->iPos][this->jPos].getCellType();
				if (this->lastPosCharR != 'x')
					(*this->maze)[this->iPos][this->jPos] = this->lastPosCharR;
				else
					(*this->maze)[this->iPos][this->jPos] = '.';
				this->lastPosCharR = temp;
				this->iPos++;
				
			}
		}
		else if (move == 'd' && this->jPos + 1 > 0) {
			if ((*this->maze)[this->iPos][this->jPos + 1].getCellType() == '.' || (*this->maze)[this->iPos][this->jPos+1].getCellType() == 'M' || (*this->maze)[this->iPos][this->jPos+1].getCellType() == 'P') {
				char temp = (*this->maze)[this->iPos][this->jPos + 1].getCellType();
				if (temp == 'P') {
					temp = '.';
					generateItem();
				}
				else if (temp == 'M') {
					this->end = true;
				}
				(*this->maze)[this->iPos][this->jPos + 1] = (*this->maze)[this->iPos][this->jPos].getCellType();
				if (this->lastPosCharR != 'x')
					(*this->maze)[this->iPos][this->jPos] = this->lastPosCharR;
				else
					(*this->maze)[this->iPos][this->jPos] = '.';
				this->lastPosCharR = temp;
				this->jPos++;
				
			}
		}

		return true;
	

}

void Game::moveMSword() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::vector<std::string> positions = { "up","down","left","right" };
		std::uniform_int_distribution<> randPosition(0, positions.size() - 1);
		char temp;
		if (this->iMPos - 1 > 0) {
			if ((*this->maze)[this->iMPos - 1][this->jMPos].getCellType() == 'R') {
				temp = (*this->maze)[this->iMPos - 1][this->jMPos].getCellType();//zadrzava karakter
				if (this->lastPosCharM != 'x') {
					(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
				}
				else
					(*this->maze)[this->iMPos][this->jMPos] = '.';
				this->lastPosCharM = temp;
				this->iMPos--;
				this->end = true;
				return;
			}
		}
		if (this->jMPos - 1 > 0) {
			if ((*this->maze)[this->iMPos][this->jMPos - 1].getCellType() == 'R') {
				temp = (*this->maze)[this->iMPos][this->jMPos - 1].getCellType();
				if (this->lastPosCharM != 'x') {
					(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
				}
				else
					(*this->maze)[this->iMPos][this->jMPos] = '.';
				this->lastPosCharM = temp;
				this->jMPos--;
				this->end = true;
				return;
			}
		}
		if (this->iMPos + 1 <= (*this->maze).getRowNum() - 1) {
			if ((*this->maze)[this->iMPos + 1][this->jMPos].getCellType() == 'R') {
				temp = (*this->maze)[this->iMPos + 1][this->jMPos].getCellType();
				if (this->lastPosCharM != 'x') {
					(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
				}
				else
					(*this->maze)[this->iMPos][this->jMPos] = '.';
				this->lastPosCharM = temp;
				this->iMPos++;
				this->end = true;
				return;
			}
		}
		if (this->jMPos + 1 <= (*this->maze).getColNum() - 1) {
			if ((*this->maze)[this->iMPos][this->jMPos + 1].getCellType() == 'R') {
				temp = (*this->maze)[this->iMPos][this->jMPos + 1].getCellType();
				if (this->lastPosCharM != 'x') {
					(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
				}
				else
					(*this->maze)[this->iMPos][this->jMPos] = '.';
				this->lastPosCharM = temp;
				this->jMPos++;
				this->end = true;
				return;
			}
		}
		while (true) {
			int randMove = randPosition(gen);
			if (positions[randMove] == "up" && this->iMPos - 1 > 0) {
				if ((*this->maze)[this->iMPos - 1][this->jMPos].getCellType() == '.' || (*this->maze)[this->iMPos - 1][this->jMPos].getCellType() == 'P') {
					temp = (*this->maze)[this->iMPos - 1][this->jMPos].getCellType();
					if (temp == 'P') {
						temp = '.';
					}
					(*this->maze)[this->iMPos - 1][this->jMPos] = (*this->maze)[this->iMPos][this->jMPos].getCellType();
					if (this->lastPosCharM != 'x') {
						(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
					}
					else
						(*this->maze)[this->iMPos][this->jMPos] = '.';
					this->lastPosCharM = temp;
					this->iMPos--;
					return;

				}
			}
			else if (positions[randMove] == "left" && this->jMPos - 1 > 0) {
				if ((*this->maze)[this->iMPos][this->jMPos - 1].getCellType() == '.' || (*this->maze)[this->iMPos][this->jMPos - 1].getCellType() == 'P') {
					temp = (*this->maze)[this->iMPos][this->jMPos - 1].getCellType();
					if (temp == 'P') {
						temp = '.';
					}
					(*this->maze)[this->iMPos][this->jMPos - 1] = (*this->maze)[this->iMPos][this->jMPos].getCellType();
					if (this->lastPosCharM != 'x') {
						(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
					}
					else
						(*this->maze)[this->iMPos][this->jMPos] = '.';
					this->lastPosCharM = temp;
					this->jMPos--;
					return;
				}
			}
			else if (positions[randMove] == "down" && this->iMPos + 1 <= (*this->maze).getRowNum() - 1) {
				if ((*this->maze)[this->iMPos + 1][this->jMPos].getCellType() == '.' || (*this->maze)[this->iMPos + 1][this->jMPos].getCellType() == 'P') {
					temp = (*this->maze)[this->iMPos + 1][this->jMPos].getCellType();
					if (temp == 'P') {
						temp = '.';
					}
					(*this->maze)[this->iMPos + 1][this->jMPos] = (*this->maze)[this->iMPos][this->jMPos].getCellType();
					if (this->lastPosCharM != 'x') {
						(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
					}
					else
						(*this->maze)[this->iMPos][this->jMPos] = '.';
					this->lastPosCharM = temp;
					this->iMPos++;
					return;
				}
			}
			else if (positions[randMove] == "right" && this->jMPos + 1 <= (*this->maze).getColNum() - 1) {
				if ((*this->maze)[this->iMPos][this->jMPos + 1].getCellType() == '.' || (*this->maze)[this->iMPos][this->jMPos + 1].getCellType() == 'P') {
					temp = (*this->maze)[this->iMPos][this->jMPos + 1].getCellType();
					if (temp == 'P') {
						temp = '.';
					}
					(*this->maze)[this->iMPos][this->jMPos + 1] = (*this->maze)[this->iMPos][this->jMPos].getCellType();
					if (this->lastPosCharM != 'x') {
						(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
					}
					else
						(*this->maze)[this->iMPos][this->jMPos] = '.';
					this->lastPosCharM = temp;
					this->jMPos++;
					return;
				}
			}
		}
	

}

void Game::mazeStateFogOfWar() {
	int red = this->iPos-1;
	for (int g = 0;g < 3;g++) {
		for (int j = this->jPos-1;j < this->jPos + 2;j++) {
			std::cout << (*this->maze)[red][j].getCellType();
		}
		red++;
		std::cout<<std::endl;
	}
}

void Game::moveMShield() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<std::string> positions = { "up","down","left","right" };
	std::uniform_int_distribution<> randPosition(0, positions.size() - 1);
	char temp;
	
	while (true) {
		int randMove = randPosition(gen);
		if (positions[randMove] == "up" && this->iMPos - 1 > 0) {
			if ((*this->maze)[this->iMPos - 1][this->jMPos].getCellType() == '.' || (*this->maze)[this->iMPos - 1][this->jMPos].getCellType() == 'P') {
				temp = (*this->maze)[this->iMPos - 1][this->jMPos].getCellType();
				if (temp == 'P') {
					temp = '.';
				}
				(*this->maze)[this->iMPos - 1][this->jMPos] = (*this->maze)[this->iMPos][this->jMPos].getCellType();
				if (this->lastPosCharM != 'x') {
					(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
				}
				else
					(*this->maze)[this->iMPos][this->jMPos] = '.';
				this->lastPosCharM= temp;
				this->iMPos--;
				return;

			}
		}
		else if (positions[randMove] == "left" && this->jMPos - 1 > 0) {
			if ((*this->maze)[this->iMPos][this->jMPos - 1].getCellType() == '.' || (*this->maze)[this->iMPos][this->jMPos - 1].getCellType() == 'P') {
				temp = (*this->maze)[this->iMPos][this->jMPos - 1].getCellType();
				if (temp == 'P') {
					temp = '.';
				}
				(*this->maze)[this->iMPos][this->jMPos - 1] = (*this->maze)[this->iMPos][this->jMPos].getCellType();
				if (this->lastPosCharM != 'x') {
					(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
				}
				else
					(*this->maze)[this->iMPos][this->jMPos] = '.';
				this->lastPosCharM = temp;
				this->jMPos--;
				return;
			}
		}
		else if (positions[randMove] == "down" && this->iMPos + 1 <= (*this->maze).getRowNum() - 1) {
			if ((*this->maze)[this->iMPos + 1][this->jMPos].getCellType() == '.' || (*this->maze)[this->iMPos + 1][this->jMPos].getCellType() == 'P') {
				temp = (*this->maze)[this->iMPos + 1][this->jMPos].getCellType();
				if (temp == 'P') {
					temp = '.';
				}
				(*this->maze)[this->iMPos + 1][this->jMPos] = (*this->maze)[this->iMPos][this->jMPos].getCellType();
				if (this->lastPosCharM != 'x') {
					(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
				}
				else
					(*this->maze)[this->iMPos][this->jMPos] = '.';
				this->lastPosCharM = temp;
				this->iMPos++;
				return;
			}
		}
		else if (positions[randMove] == "right" && this->jMPos + 1 <= (*this->maze).getColNum() - 1) {
			if ((*this->maze)[this->iMPos][this->jMPos + 1].getCellType() == '.' || (*this->maze)[this->iMPos][this->jMPos + 1].getCellType() == 'P') {
				temp = (*this->maze)[this->iMPos][this->jMPos + 1].getCellType();
				if (temp == 'P') {
					temp = '.';
				}
				(*this->maze)[this->iMPos][this->jMPos + 1] = (*this->maze)[this->iMPos][this->jMPos].getCellType();
				if (this->lastPosCharM != 'x') {
					(*this->maze)[this->iMPos][this->jMPos] = this->lastPosCharM;
				}
				else
					(*this->maze)[this->iMPos][this->jMPos] = '.';
				this->lastPosCharM = temp;
				this->jMPos++;
				return;
			}
		}
	}

}

bool Game::moveRHammer() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randItem(0, this->items.size() - 1);
	char move;
	while (true) {
		std::cout << "Unesite slovo: ";
		std::cin >> move;
		if (move != 'w' && move != 'a' && move != 's' && move != 'd' && move != 'q') {
			continue;
		}
		if (move == 'q') {
			return false;
		}
		break;
	}
	if (move == 'w' && this->iPos - 1 > 0) {
		if ((*this->maze)[this->iPos - 1][this->jPos].getCellType() == '.' || (*this->maze)[this->iPos - 1][this->jPos].getCellType() == '#' || (*this->maze)[this->iPos - 1][this->jPos].getCellType() == 'P') {
			char temp = (*this->maze)[this->iPos - 1][this->jPos].getCellType();
			if (temp == 'P') {
				temp = '.';
				generateItem();
			}
			(*this->maze)[this->iPos - 1][this->jPos] = (*this->maze)[this->iPos][this->jPos].getCellType();
			if (this->lastPosCharR != 'x')
				(*this->maze)[this->iPos][this->jPos] = this->lastPosCharR;
			else
				(*this->maze)[this->iPos][this->jPos] = '.';
			this->lastPosCharR = temp;
			this->iPos--;

		}
	}
	else if (move == 'a' && this->jPos - 1 > 0) {
		if ((*this->maze)[this->iPos][this->jPos - 1].getCellType() == '.' || (*this->maze)[this->iPos][this->jPos - 1].getCellType() == '#' || (*this->maze)[this->iPos][this->jPos - 1].getCellType() == 'P') {
			char temp = (*this->maze)[this->iPos][this->jPos - 1].getCellType();
			if (temp == 'P') {
				temp = '.';
				generateItem();
			}
			(*this->maze)[this->iPos][this->jPos - 1] = (*this->maze)[this->iPos][this->jPos].getCellType();
			if (this->lastPosCharR != 'x')
				(*this->maze)[this->iPos][this->jPos] = this->lastPosCharR;
			else
				(*this->maze)[this->iPos][this->jPos] = '.';
			this->lastPosCharR = temp;
			this->jPos--;

		}
	}
	else if (move == 's' && this->iPos + 1 > 0) {
		if ((*this->maze)[this->iPos + 1][this->jPos].getCellType() == '.' || (*this->maze)[this->iPos + 1][this->jPos].getCellType() == '#' || (*this->maze)[this->iPos + 1][this->jPos].getCellType() == 'P') {
			char temp = (*this->maze)[this->iPos + 1][this->jPos].getCellType();
			if (temp == 'P') {
				temp = '.';
				generateItem();
			}
			(*this->maze)[this->iPos + 1][this->jPos] = (*this->maze)[this->iPos][this->jPos].getCellType();
			if (this->lastPosCharR != 'x')
				(*this->maze)[this->iPos][this->jPos] = this->lastPosCharR;
			else
				(*this->maze)[this->iPos][this->jPos] = '.';
			this->lastPosCharR = temp;
			this->iPos++;

		}
	}
	else if (move == 'd' && this->jPos + 1 > 0) {
		if ((*this->maze)[this->iPos][this->jPos + 1].getCellType() == '.' || (*this->maze)[this->iPos][this->jPos + 1].getCellType() == '#' || (*this->maze)[this->iPos][this->jPos + 1].getCellType() == 'P') {
			char temp = (*this->maze)[this->iPos][this->jPos + 1].getCellType();
			if (temp == 'P') {
				temp = '.';
				generateItem();
			}
			(*this->maze)[this->iPos][this->jPos + 1] = (*this->maze)[this->iPos][this->jPos].getCellType();
			if (this->lastPosCharR != 'x')
				(*this->maze)[this->iPos][this->jPos] = this->lastPosCharR;
			else
				(*this->maze)[this->iPos][this->jPos] = '.';
			this->lastPosCharR = temp;
			this->jPos++;

		}
	}

	return true;
}

unsigned int Game::getIEnd() {
	return iEnd;
}
unsigned int Game::getJEnd() {
	return jEnd;
}

Game::~Game() {
	delete maze;
	maze = nullptr;
	for (Item*& item : items) {//referenca na pokazivac bez toga ne moze da se menja na sta pointer pokazuje, bez toga moze da se menja vrednost onoga na sta pointer pokazuje ali bi menjanje pointer bilo lokalno
		delete item;
		item = nullptr;

	}
	delete activeItem;
	activeItem = nullptr;
}