#pragma once

#ifndef __MYSCENE_H__//�ж��Ƿ��ظ�����ͷ�ļ�
#define __MYSCENE_H__
#include "cocos2d.h"//��Ҫ����cocos2d-xͷ�ļ�

class CMyScene :public cocos2d::Layer//������������Layer����
{
public:
    static cocos2d::Scene* createScene();

    //???
   // void CMyScene::MoustEvent();
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual bool init();



    CMyScene();//�չ��캯��
    ~CMyScene();//����������
    CREATE_FUNC(CMyScene);//�������Ҫ������Ǻ궨��ģ�ÿ�������С�
};

#endif