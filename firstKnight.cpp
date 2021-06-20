#include "firstKnight.h"
#include "battleground.h"
USING_NS_CC;

//骑士精灵的移动速度；数值越小，移动速度越大
const double moveSpeed = 0.5;
bool choiceProp = false;
int propUpbuff = 0, propDowndebuff = 0, propRandom = 0, Pause = 0, Exit = 0;
//本函数已使用setPosition语句简化
/*void Knight::initPosition(const cocos2d::Vec2& pos) 
{
	setPosition(pos);
	//setAnchorPoint(Vec2(0.5f, 0.5f));
}*/

Knight* Knight::createWithSpriteName(const char* spriteName, int knightGrade, int knightType)
{
	Knight* knight = new Knight();

	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(spriteName);


	initSettings(knight, knightGrade, knightType);

	if (knight && knight->initWithTexture(texture)) {
		return knight;
	}

	return NULL;
}


Knight* Knight::createWithSpriteName(const char* spriteName, int knightGrade, int knightType, std::vector<bool>props)
{
	Knight* knight = new Knight();

	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(spriteName);


	initSettings(knight, knightGrade, knightType, props);

	if (knight && knight->initWithTexture(texture)) {
		return knight;
	}



	return NULL;
}

void Knight::initSettings(Knight* knight, int knightGrade, int knightType)
{
	double k = 100;
	if (knightGrade == 1)
		k = 100;
	else if (knightGrade == 2)
		k = 120;
	else if (knightGrade == 3)
		k = 150;


	/* 进行基本参数初始化 */
	if (knightGrade == 1 || knightGrade == 2 || knightGrade == 3)
	{
		knight->setHitPoints(k);
		knight->setManaPoints(k);
		knight->setArmorPoints(100);
		knight->setInitHitPoints(k);
		knight->setInitManaPoints(k);
		knight->setInitArmorPoints(100);
		if (knightType == 2)
		{
			knight->setHitPoints(k * 1.1);
			knight->setInitHitPoints(k * 1.1);
		}
	}

	if (knightType == 1)
	{
		knight->setMyMovespeed(8);
		knight->setMyHurt(1.05f);
		knight->setMyGetHurt(1.1f);
	}
	else if (knightType == 2)
	{
		knight->setMyMovespeed(12);
		knight->setMyHurt(1.0f);
		knight->setMyGetHurt(0.9f);
	}

	knight->setPlaceType(0);
	knight->setAddcoin(0);
	knight->setSwampSpeed(0);
	knight->setAddspeed(0);
	knight->setDespeed(0);
	knight->setNoenemy(false);

	Pause = 0;
	Exit = 0;
}

 
void Knight::initSettings(Knight* knight, int knightGrade, int knightType, std::vector<bool>props)
{
	double k = 100;
	if (knightGrade == 1)
		k = 100;
	else if (knightGrade == 2)
		k = 120;
	else if (knightGrade == 3)
		k = 150;


	if (props[0] == true || propUpbuff > 0)
		knight->setUpbuff(1.2);
	else
		knight->setUpbuff(1.0);


	if (props[1] == true || propDowndebuff > 0)
		knight->setDowndebuff(0.8);
	else
		knight->setDowndebuff(1.0);


	if (props[2] == true || propRandom > 0)
	{
		srand(time(0));
		if (rand() % 2 == 0)
		{
			knight->setUpbuff(1.2);
			knight->setDowndebuff(1.0);
		}
		else
		{
			knight->setUpbuff(1.0);
			knight->setDowndebuff(0.8);
		}
	}

	/* 进行基本参数初始化 */
	if (knightGrade == 1 || knightGrade == 2 || knightGrade == 3)
	{
		knight->setHitPoints(k);
		knight->setManaPoints(k);
		knight->setArmorPoints(100);
		knight->setInitHitPoints(k);
		knight->setInitManaPoints(k);
		knight->setInitArmorPoints(100);
		if (knightType == 2)
		{
			knight->setHitPoints(k * 1.1);
			knight->setInitHitPoints(k * 1.1);
		}
	}

	if (knightType == 1)
	{
		knight->setMyMovespeed(8);
		knight->setMyHurt(1.05f);
		knight->setMyGetHurt(1.1f);
	}
	else if (knightType == 2)
	{
		knight->setMyMovespeed(12);
		knight->setMyHurt(1.0f);
		knight->setMyGetHurt(0.9f);
	}

	knight->setPlaceType(0);
	knight->setAddcoin(0);
	knight->setSwampSpeed(0);
	knight->setAddspeed(0);
	knight->setDespeed(0);
	knight->setNoenemy(false);
}

