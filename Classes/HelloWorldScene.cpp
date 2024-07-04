#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	for (int i = 0; i < 360; i++)
	{
		sinTBL[i] = sin(i*0.0175);
		cosTBL[i] = cos(i*0.0175);
	}
	num = 50;
	srand(time(nullptr));
	schedule(schedule_selector(HelloWorld::CreateBullet), 2.0f, 100000, 0.0f);
	schedule(schedule_selector(HelloWorld::Createblue), 4.0f, 100000, 0.0f);
	scheduleUpdate();
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label_ = Label::createWithTTF("Dodge", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label_->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label_->getContentSize().height));

    // add the label as a child to this layer

	auto K_listner = EventListenerKeyboard::create();
	K_listner->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	K_listner->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(K_listner, this);

    this->addChild(label_, 1);

	Player = new Cship(this);

	for (int i = 0; i < 50; i++)
	{
		Cbullet *Bullet = new Cbullet(this);
		Bullet->Move();
		bullet.push_back(Bullet);
	}

	PlayTime = GetTickCount();

	sprintf(PlayTime_, "%.2f sec", 0.00);
	label = Label::createWithSystemFont(PlayTime_, "Marker Felt.ttf", 20);
	label->setPosition(Vec2(500, 700));
	this->addChild(label);

	sprintf(BulletCount_, "%d bullet", 50);
	count = Label::createWithSystemFont(BulletCount_, "Marker Felt.ttf", 20);
	count->setPosition(Vec2(500, 680));
	this->addChild(count);
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if ((keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && Player->y < 748))
	{
		up = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && Player->y > 0)
	{
		down = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && Player->x > 20)
	{
		left = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && Player->x < 1004)
	{
		right = true;
	}
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		up = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		down = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		left = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		right = false;
	}
}
bool HelloWorld::colliosionCheck(Rect box1, Rect box2)
{
	return box1.intersectsRect(box2);
}

void HelloWorld::CreateBullet(float dt)
{
	Cbullet *Bullet = new Cbullet(this);
	Bullet->Move();
	bullet.push_back(Bullet);
	sprintf(BulletCount_, "%d bullet", ++num);
	count->setString(BulletCount_);
}

void HelloWorld::update(float dt)
{
	Targetting();
	if (up == true && Player->y < 748)
	{
		Player->y += 3;
	}
	else if (down == true && Player->y > 0)
	{
		Player->y -= 3;
	}
	if (left == true && Player->x > 20)
	{
		Player->x -= 3;
	}
	else if (right == true && Player->x < 1004)
	{
		Player->x += 3;
	}
	Player->Move(Player->x, Player->y);
	///////////////////////////////////
	for (bullet_itr = bullet.begin(); bullet_itr < bullet.end(); bullet_itr++)
	{
		if (colliosionCheck(Player->ship->getBoundingBox(), (*bullet_itr)->bullet->getBoundingBox()))
		{
			/*CCDirector::sharedDirector()->pause();*/
		}
	}
	/////////////////////////////////////
	static float a = 0;
	if (GetTickCount() - PlayTime >= 10 && PlayTime > 0)
	{
		a = a + 0.01f;
		PlayTime = GetTickCount();
		sprintf(PlayTime_, "%.2f sec", a);
		label->setString(PlayTime_);
	}

}
void HelloWorld::Targetting()
{
	for (blue_itr = blue.begin(); blue_itr < blue.end(); blue_itr++)
	{
		int bx = (*blue_itr)->bullet->getPosition().x, by = (*blue_itr)->bullet->getPosition().y;
		temp = (int)((atan2(abs(Player->ship->getPosition().y - by), abs(Player->ship->getPosition().x - bx))) * 180) / 3.14;
		if (Player->ship->getPosition().y - by> 0)
		{
			if (Player->ship->getPosition().x - bx > 0)
				temp = temp + 90;
			else
				temp = 270 - temp;
		}
		else
		{
			if (Player->ship->getPosition().x - bx > 0)
				temp = 90 - temp;
			else
				temp = 270 + temp;
		}
		bx += sinTBL[temp] * 2;
		by -= cosTBL[temp] * 2;
		(*blue_itr)->fallow(bx, by);
	}
}

void HelloWorld::Createblue(float dt)
{
	Cbullet *Blue = new Cbullet(this);
	Blue->bullet->setTexture("blue_bullet.png");
	Blue->Move();
	blue.push_back(Blue);
	Targetting();
	sprintf(BulletCount_, "%d bullet", ++num);
	count->setString(BulletCount_);
}