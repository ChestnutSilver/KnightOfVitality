#pragma once
#define __MYSCENE_H__
#include "cocos2d.h"//需要包含cocos2d-x头文件
#include "firstKnight.h"

class safeground :public cocos2d::Layer//场景类派生于Layer层类
{
    CC_SYNTHESIZE(int, coin, Coin);
    CC_SYNTHESIZE(int, knightGrade, KnightGrade);
    CC_SYNTHESIZE(int, knightType, KnightType);


public:

    static int selectKnightGread();
    static int selectKnightType();

    static bool selectProp1();
    static bool selectProp2();
    static bool selectProp3();

    static cocos2d::Scene* createScene(int coinsum, Knight* knight);

    //???
   // void CMyScene::MoustEvent();
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual bool init();


    void myCoinSum(int coinsum);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    cocos2d::EventListenerKeyboard* keyListener;

    void upgradeCallback(cocos2d::Ref* pSender);
    void changeTypeCallback(Ref* pSender);
    void prop1Callback(Ref* pSender);
    void prop2Callback(Ref* pSender);
    void prop3Callback(Ref* pSender);

    safeground();//空构造函数
    ~safeground();//空析构函数
    CREATE_FUNC(safeground);//这个很重要，这个是宏定义的，每个必须有、
private:
    Knight* knight;
};
