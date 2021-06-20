#include "MyScene.h"
#include "HelloWorldScene.h"
#include "safeground.h"

USING_NS_CC;

Scene* CMyScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CMyScene::create();
    scene->addChild(layer);
    return scene;
}

// 当文件不存在时，打印有用的错误消息而不是分段。  Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool CMyScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //???
    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png", CC_CALLBACK_1(CMyScene::menuCloseCallback, this));
    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);



    auto sprite = Sprite::create("start.png");
    if (sprite == nullptr)
    {
        problemLoading("'start.png'");
    }
    else
    {
        // 将精灵放置在屏幕中央    position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // 将精灵作为子对象添加到此层  add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }


    

    //MoustEvent();
    return true;
}



//???
void CMyScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application


    // Director::getInstance()->end();

    const int initcoin = 100;
    auto scene = safeground::createScene(initcoin, NULL);
    Director::getInstance()->replaceScene(scene);


    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


/*void CMyScene::MoustEvent()
{
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [](Event* event)
    {
        EventMouse* e = (EventMouse*)event;

        auto safeground = HelloWorld::createScene();
        Director::getInstance()->replaceScene(safeground);

    };
}*/

CMyScene::CMyScene()
{

}


CMyScene::~CMyScene()
{


}

