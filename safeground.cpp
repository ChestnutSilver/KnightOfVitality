#include "HelloWorldScene.h"
#include "safeground.h"
#include "firstKnight.h"
USING_NS_CC;

int addgrade = 0, addtype = 0, prop1 = 0, prop2 = 0, prop3 = 0;
Label* labelGrade;
Label* labelType;
Label* labelGrade1;
Label* labelType1;
Label* labelCoin;
Scene* safeground::createScene(int coinsum, Knight* knight)
{
    auto scene = Scene::create();
    auto layer = safeground::create();
    scene->addChild(layer);

    addgrade = 0;
    addtype = 0;
    prop1 = 0;
    prop2 = 0;
    prop3 = 0;
    layer->setCoin(coinsum);
    layer->myCoinSum(coinsum);
    layer->setKnightGrade(1);
    
    return scene;
}
void safeground::myCoinSum(int coinsum)
{
    std::string coinlabel = "Coin:" + std::to_string(coinsum);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    labelCoin = Label::createWithSystemFont(coinlabel, "Arial", 22);
    
    labelCoin->setColor(Color3B::YELLOW);
   
    labelCoin->setPosition(visibleSize.width / 2 + 400, visibleSize.height / 2 + 300);
        
    this->addChild(labelCoin, 1001);
}
// 当文件不存在时，打印有用的错误消息而不是分段。  Print useful error message instead of segfaulting when files are not there.
/*static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}*/

bool safeground::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto labelStore = Label::createWithSystemFont("PROP STORE", "Arial", 24);
    labelStore->setColor(Color3B::GREEN);
    labelStore->setPosition(Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y + 120));
    this->addChild(labelStore, 1001);

    auto sprite = Sprite::create("safeground.png");
    // 将精灵放置在屏幕中央    position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    // 将精灵作为子对象添加到此层  add the sprite as a child to this layer
    this->addChild(sprite, 0);

    //加入精灵：骑士精灵，并设置骑士的初始位置

    knight = Knight::createWithSpriteName("Knight.png", 1, 1);
    knight->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
          /*initPosition*/
    this->addChild(knight, 0);
    

    /*点击！*/
    auto upgradeItem = MenuItemImage::create("setGrade.png", "setGrade.png", CC_CALLBACK_1(safeground::upgradeCallback, this));
    upgradeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x + 400, visibleSize.height / 2 + origin.y + 150));
    auto menu = Menu::create(upgradeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    labelGrade = Label::createWithSystemFont("Click the blue coin to upgrade!(coin 10)\nKnight: LV.1\nMaxHP: 100\nMaxArmor: 100\nMaxMP: 100", "Arial", 18);
    labelGrade->setColor(Color3B::YELLOW);
    labelGrade->setPosition(Vec2(visibleSize.width / 2 + origin.x + 400, visibleSize.height / 2 + origin.y + 60));
    this->addChild(labelGrade, 1001);



    auto changeTypeItem = MenuItemImage::create("Knight2nd.png", "Knight2nd.png", CC_CALLBACK_1(safeground::changeTypeCallback, this));
    changeTypeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x + 410, visibleSize.height / 2 + origin.y - 50));
    auto menu2 = Menu::create(changeTypeItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);


    labelType = Label::createWithSystemFont("Click the knight to change!(FREE)\nKnight: 1st\nMovespeed: basic+20%\nHurt: basic+5%\nGetHurt: basic+10%\nMaxHP: basic+0%", "Arial", 18);
    labelType->setColor(Color3B::YELLOW);
    labelType->setPosition(Vec2(visibleSize.width / 2 + origin.x + 360, visibleSize.height / 2 + origin.y - 160));
    this->addChild(labelType, 1001);




    /*********************/
    auto Prop1Item = MenuItemImage::create("Prop1.png", "Prop1.png", CC_CALLBACK_1(safeground::prop1Callback, this));
    Prop1Item->setPosition(Vec2(visibleSize.width / 2 + origin.x - 410, visibleSize.height / 2 + origin.y + 80));
    auto menu3 = Menu::create(Prop1Item, NULL);
    menu3->setPosition(Vec2::ZERO);
    this->addChild(menu3, 1);

    auto Prop1Type = Label::createWithSystemFont("Click the prop to strengthen buff!(coin 5)", "Arial", 18);
    Prop1Type->setColor(Color3B::YELLOW);
    Prop1Type->setPosition(Vec2(visibleSize.width / 2 + origin.x - 350, visibleSize.height / 2 + origin.y + 40));
    this->addChild(Prop1Type, 1001);

    /**/
    auto Prop2Item = MenuItemImage::create("Prop2.png", "Prop2.png", CC_CALLBACK_1(safeground::prop2Callback, this));
    Prop2Item->setPosition(Vec2(visibleSize.width / 2 + origin.x - 410, visibleSize.height / 2 + origin.y + 0));
    auto menu4 = Menu::create(Prop2Item, NULL);
    menu4->setPosition(Vec2::ZERO);
    this->addChild(menu4, 1);

    auto Prop2Type = Label::createWithSystemFont("Click the prop to weaken debuff!(coin 4)", "Arial", 18);
    Prop2Type->setColor(Color3B::YELLOW);
    Prop2Type->setPosition(Vec2(visibleSize.width / 2 + origin.x - 350, visibleSize.height / 2 + origin.y - 40));
    this->addChild(Prop2Type, 1001);
    /**/
    auto Prop3Item = MenuItemImage::create("Prop3.png", "Prop3.png", CC_CALLBACK_1(safeground::prop3Callback, this));
    Prop3Item->setPosition(Vec2(visibleSize.width / 2 + origin.x - 410, visibleSize.height / 2 + origin.y - 80));
    auto menu5 = Menu::create(Prop3Item, NULL);
    menu5->setPosition(Vec2::ZERO);
    this->addChild(menu5, 1);

    auto Prop3Type = Label::createWithSystemFont("Click the prop to get randomly!(coin 3)", "Arial", 18);
    Prop3Type->setColor(Color3B::YELLOW);
    Prop3Type->setPosition(Vec2(visibleSize.width / 2 + origin.x - 350, visibleSize.height / 2 + origin.y - 120));
    this->addChild(Prop3Type, 1001);









    //设置键盘事件监听器
    keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(safeground::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(safeground::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);





    return true;

}
void safeground::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    int dir = 0;
    if (keyCode == EventKeyboard::KeyCode::KEY_W)//在这里设置控制人物上下左右移动的四个按键，例如，按键a为KEY_A；按键左箭头为KEY_LEFT_ARROW
    {
        dir = 1;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        dir = 2;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        dir = 3;
        knight->setFlippedX(true);                        //使精灵在向左走时，x镜像对称翻转
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        dir = 4;
        knight->setFlippedX(false);
    }

    knight->moveStep(dir);
}


