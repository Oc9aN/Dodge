#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ship.h"
#include "bullet.h"
#include <vector>

class HelloWorld : public cocos2d::Layer
{
public:
	int num;

	double sinTBL[360];
	double cosTBL[360];
	int temp;
	void Targetting();
	std::vector<Cbullet*> blue;
	std::vector<Cbullet*>::iterator blue_itr;
	void Createblue(float dt);

    static cocos2d::Scene* createScene();

	std::vector<Cbullet*> bullet;
	std::vector<Cbullet*>::iterator bullet_itr;

    virtual bool init();

	bool colliosionCheck(Rect box1, Rect box2);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	bool right,left,up,down;

	void CreateBullet(float dt);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	Cship *Player;
	void update(float dt);

	int PlayTime;
	char PlayTime_[30];
	Label *label;

	char BulletCount_[30];
	Label *count;
};

#endif // __HELLOWORLD_SCENE_H__
