#include "Bullet.h"

USING_NS_CC;

Bullet* Bullet::createWithSpriteName(const char* spriteName) 
{
	Bullet* bullet = new Bullet();
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(spriteName);

	if (bullet && bullet->initWithTexture(texture)) {

		/*auto body = PhysicsBody::createBox(bullet->getContentSize());

		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x03);

		bullet->setPhysicsBody(body);*/
		return bullet;
	}
	return NULL;
}

//本函数暂时被置空 202106160008
void Bullet::shootBulletFromKnight(Knight* knight,Enemy *enemy)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 enemyPos = enemy->getPosition() + visibleSize / 2;

	runAction(MoveTo::create(0.2, enemyPos));//remove


	
	//setPosition(knight->getPosition());
	//setVisible(true);


	//scheduleUpdate();

}

void Bullet::update(float dt) 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	setPosition(Vec2(getPosition() + velocity * dt));

	if (getPosition().y > visibleSize.height) 
	{
		setVisible(false);
		unscheduleUpdate();
		removeFromParent();
	}
}



void Bullet::bulletRotate(Bullet* bullet, Knight* knight, Enemy* enemy)//子弹围绕敌人旋转
{
	Vec2 enemyPos = enemy->getPosition();
	Vec2 knightPos = knight->getPosition();
	double len_y = enemyPos.y - knightPos.y;
	double len_x = enemyPos.x - knightPos.x;
	double tan_yx = tan_yx = abs(len_y) / abs(len_x);
	float angle = 0;
	if (len_y > 0 && len_x < 0) {
		angle = atan(tan_yx) * 180 / M_PI - 90;
	}
	else if (len_y > 0 && len_x > 0) {
		angle = 90 - atan(tan_yx) * 180 / M_PI;
	}
	else if (len_y < 0 && len_x < 0) {
		angle = -atan(tan_yx) * 180 / M_PI - 90;
	}
	else if (len_y < 0 && len_x > 0) {
		angle = atan(tan_yx) * 180 / M_PI + 90;
	}
	bullet->setRotation(angle + 90);
}



void Bullet::bulletfalse(float dt)//设置子弹（定时）消失
{
	removeFromParent();
}


/*void Bullet::ShootManyTimes(Bullet* bullet, Vec2 knightPos, Vec2 enemyPos, Knight* playerKnight, Enemy* enemy)
{
	bullet->runAction(MoveTo::create(0.2, enemyPos));
	bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.2, 0, 0.2);


	bullet = Bullet::createWithSpriteName("bullet2.png");
	addChild(bullet, 10);
	bullet->setPosition(knightPos);
	bullet->bulletRotate(bullet, playerKnight, enemy);
	bullet->runAction(MoveTo::create(0.1, enemyPos));
	bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.1, 0, 0.1);


	bullet = Bullet::createWithSpriteName("bullet2.png");
	addChild(bullet, 10);
	bullet->setPosition(knightPos);
	bullet->bulletRotate(bullet, playerKnight, enemy);
	bullet->runAction(MoveTo::create(0.3, enemyPos));
	bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.3, 0, 0.3);
}*/