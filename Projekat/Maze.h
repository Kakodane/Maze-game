#pragma once
class Cell {
	unsigned int x, y;
	char cellType;

public:
	Cell();
	Cell(unsigned int x, unsigned int y, char type);
	Cell& operator=(char type);
	Cell& operator=(const Cell& cell);
	unsigned int getX();
	void setX(unsigned int x);
	unsigned int getY();
	void setY(unsigned int y);
	char getCellType();
	void setCellType(char type);

};


class Maze {
	unsigned int x, y;
	unsigned int itemNum;
	Cell** maze;
public:
	Maze(){}
	Maze(unsigned int x, unsigned int y,unsigned int items);
	void dodajElement(Cell& cell);
	Cell* operator[](unsigned int x);
	void mazeState();
	bool makeMaze();
	~Maze();
	unsigned int getRowNum();
	unsigned int getColNum();
	//Maze& operator=(Maze& maze);


};