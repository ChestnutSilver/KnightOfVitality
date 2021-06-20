#pragma once
#include "cocos2d.h"
#include "firstKnight.h"

class Box :public cocos2d::Sprite
{
public:

	static Box* createWithSpriteName(const char* spriteName);

};