
#include<iostream>
#include "Item.h"

Item::Item(unsigned int dur, std::string name) :itemDuration(dur), itemName(name) {}
unsigned int Item::getItemDuration() {
	return itemDuration;
}
void Item::decreaseItemDuration() {
	itemDuration--;
}
FogOfWar::FogOfWar(unsigned int dur, std::string name) :Item(dur, name) {}
std::string FogOfWar::getName() {
	return itemName;
}

Sword::Sword(unsigned int dur, std::string name) :Item(dur, name) {}
std::string Sword::getName() {
	return itemName;
}

Shield::Shield(unsigned int dur, std::string name) :Item(dur, name) {}
std::string Shield::getName() {
	return itemName;
}

Hammer::Hammer(unsigned int dur, std::string name) :Item(dur, name) {}
std::string Hammer::getName() {
	return itemName;
}