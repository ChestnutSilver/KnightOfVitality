#pragma once

#ifndef __MYSCENE_H__//判断是否重复包含头文件
#define __MYSCENE_H__
#include "cocos2d.h"//需要包含cocos2d-x头文件

class CMyScene :public cocos2d::Layer//场景类派生于Layer层类
{
public:
    static cocos2d::Scene* createScene();

    //???
   // void CMyScene::MoustEvent();
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual bool init();



    CMyScene();//空构造函数
    ~CMyScene();//空析构函数
    CREATE_FUNC(CMyScene);//这个很重要，这个是宏定义的，每个必须有、
};

#endif