/* 在这里完成人物的升级 */
int safeground::selectKnightGread()
{
    if (addgrade >= 2)
        return 3;
    else
        return 1 + addgrade;
}


int safeground::selectKnightType()
{
    if (addtype >= 1)
        return 2;
    else
        return 1;
}


bool safeground::selectProp2()
{
    if (prop2 >= 1)
        return true;
    else
        return false;
}

bool safeground::selectProp1()
{
    if (prop1 >= 1)
        return true;
    else
        return false;
}



bool safeground::selectProp3()
{
    if (prop3 >= 1)
        return true;
    else
        return false;
}


void safeground::upgradeCallback(Ref* pSender)
{
    addgrade++;

    //
    if (labelGrade != NULL)
        labelGrade->setVisible(false);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    if (addgrade == 1)
    {
        this->setCoin(this->getCoin() - 10);
        labelCoin->setVisible(false);
        myCoinSum(this->getCoin());

        labelGrade1 = Label::createWithSystemFont("Click the blue coin to upgrade!\nKnight: LV.2\nMaxHP: 120\nMaxArmor: 100\nMaxMP: 120", "Arial", 18);
        labelGrade1->setColor(Color3B::GREEN);
        labelGrade1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 400, visibleSize.height / 2 + origin.y + 60));
        this->addChild(labelGrade1, 1001);
    }

    else if (addgrade == 2)
    {
        this->setCoin(this->getCoin() - 10);
        labelCoin->setVisible(false);
        myCoinSum(this->getCoin());

        if (labelGrade1 != NULL)
            labelGrade1->setVisible(false);
        Label* labelGrade2 = Label::createWithSystemFont("Highest level now!\nKnight: LV.3\nMaxHP: 150\nMaxArmor: 100\nMaxMP: 150", "Arial", 18);
        labelGrade2->setColor(Color3B::RED);
        labelGrade2->setPosition(Vec2(visibleSize.width / 2 + origin.x + 400, visibleSize.height / 2 + origin.y + 60));
        this->addChild(labelGrade2, 1001);
    }

}


void safeground::changeTypeCallback(Ref* pSender)
{
    addtype++;
    if (labelType != NULL)
        labelType->setVisible(false);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    if (addtype == 1)
    {
        labelType1 = Label::createWithSystemFont("Knight changed!\nKnight: 2nd\nMovespeed: basic+30%\nHurt: basic+0%\nGetHurt: basic-10%\nMaxHP: basic+10%", "Arial", 18);
        labelType1->setColor(Color3B::GREEN);
        labelType1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 400, visibleSize.height / 2 + origin.y - 160));
        this->addChild(labelType1, 1001);
    }
}



void safeground::prop1Callback(Ref* pSender)
{
    prop1++;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if (prop1 == 1)
    {
        this->setCoin(this->getCoin() - 5);
        labelCoin->setVisible(false);
        myCoinSum(this->getCoin());
        Label *labelProp1 = Label::createWithSystemFont("selected!", "Arial", 18);
        labelProp1->setColor(Color3B::GREEN);
        labelProp1->setPosition(Vec2(visibleSize.width / 2 + origin.x - 140, visibleSize.height / 2 + origin.y + 40));
        this->addChild(labelProp1, 1001);
    }
}

void safeground::prop2Callback(Ref* pSender)
{
    prop2++;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if (prop2 == 1)
    {
        this->setCoin(this->getCoin() - 4);
        labelCoin->setVisible(false);
        myCoinSum(this->getCoin());
        Label* labelProp2 = Label::createWithSystemFont("selected!", "Arial", 18);
        labelProp2->setColor(Color3B::GREEN);
        labelProp2->setPosition(Vec2(visibleSize.width / 2 + origin.x - 140, visibleSize.height / 2 + origin.y - 40));
        this->addChild(labelProp2, 1001);
    }
}

void safeground::prop3Callback(Ref* pSender)
{
    prop3++;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if (prop3 == 1)
    {
        this->setCoin(this->getCoin() - 3);
        labelCoin->setVisible(false);
        myCoinSum(this->getCoin());
        Label* labelProp3 = Label::createWithSystemFont("selected!", "Arial", 18);
        labelProp3->setColor(Color3B::GREEN);
        labelProp3->setPosition(Vec2(visibleSize.width / 2 + origin.x - 140, visibleSize.height / 2 + origin.y - 120));
        this->addChild(labelProp3, 1001);
    }
}


safeground::safeground()
{

}

safeground::~safeground()
{

}
