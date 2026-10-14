#pragma once
#include<iostream>
class Item {
protected:
	unsigned int itemDuration;
	std::string itemName;
public:
	Item(unsigned int dur, std::string name);
	virtual std::string getName() = 0;
	unsigned int getItemDuration();
	void decreaseItemDuration();
};
class FogOfWar:public Item {
public:
	FogOfWar(unsigned int dur, std::string name);
	std::string getName();
};
class Sword :public Item {
public:
	Sword(unsigned int dur, std::string name);
	std::string getName();
};
class Shield :public Item {
public:
	Shield(unsigned int dur, std::string name);
	std::string getName();
};
class Hammer :public Item {
public:
	Hammer(unsigned int dur, std::string name);
	std::string getName();
};