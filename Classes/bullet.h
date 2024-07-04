#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Cbullet
{
public:
	int x, y;
	Sprite *bullet;
	Cbullet(Layer* layer);
	void Move();
	void fallow(int x,int y);
};