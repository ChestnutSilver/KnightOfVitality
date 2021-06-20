#pragma once
#define __MYSCENE_H__
#include "cocos2d.h"//��Ҫ����cocos2d-xͷ�ļ�
#include "firstKnight.h"

class safeground :public cocos2d::Layer//������������Layer����
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

    safeground();//�չ��캯��
    ~safeground();//����������
    CREATE_FUNC(safeground);//�������Ҫ������Ǻ궨��ģ�ÿ�������С�
private:
    Knight* knight;
};
