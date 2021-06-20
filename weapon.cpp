#include "weapon.h"

USING_NS_CC;

Weapon* Weapon::createWithSpriteName(const char* spriteName)
{
	Weapon* weapon = new Weapon();
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(spriteName);

	if (weapon && weapon->initWithTexture(texture)) {

		/*auto body = PhysicsBody::createBox(bullet->getContentSize());

		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x03);

		bullet->setPhysicsBody(body);*/
		return weapon;
	}
	return NULL;
}

void Weapon::weaponRotate(Weapon* weapon, Knight* knight, Enemy* enemy)//×Óµ¯Î§ÈÆµÐÈËÐý×ª
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
	weapon->setRotation(angle + 90);
}