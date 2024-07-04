#include "ship.h"

Cship::Cship(Layer* layer)
{
	x = 512;
	y = 384;
	ship = Sprite::create("ship.png");
	ship->setPosition(x, y);
	ship->setScale(0.4f);
	layer->addChild(ship, 1);
}

void Cship::Move(int _x, int _y)
{
	ship->setPosition(_x, _y);
}