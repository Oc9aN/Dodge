#include "bullet.h"

Cbullet::Cbullet(Layer *layer)
{
	bullet = Sprite::create("red_bullet.png");
	bullet->setScale(0.1f);
	layer->addChild(bullet, 1);
}

void Cbullet::Move()
{
	int a;
	a = rand() % 2;
	if (a == 0)
	{
		x = (rand() % 2) * 1024;
		y = rand() % 768;
		bullet->setPosition(Vec2(x, y));
	}
	else
	{
		x = rand() % 1024;
		y = (rand() % 2) * 768;
		bullet->setPosition(Vec2(x, y));
	}
	auto move = MoveTo::create(rand() % 10 + 3, Vec2(1024 - x, 768 - y));
	auto seq = Sequence::create(move, CallFunc::create(CC_CALLBACK_0(Cbullet::Move, this)), nullptr);
	bullet->runAction(seq);
}

void Cbullet::fallow(int x, int y)
{
	bullet->stopAllActions();
	bullet->setPosition(x, y);
}
