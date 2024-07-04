#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Cship
{
public:
	int x, y;
	Sprite *ship;
	Cship(Layer* layer);
	void Move(int _x,int _y);
};