void Knight::moveStep(int dir)
{
	//定义两个位置，和之前初始化位置时的方法一样
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//安全场地中，战斗场地入口的位置
	const double entranceLeftX = visibleSize.width / 2 + origin.x - 50;
	const double entranceRightX = visibleSize.width / 2 + origin.x + 130;
	const double entranceUpY = visibleSize.height / 2 + origin.y + 220;


	auto pos = getPosition();

	if (dir == 1)
		pos.y += STEP;
	else if (dir == 2)
		pos.y -= STEP;
	else if (dir == 3)
		pos.x -= STEP;
	else if (dir == 4)
		pos.x += STEP;

	runAction(MoveTo::create(moveSpeed, pos));  //使骑士精灵移动到pos处，移动一步的时间为moveSpeed（const）



	//意图：当骑士精灵的位置走到指定位置（此处为入口处）时，切换至相应的场景
	if (pos.x > entranceLeftX && pos.x < entranceRightX && pos.y > entranceUpY)
	{
		auto scene = BattleGround::createScene();
		Director::getInstance()->replaceScene(scene);  //切换场景

	}


}

//显示血量条，传入骑士，和参数（百分号前面的数字）
void Knight::getBloodbar(Knight* playerKnight, float a, int SCENE)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();


	cocos2d::TMXTiledMap* smallMap;

	if (SCENE == 1)
	    smallMap = TMXTiledMap::create("battleone.tmx");
	else if (SCENE == 2)
		smallMap = TMXTiledMap::create("battletwo.tmx");

	smallMap->setPosition(visibleSize.width / 2 - 300, visibleSize.height / 2 - 300);

	addChild(smallMap, 1000);
	smallMap->setScale(0.060);

	Label* label = Label::createWithSystemFont("explored", "Arial", 18);
	label->setColor(Color3B::GREEN);
	if (playerKnight->getPlaceType() == 0)
	{
		if (SCENE == 1)
			label->setPosition(visibleSize.width / 2 - 210, visibleSize.height / 2 - 15);
		else if (SCENE == 2)
			label->setPosition(visibleSize.width / 2 - 110, visibleSize.height / 2 - 213);
		this->addChild(label, 1001);
	}
	else if (playerKnight->getPlaceType() == 1)
	{
		Label* label1 = label;
		if (SCENE == 1)
			label1->setPosition(visibleSize.width / 2 - 110, visibleSize.height / 2 - 15);
		else if (SCENE == 2)
			label1->setPosition(visibleSize.width / 2 - 110, visibleSize.height / 2 - 114);
		this->addChild(label1, 1001);
	}
	else if (playerKnight->getPlaceType() == 2)
	{
		Label* label2 = label;
		if (SCENE == 1)
			label2->setPosition(visibleSize.width / 2 - 110, visibleSize.height / 2 - 114);
		else if (SCENE == 2)
			label2->setPosition(visibleSize.width / 2 - 110, visibleSize.height / 2 - 15);
		this->addChild(label2, 1001);
	}
	else if (playerKnight->getPlaceType() == 3)
	{
		Label* label3 = label;
		label3->setPosition(visibleSize.width / 2 - 10, visibleSize.height / 2 - 114);
		this->addChild(label3, 1001);
	}
	else if (playerKnight->getPlaceType() == 4)
	{
		Label* label4 = label;
		if (SCENE == 1)
			label4->setPosition(visibleSize.width / 2 - 210, visibleSize.height / 2 - 114);
		else if (SCENE == 2)
			label4->setPosition(visibleSize.width / 2 - 10, visibleSize.height / 2 - 15);
		this->addChild(label4, 1001);
	}
	else if (playerKnight->getPlaceType() == 5)
	{
		Label* label5 = label;
		label5->setPosition(visibleSize.width / 2 - 210, visibleSize.height / 2 - 114);
		this->addChild(label5, 1001);
	}

	choiceProps(playerKnight, SCENE);


}

