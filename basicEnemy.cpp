#include "basicEnemy.h"
#include "battleground.h"
USING_NS_CC;

Enemy* Enemy::createWithSpriteName(const char* spriteName)
{
	Enemy* enemy = new Enemy();


	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(spriteName);

	if (enemy && enemy->initWithTexture(texture)) {
		//enemy->moveRandom();
		//enemy->scheduleUpdate();
		return enemy;
	}

	return NULL;

}

Enemy* Enemy::NearestEnemy(int BulletType,Vec2 knightPos, Vector<Enemy*> enemyArray)
{
	double distance = 300;
	if (BulletType == 3 || BulletType == 4)//近身武器
		distance = 80;

	for (Enemy* enemy : enemyArray)
	{
		Vec2 enemyPos = enemy->getPosition();
		double temp = pow((pow(fabs(knightPos.x - enemyPos.x), 2)) + (pow(fabs(knightPos.y - enemyPos.y), 2)), 0.5);
		if (temp < distance && enemy->getAlive() == true)
		{
			distance = temp;
		}
	}
	for (Enemy* enemy : enemyArray)
	{
		Vec2 enemyPos = enemy->getPosition();
		double temp = pow((pow(fabs(knightPos.x - enemyPos.x), 2)) + (pow(fabs(knightPos.y - enemyPos.y), 2)), 0.5);
		if (fabs(temp - distance) < 0.01)
		{
			return enemy;
		}
	}
	return NULL;
}



	//Enemy* e = new Enemy();



	/*e->init(pos);

	e->moveRandom(pos);

	e->scheduleUpdate();

	e->autorelease();
	return e;*/

/*void Enemy::moveRandom()//回调函数update()每一秒调一次函数
{
	Vec2 pos = enemy->getPosition();

	srand(unsigned int(time(0)));
	int i = rand() % 4;

	if (i == 0)
	{
		pos.x -= 0.5;
		enemy->setFlippedX(true);
	}
	else if (i == 1)
	{
		pos.x += 0.5;
		enemy->setFlippedX(false);
	}
	else if (i == 2)
	{
		pos.y -= 0.5;
	}
	else if (i == 3)
	{
		pos.y += 0.5;
	}

	enemy->runAction(MoveTo::create(0.05, pos));

	enemy->setPosition(pos);
}

void Enemy::update(float dt)
{
	//Vec2 pos = enemy->getPosition();//!!!!!!!
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (1)//(pos.x > visibleSize.width / 2 - 200 && pos.x < visibleSize.width / 2 + 200 && pos.y<visibleSize.height / 2 + 200 && pos.y > visibleSize.height / 2 - 200)
		moveRandom();
}*/
/*bool Enemy::init(cocos2d::Vec2& pos)
{
	Sprite::init();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	srand(unsigned int(time(0)));
	int i = rand() % 4;

	switch (i)
	{
		case 0:
		{
			enemy = Sprite::create("enemyice1.png");
			break;
		}
		case 1:
		{
			enemy = Sprite::create("enemyice2.png");
			break;
		}
		case 2:
		{
			enemy = Sprite::create("enemyice3.png");
			break;
		}
		case 3:
		{
			enemy = Sprite::create("enemyice4.png");
			break;
		}
	}

	enemy->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));



	//enemy->setPhysicsBody(PhysicsBody::createBox(enemy->getContentSize()));
	//enemy->getPhysicsBody()->setContactTestBitmask(1);
	//enemy->getPhysicsBody()->setTag(3);

	//enemy->runAction(Sequence::create(MoveTo::create(0.5f, Point(10, p)), CallFuncN::create(CC_CALLBACK_0(Enemy::rm, this)), NULL));
	addChild(enemy);


	return true;
}

void Enemy::moveRandom(cocos2d::Vec2& pos)//回调函数update()每一秒调一次函数
{

	srand(unsigned int(time(0)));
	int i = rand() % 4;

	if (i == 0)
	{
		pos.x -= 0.5;
		enemy->setFlippedX(true);
	}
	else if (i == 1)
	{
		pos.x += 0.5;
		enemy->setFlippedX(false);
	}
	else if (i == 2)
	{
		pos.y -= 0.5;
	}
	else if (i == 3)
	{
		pos.y += 0.5;
	}

	enemy->runAction(MoveTo::create(0.05, pos));

	enemy->setPosition(pos);
}


void Enemy::update(float dt)
{
	Vec2 pos = enemy->getPosition();//!!!!!!!
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (1)//(pos.x > visibleSize.width / 2 - 200 && pos.x < visibleSize.width / 2 + 200 && pos.y<visibleSize.height / 2 + 200 && pos.y > visibleSize.height / 2 - 200)
		moveRandom(pos);
}*/