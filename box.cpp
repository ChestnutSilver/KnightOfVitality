#include "box.h"

USING_NS_CC;

Box* Box::createWithSpriteName(const char* spriteName)
{
	Box* box = new Box();
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(spriteName);

	if (box && box->initWithTexture(texture)) 
	{		
		return box;
	}
	return NULL;
}