void Knight::choiceProps(Knight* playerKnight, int SCENE)
{
	/*********************/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	

	auto Prop1Item = MenuItemImage::create("Prop1.png", "Prop1.png", CC_CALLBACK_1(Knight::prop1Callback, this));
	Prop1Item->setPosition(Vec2(visibleSize.width / 2-800, visibleSize.height / 2));
	auto menu3 = Menu::create(Prop1Item, NULL);
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3, 1);

	Label* Prop1Type;
	if (choiceProp == false)
	{
		Prop1Type = Label::createWithSystemFont("You can get (only) a prop FREE.", "Arial", 18);
		Prop1Type->setColor(Color3B::YELLOW);
		Prop1Type->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height / 2 + 10));
		this->addChild(Prop1Type, 1001);
	}


	/**/
	auto Prop2Item = MenuItemImage::create("Prop2.png", "Prop2.png", CC_CALLBACK_1(Knight::prop2Callback, this));
	Prop2Item->setPosition(Vec2(visibleSize.width / 2-700, visibleSize.height / 2));
	auto menu4 = Menu::create(Prop2Item, NULL);
	menu4->setPosition(Vec2::ZERO);
	this->addChild(menu4, 1);

	auto Prop3Item = MenuItemImage::create("Prop3.png", "Prop3.png", CC_CALLBACK_1(Knight::prop3Callback, this));
	Prop3Item->setPosition(Vec2(visibleSize.width / 2-600, visibleSize.height / 2));
	auto menu5 = Menu::create(Prop3Item, NULL);
	menu5->setPosition(Vec2::ZERO);
	this->addChild(menu5, 1);


	pauseAndExit();
}
void Knight::pauseAndExit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto setItem = MenuItemImage::create("set.png", "set.png", CC_CALLBACK_1(Knight::setCallback, this));
	setItem->setPosition(Vec2(visibleSize.width / 2 - 950, visibleSize.height / 2-100));
	setItem->setScale(0.5);
	auto menuset = Menu::create(setItem, NULL);
	menuset->setPosition(Vec2::ZERO);
	this->addChild(menuset, 1);

	auto exitItem = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(Knight::exitCallback, this));
	exitItem->setPosition(Vec2(visibleSize.width / 2 - 950, visibleSize.height / 2-150));
	exitItem->setScale(0.5);
	auto menuexit = Menu::create(exitItem, NULL);
	menuexit->setPosition(Vec2::ZERO);
	this->addChild(menuexit, 1);
}


void Knight::setCallback(Ref* pSender)
{
	Pause++;
}
void Knight::exitCallback(Ref* pSender)
{
	Exit++;
}

void Knight::prop1Callback(Ref* pSender)
{
	if (choiceProp == true)
		return;
	choiceProp = true;
	propUpbuff++;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Label* labelProp1 = Label::createWithSystemFont("selected the 1st!", "Arial", 18);
	labelProp1->setColor(Color3B::GREEN);
	labelProp1->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height / 2-20));
	this->addChild(labelProp1, 1001);
}

void Knight::prop2Callback(Ref* pSender)
{
	if (choiceProp == true)
		return;
	choiceProp = true;
	propDowndebuff++;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Label* labelProp2 = Label::createWithSystemFont("selected the 2nd!", "Arial", 18);
	labelProp2->setColor(Color3B::GREEN);
	labelProp2->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height / 2-20));
	this->addChild(labelProp2, 1001);
}

void Knight::prop3Callback(Ref* pSender)
{
	if (choiceProp == true)
		return;
	choiceProp = true;
	propRandom++;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Label* labelProp3 = Label::createWithSystemFont("selected the 3rd!", "Arial", 18);
	labelProp3->setColor(Color3B::GREEN);
	labelProp3->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height / 2-20));
	this->addChild(labelProp3, 1001);
}

bool Knight::choicePause()
{
	if (Pause % 2 == 1)
	{
		Pause = 0;
		return true;
	}

	else
		return false;
}

bool Knight::choiceExit()
{
	if (Exit >= 1)
		return true;
	else
		return false;
}


bool Knight::choiceProp2()
{
	if (propDowndebuff >= 1)
		return true;
	else
		return false;
}




bool Knight::choiceProp1()
{
	if (propUpbuff >= 1)
		return true;
	else
		return false;
}



bool Knight::choiceProp3()
{
	if (propRandom >= 1)
		return true;
	else
		return false;
}


void Knight::TrapTerrain(Vec2 knightPos, Knight* playerKnight)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*机关地形：岩浆*/
	if (knightPos.x > visibleSize.width / 2 + 200 && knightPos.x < visibleSize.width / 2 + 280 && knightPos.y>visibleSize.height / 2 + 1370 && knightPos.y < visibleSize.height / 2 + 1890)
		playerKnight->setHitPoints(playerKnight->getHitPoints() - 2);
	/*机关地形：地刺*/
	if (knightPos.x > visibleSize.width / 2 - 220 && knightPos.x < visibleSize.width / 2 + 220 && knightPos.y>visibleSize.height / 2 - 200 && knightPos.y < visibleSize.height / 2 - 120)
		playerKnight->setHitPoints(playerKnight->getHitPoints() - 2);
	/*机关地形：沼泽*/
	if (knightPos.x > visibleSize.width / 2 - 45 && knightPos.x < visibleSize.width / 2 + 45 && knightPos.y>visibleSize.height / 2 + 640 && knightPos.y < visibleSize.height / 2 + 1080)
		playerKnight->setSwampSpeed(-20);
	else
		playerKnight->setSwampSpeed(0);
}