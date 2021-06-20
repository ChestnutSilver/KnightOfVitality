#include "battleground.h"
#include "basicEnemy.h"
#include "firstKnight.h"
#include "cocos2d.h"
#include "Bullet.h"
#include "weapon.h"
#include "box.h"
#include "smallMap.h"
#include "MyScene.h"
#include "safeground.h"
#include <vector>
USING_NS_CC;

static int SCENE = 1;
cocos2d::Vector<cocos2d::Node*> mynode;
Scene* BattleGround::createScene()
{
    auto scene = Scene::create();
    auto layer = BattleGround::create();
    scene->addChild(layer);
    return scene;
}

bool BattleGround::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (SCENE == 1)
        tileMap = TMXTiledMap::create("battleone.tmx");
    else if (SCENE == 2)
        tileMap = TMXTiledMap::create("battletwo.tmx");
    tileMap->setPosition(-2640, -2740);//设置了map的位置
    addChild(tileMap);


    TMXObjectGroup* group = tileMap->getObjectGroup("objects"); //注意，这里的objects需要与tiledmap中的对象层名称一致
    ValueMap spawnPoint = group->getObject("Knight");

    float x = spawnPoint["x"].asFloat();
    float y = spawnPoint["y"].asFloat();


    /* 记得修改参数！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
    /* 记得修改参数！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
    /* 记得修改参数！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/

    int KnightGread = safeground::selectKnightGread();
    int KnightType = safeground::selectKnightType();
    std::vector<bool>props = { safeground::selectProp1() , safeground::selectProp2() , safeground::selectProp3() };

    if (KnightGread == 1 && KnightType == 1)
        playerKnight = Knight::createWithSpriteName("Knight.png", 1, 1, props);
    else if (KnightGread == 2 && KnightType == 1)
        playerKnight = Knight::createWithSpriteName("Knight.png", 2, 1, props);
    else if (KnightGread == 3 && KnightType == 1)
        playerKnight = Knight::createWithSpriteName("Knight.png", 3, 1, props);
    else if (KnightGread == 1 && KnightType == 2)
        playerKnight = Knight::createWithSpriteName("Knight2nd.png", 1, 2, props);
    else if (KnightGread == 2 && KnightType == 2)
        playerKnight = Knight::createWithSpriteName("Knight2nd.png", 2, 2, props);
    else if (KnightGread == 3 && KnightType == 2)
        playerKnight = Knight::createWithSpriteName("Knight2nd.png", 3, 2, props);




    if (SCENE == 1)
        playerKnight->setPosition(Vec2(visibleSize.width / 2 - 1650, visibleSize.height / 2 + 1650));  //x越大越在右边，y越大越在下边，目前放在了屏幕的中间
    else if (SCENE == 2)
        playerKnight->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 - 1650));  //x越大越在右边，y越大越在下边，目前放在了屏幕的中间
    setViewpointCenter(playerKnight->getPosition(), 1);

    

    addChild(playerKnight, 2, 200);

    
    playerKnight->getBloodbar(playerKnight, playerKnight->getHitPoints(), SCENE);



    bloodprogressInit();
    manaprogressInit();
    armorprogressInit();


    Sprite* passDoor = Sprite::create("passdoor.png");
    if (SCENE == 1)
        passDoor->setPosition(Vec2(visibleSize.width / 2 - 1650, visibleSize.height / 2));
    else if (SCENE == 2)
        passDoor->setPosition(Vec2(visibleSize.height / 2 + 1900, visibleSize.height / 2 + 1700));
    addChild(passDoor);





    weapon = Weapon::createWithSpriteName("weapon1.png");
    addChild(weapon,10);
    weapon->setFlippedX(true);
    Vec2 knightPos = playerKnight->getPosition();
    weapon->setPosition(knightPos.x, knightPos.y - 16);
    setBulletType(1);


    box = Box::createWithSpriteName("boxClose.png");
    addChild(box, 1);
    box->setPosition(Vec2(visibleSize.width / 2 + 1600, visibleSize.height / 2));


    //enemyCreate();//随机创建敌人


  

    schedule(CC_SCHEDULE_SELECTOR(BattleGround::update), 0.2f);
    schedule(CC_SCHEDULE_SELECTOR(BattleGround::updateEnemyAttackToKnight), 0.8f);
    schedule(CC_SCHEDULE_SELECTOR(BattleGround::updateBossAttackToKnight), 1.0f);

    Collidable = tileMap->getLayer("collidable");//创建刚体层

    //设置键盘事件监听器
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(BattleGround::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(BattleGround::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    
    return true;
}

void BattleGround::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    const double moveSpeed = 0.5;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 knightPos = playerKnight->getPosition();
    Vec2 weaponPos = weapon->getPosition();

    Scheduler* deScheduler = Director::getInstance()->getScheduler();
    deScheduler->resumeTarget(this);
    Director::getInstance()->getActionManager()->resumeTargets(mynode);
    
    int dir = 0;
    if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S
        || keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D && playerKnight->getNoenemysteps() > 0)
        playerKnight->setNoenemysteps(playerKnight->getNoenemysteps() - 1);

    if (keyCode == EventKeyboard::KeyCode::KEY_W)//在这里设置控制人物上下左右移动的四个按键，例如，按键a为KEY_A；按键左箭头为KEY_LEFT_ARROW
    {
        if (playerKnight->getBuffsteps() > 0)
        {
            knightPos.y += tileMap->getTileSize().height + 40;
            playerKnight->setBuffsteps(playerKnight->getBuffsteps() - 1);
        }
        else if (playerKnight->getDebuffsteps() > 0)
        {
            knightPos.y += tileMap->getTileSize().height - 20;
            playerKnight->setDebuffsteps(playerKnight->getDebuffsteps() - 1);
        }
        else
            knightPos.y += tileMap->getTileSize().height + playerKnight->getMyMovespeed() + playerKnight->getSwampSpeed();

    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        if (playerKnight->getBuffsteps() > 0)
        {
            knightPos.y -= tileMap->getTileSize().height + 40;
            playerKnight->setBuffsteps(playerKnight->getBuffsteps() - 1);
        }
        else if (playerKnight->getDebuffsteps() > 0)
        {
            knightPos.y -= tileMap->getTileSize().height - 20;
            playerKnight->setDebuffsteps(playerKnight->getDebuffsteps() - 1);
        }
        else
            knightPos.y -= tileMap->getTileSize().height + playerKnight->getMyMovespeed() + playerKnight->getSwampSpeed();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        if (playerKnight->getBuffsteps() > 0)
        {
            knightPos.x -= tileMap->getTileSize().height + 40;
            playerKnight->setBuffsteps(playerKnight->getBuffsteps() - 1);
        }
        else if (playerKnight->getDebuffsteps() > 0)
        {
            knightPos.x -= tileMap->getTileSize().height - 20;
            playerKnight->setDebuffsteps(playerKnight->getDebuffsteps() - 1);
        }
        else
            knightPos.x -= tileMap->getTileSize().height + playerKnight->getMyMovespeed() + playerKnight->getSwampSpeed();           //这个移动的距离就是每个瓦片的长度or宽度
        playerKnight->setFlippedX(true);                        //使精灵在向左走时，x镜像对称翻转
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        if (playerKnight->getBuffsteps() > 0)
        {
            knightPos.x += tileMap->getTileSize().height + 40;
            playerKnight->setBuffsteps(playerKnight->getBuffsteps() - 1);
        }
        else if (playerKnight->getDebuffsteps() > 0)
        {
            knightPos.x += tileMap->getTileSize().height - 20;
            playerKnight->setDebuffsteps(playerKnight->getDebuffsteps() - 1);
        }
        else
            knightPos.x += tileMap->getTileSize().height + playerKnight->getMyMovespeed() + playerKnight->getSwampSpeed();
        playerKnight->setFlippedX(false);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_J)
    {
        srand(time(0));

        if (nearestEnemy() != NULL)
            shootBullet(knightPos);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_K)
    {
        static int changeWeapon = 0;
        if (changeWeapon % 4 == 0)
        {
            changeWeapon++;
            setBulletType(1);
            weapon->removeFromParent();
            weapon = Weapon::createWithSpriteName("weapon1.png");
            weapon->setPosition(Vec2(knightPos.x, knightPos.y - 16));
            addChild(weapon, 10);
        }
        else if (changeWeapon % 4 == 1)
        {
            changeWeapon++;
            setBulletType(2);
            weapon->removeFromParent();
            weapon = Weapon::createWithSpriteName("weapon2.png");
            weapon->setPosition(Vec2(knightPos.x, knightPos.y - 16));
            addChild(weapon, 10);
        }
        else if (changeWeapon % 4 == 2)
        {
            changeWeapon++;
            setBulletType(3);
            weapon->removeFromParent();
            weapon = Weapon::createWithSpriteName("weapon31.png");
            weapon->setPosition(Vec2(knightPos.x, knightPos.y - 16));
            addChild(weapon, 10);
        }
        else if (changeWeapon % 4 == 3)
        {
            changeWeapon++;
            setBulletType(4);
            weapon->removeFromParent();
            weapon = Weapon::createWithSpriteName("weapon32.png");
            weapon->setPosition(Vec2(knightPos.x, knightPos.y - 16));
            addChild(weapon, 10);
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_L)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        if (knightPos.x > visibleSize.width / 2 + 1550 && knightPos.x<visibleSize.width / 2 + 1650 && knightPos.y>visibleSize.height / 2 - 50 && knightPos.y < visibleSize.height / 2 + 50)
        {
            box = Box::createWithSpriteName("boxOpen.png");
            addChild(box, 1);
            box->setPosition(Vec2(visibleSize.width / 2 + 1600, visibleSize.height / 2));

            if (1)
            {
                auto addhp = Sprite::create("addHP.png");
                addChild(addhp, 5);
                addhp->setPosition(Vec2(visibleSize.width / 2 + 1600, visibleSize.height / 2));
                addhp->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 1, 0, 1);
                playerKnight->setHitPoints(playerKnight->getHitPoints() + 20);
            }
        }
    }


    /* 机关地形 */
    playerKnight->TrapTerrain(knightPos, playerKnight);


    if (playerKnight->getHitPoints() <= 0)
    {
        auto scene = safeground::createScene(playerKnight->getAddcoin(), playerKnight);
        Director::getInstance()->replaceScene(scene);        
    }

    pBloodProGress->setPercentage(playerKnight->getHitPoints() / playerKnight->getInitHitPoints() * 100);
    pManaProGress->setPercentage(playerKnight->getManaPoints() / playerKnight->getInitManaPoints() * 100);
    pArmorProGress->setPercentage(playerKnight->getArmorPoints() / playerKnight->getInitArmorPoints() * 100);


    weaponPos = Vec2(knightPos.x, knightPos.y - 16);
    weapon->runAction(MoveTo::create(moveSpeed, weaponPos));
    this->setViewpointCenter(knightPos);//重新设置视点
    this->setKnightPosition(knightPos);//骑士移动



    static std::vector<bool>explore = { 0,0,0,0,0,0,0,0,0,0};

    if (knightPos.x > visibleSize.width / 2 - 400 && explore[0] == 0 && SCENE == 1 || knightPos.y > visibleSize.height / 2 - 300 && explore[5] == 0 && SCENE == 2)
    {
        if (SCENE == 1)
            explore[0] = 1;
        else if (SCENE == 2)
            explore[5] = 1;
        playerKnight->setPlaceType(1);
        playerKnight->getBloodbar(playerKnight, playerKnight->getHitPoints(), SCENE);
        enemyCreate();//随机创建敌人
    }
    else if (knightPos.y < visibleSize.height / 2 + 300 && explore[1] == 0 && SCENE == 1 || knightPos.y>visibleSize.height / 2 + 1300 && explore[6] == 0 && SCENE == 2)
    {
        if (SCENE == 1)
            explore[1] = 1;
        else if (SCENE == 2)
            explore[6] = 1;
        playerKnight->setPlaceType(2);
        playerKnight->getBloodbar(playerKnight, playerKnight->getHitPoints(), SCENE);
        enemyCreate();//随机创建敌人
    }
    else if (knightPos.x > visibleSize.height / 2 + 1400 && explore[2] == 0 && SCENE == 1 || knightPos.x > visibleSize.height / 2 + 1400 && knightPos.y < visibleSize.height / 2 + 300 && explore[7] == 0 && SCENE == 2)
    {
        if (SCENE == 1)
            explore[2] = 1;
        else if (SCENE == 2)
            explore[7] = 1;
        playerKnight->setPlaceType(3);
        playerKnight->getBloodbar(playerKnight, playerKnight->getHitPoints(), SCENE);
    }
    else if (knightPos.x < visibleSize.height / 2 - 1200 && knightPos.y < visibleSize.height / 2 + 300 && explore[3] == 0 && SCENE == 1 || knightPos.x> visibleSize.height / 2 + 1550 && knightPos.y > visibleSize.height / 2 + 1300 && explore[8] == 0 && SCENE == 2)
    {
        if (SCENE == 1)
            explore[3] = 1;
        else if (SCENE == 2)
            explore[8] = 1;
        playerKnight->setPlaceType(4);
        playerKnight->getBloodbar(playerKnight, playerKnight->getHitPoints(), SCENE);
              
    }


    else if (knightPos.x < visibleSize.height / 2 - 1200 && knightPos.y < visibleSize.height / 2 + 300 && explore[9] == 0 && SCENE == 2)
    {
        explore[9] = 1;
        playerKnight->setPlaceType(5);
        playerKnight->getBloodbar(playerKnight, playerKnight->getHitPoints(), SCENE);
        bossCreate();
    }










    /* 游戏结束，回到安全场地 */
    if (knightPos.x < visibleSize.height / 2 - 1350 && knightPos.y < visibleSize.height / 2 + 300 && explore[3] == 1 && SCENE == 1 || knightPos.x>visibleSize.height / 2 + 1900 && knightPos.y > visibleSize.height / 2 + 1300 && explore[8] == 1 && SCENE == 2)
    {
        if (SCENE == 1)
            SCENE = 2;
        else if (SCENE == 2)
            SCENE = 1;
        auto scene = safeground::createScene(playerKnight->getAddcoin(), playerKnight);
        Director::getInstance()->replaceScene(scene);
    }




    //playerKnight->runAction(MoveTo::create(moveSpeed, knightPos));  //帧动画比setPosition舒适许多！  
}

/* 功能：检测碰撞，在碰撞时不允许骑士移动，在未碰撞时允许骑士移动 */
void BattleGround::setKnightPosition(Vec2 position)
{
    const double moveSpeed = 0.5;

    Vec2 tileCoord = this->tileCoordFromPosition(position);

    int tileGid = Collidable->getTileGIDAt(tileCoord);

    if (tileGid > 0)
    {
        Value prop = tileMap->getPropertiesForGID(tileGid);
        ValueMap propValueMap = prop.asValueMap();

        std::string collision = propValueMap["Collidable"].asString();

        if (collision == "true")
        {
            return;//在这里可以添加检测到碰撞的效果
        }
    }
    playerKnight->runAction(MoveTo::create(moveSpeed, position));
}

Vec2 BattleGround::tileCoordFromPosition(Vec2 pos)
{
    //int x = pos.x / tileMap->getTileSize().width;
    //int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - pos.y) / tileMap->getTileSize().height; //这里没有使用鼠标的触摸，所以不用这样的坐标计算方法
    int x = (pos.x+2640) / tileMap->getTileSize().width;
    int y = (pos.y+2980) / tileMap->getTileSize().height;

    return Vec2(x, y);
}

/* 功能：重新设置视点，使得人物能够永远在屏幕中央 */
/* Reference：重新设置视点的方法（通过屏幕中心点与骑士位置对比的偏移量移动地图），参考了《学习笔记》258页-设置滚动地图的知识 */
void BattleGround::setViewpointCenter(Vec2 position)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int x = MAX(position.x, visibleSize.width / 2);
    int y = MAX(position.y, visibleSize.height / 2);
    x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - visibleSize.width / 2);
    y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - visibleSize.height / 2);

    //屏幕中心点
    Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    //使精灵处于屏幕中心。移动地图目标位置
    Vec2 pointB = position;

    //地图移动偏移量
    Vec2 offset = pointA - pointB;

    this->runAction(MoveTo::create(0.5, offset));
   // this->setPosition(offset);
}


void BattleGround::setViewpointCenter(Vec2 position, int first)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int x = MAX(position.x, visibleSize.width / 2);
    int y = MAX(position.y, visibleSize.height / 2);
    x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - visibleSize.width / 2);
    y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - visibleSize.height / 2);

    //屏幕中心点
    Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    //使精灵处于屏幕中心。移动地图目标位置
    Vec2 pointB = position;

    //地图移动偏移量
    Vec2 offset = pointA - pointB;

    this->runAction(MoveTo::create(0.01, offset));
}

void BattleGround::shootBullet(Vec2 position)
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vec2 knightPos = playerKnight->getPosition();
    Vec2 weaponPos = position;

    Bullet* bullet;

    if (getBulletType() == 1)
    {
        bullet = Bullet::createWithSpriteName("bullet1.png");
        addChild(bullet, 10);
    }
    else if (getBulletType() == 2)
    {
        bullet = Bullet::createWithSpriteName("bullet2.png");
        addChild(bullet, 10);
    }
    else if (getBulletType() == 3)
    {
        bullet = Bullet::createWithSpriteName("bullet31.png");
        addChild(bullet, 10);
    }
    else if (getBulletType() == 4)
    {
        bullet = Bullet::createWithSpriteName("bullet32.png");
        addChild(bullet, 10);
    }

    if ((getBulletType() == 2 || getBulletType() == 3 || getBulletType() == 4) && playerKnight->getManaPoints() <= 0)
        return;

    weapon->setPosition(Vec2(position.x, position.y - 16));
    weaponPos = Vec2(position.x, position.y - 16);
    weapon->setFlippedX(true);
    weapon->runAction(MoveTo::create(0.5, weaponPos));
    weapon->weaponRotate(weapon, playerKnight, nearestEnemy());

    bullet->setPosition(knightPos);
    bulletArray.pushBack(bullet);
    //weaponArray.pushBack(weapon);


    bullet->bulletRotate(bullet, playerKnight, nearestEnemy());
    



    Vec2 enemyPos = nearestEnemy()->getPosition();


    if (getBulletType() == 1)
    {
        playerKnight->setManaPoints(playerKnight->getManaPoints() - 0);
        bullet->runAction(MoveTo::create(0.2, enemyPos));
        bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.2, 0, 0.2);
    }
    else if (getBulletType() == 2)//设计子弹快速连发
    {
        playerKnight->setManaPoints(playerKnight->getManaPoints() - 0.5);
        bullet->runAction(MoveTo::create(0.2, enemyPos));
        bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.2, 0, 0.2);


        bullet = Bullet::createWithSpriteName("bullet2.png");
        addChild(bullet, 10);
        bullet->setPosition(knightPos);
        bullet->bulletRotate(bullet, playerKnight, nearestEnemy());
        bullet->runAction(MoveTo::create(0.1, enemyPos));
        bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.1, 0, 0.1);

        bullet = Bullet::createWithSpriteName("bullet2.png");
        addChild(bullet, 10);
        bullet->setPosition(knightPos);
        bullet->bulletRotate(bullet, playerKnight, nearestEnemy());
        bullet->runAction(MoveTo::create(0.3, enemyPos));
        bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.3, 0, 0.3);
    }
    else if (getBulletType() == 3)
    {
        playerKnight->setManaPoints(playerKnight->getManaPoints() - 0.2);
        bullet->runAction(MoveTo::create(0.2, enemyPos));
        bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.2, 0, 0.2);
    }
    else if (getBulletType() == 4)
    {
        playerKnight->setManaPoints(playerKnight->getManaPoints() - 4);
        bullet->runAction(MoveTo::create(0.2, enemyPos));
        bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.2, 0, 0.2);

    }


    /* 敌人血量及生存状态监测 */
    if (getBulletType() == 1)
        nearestEnemy()->setHitPoints(nearestEnemy()->getHitPoints() - 4 * playerKnight->getMyHurt());
    else if (getBulletType() == 2)
        nearestEnemy()->setHitPoints(nearestEnemy()->getHitPoints() - 2 * playerKnight->getMyHurt());
    else if (getBulletType() == 3)
        nearestEnemy()->setHitPoints(nearestEnemy()->getHitPoints() - 5 * playerKnight->getMyHurt());
    else if (getBulletType() == 4)
    {
        nearestEnemy()->setHitPoints(nearestEnemy()->getHitPoints() - 8 * playerKnight->getMyHurt());

        for (Enemy* enemy : enemyArray)
        {
            Vec2 enemyPos = enemy->getPosition();
            double temp = pow((pow(fabs(knightPos.x - enemyPos.x), 2)) + (pow(fabs(knightPos.y - enemyPos.y), 2)), 0.5);
            if (enemy != nearestEnemy() && temp < 300 && enemy->getAlive() == true)
            {
                enemy->setHitPoints(enemy->getHitPoints() - 2 * playerKnight->getMyHurt());

                Label* mylabel = Label::createWithSystemFont("-2", "Arial", 20);
                mylabel->setPosition(enemyPos);
                mylabel->setColor(Color3B::YELLOW);
                this->addChild(mylabel, 2);
                mylabel->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.4, 0, 0.4);
            }
            if (enemy != nearestEnemy() && enemy->getHitPoints() <= 0)
            {
                enemy->setVisible(false);
                enemy->setAlive(false);

            }
        }
    }


    if (nearestEnemy()->getHitPoints() <= 0)
    {
        if (nearestEnemy()->getEnemyType() == 5)
        {
            playerKnight->setHitPoints(10000);
            auto noenemylabel = Label::createWithSystemFont("GET BOSS SUPER BUFF! Invincible!!", "Arial", 24);
            noenemylabel->setPosition(enemyPos + Vec2(0, 80));
            noenemylabel->setColor(Color3B::RED);
            this->addChild(noenemylabel, 2);
            noenemylabel->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 3, 0, 3);
        }
        nearestEnemy()->setVisible(false);
        nearestEnemy()->setAlive(false);




        srand(time(0));
        if (rand() % 3 == 0)
        {
            auto miniaddmp = Sprite::create("miniaddMP.png");
            addChild(miniaddmp, 10);
            miniaddmp->setPosition(enemyPos);
            miniaddmp->runAction(MoveTo::create(0.5, knightPos));
            miniaddmp->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.5, 0, 0.5);

            playerKnight->setManaPoints(playerKnight->getManaPoints() + 0.5);
        }

        if (rand() % 5 == 0)
        {
            auto miniaddcoin = Sprite::create("miniaddCOIN.png");
            addChild(miniaddcoin, 10);
            miniaddcoin->setPosition(enemyPos);
            miniaddcoin->runAction(MoveTo::create(0.5, knightPos));
            miniaddcoin->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.5, 0, 0.5);
            playerKnight->setAddcoin(playerKnight->getAddcoin() + 10);

            auto coinlabel = Label::createWithSystemFont("coin+10", "Arial", 18);
            coinlabel->setPosition(enemyPos + Vec2(0, 20));
            coinlabel->setColor(Color3B::YELLOW);
            this->addChild(coinlabel, 2);
            coinlabel->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.4, 0, 0.4);
        }

        if (rand() % 6 == 0 && playerKnight->getBuffsteps() == 0 && playerKnight->getDebuffsteps() == 0)//getbuff
        {
            playerKnight->setBuffsteps(15);

            playerKnight->setAddspeed(20 * playerKnight->getUpbuff());
            playerKnight->setDespeed(0);


            auto buffspeedlabel = Label::createWithSystemFont("Get buff! Speed +50%", "Arial", 18);
            buffspeedlabel->setPosition(enemyPos + Vec2(0, 40));
            buffspeedlabel->setColor(Color3B::YELLOW);
            this->addChild(buffspeedlabel, 2);
            buffspeedlabel->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.4, 0, 0.4);
        }
        else if (rand() % 7 == 0 && playerKnight->getBuffsteps() == 0 && playerKnight->getDebuffsteps() == 0)//getdebuff
        {
            playerKnight->setDebuffsteps(15);
            playerKnight->setAddspeed(0);
            playerKnight->setDespeed(-20 * playerKnight->getDowndebuff());

            auto buffspeedlabel = Label::createWithSystemFont("Get debuff. Speed -50%", "Arial", 18);
            buffspeedlabel->setPosition(enemyPos + Vec2(0, 60));
            buffspeedlabel->setColor(Color3B::YELLOW);
            this->addChild(buffspeedlabel, 2);
            buffspeedlabel->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.4, 0, 0.4);
        }
        else if (rand() % 8 == 0 && playerKnight->getBuffsteps() == 0 && playerKnight->getDebuffsteps() == 0)
        {
            playerKnight->setNoenemy(true);
            playerKnight->setNoenemysteps(15);

            auto noenemylabel = Label::createWithSystemFont("Get super buff! Invincible!!", "Arial", 20);
            noenemylabel->setPosition(enemyPos + Vec2(0, 80));
            noenemylabel->setColor(Color3B::RED);
            this->addChild(noenemylabel, 2);
            noenemylabel->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 1, 0, 1);
        }

        else
        {
            playerKnight->setAddspeed(0);
            playerKnight->setDespeed(0);
        }


        //enemyArray.eraseObject(nearestEnemy());
    }



    /* 攻击敌人的时候显示敌人减少血量标签 */
    Label* label;
    if (getBulletType() == 1)
        label = Label::createWithSystemFont("-4", "Arial", 20);
    else if(getBulletType() == 2)
        label = Label::createWithSystemFont("-2", "Arial", 20);
    else if (getBulletType() == 3)
        label = Label::createWithSystemFont("-5", "Arial", 20);
    else if (getBulletType() == 4)
        label = Label::createWithSystemFont("-8", "Arial", 20);
    label->setPosition(enemyPos);
    label->setColor(Color3B::RED);
    this->addChild(label, 2);
    label->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.4, 0, 0.4);



    //bullet->shootBulletFromKnight(playerKnight, nearestEnemy());

}

void BattleGround::moveRandom()//回调函数update()每一秒调一次函数
{
    
    

}

void BattleGround::update(float dt)
{
    int j = 0;
    for (Enemy* enemy : enemyArray)
    {
        Vec2 pos = enemy->getPosition();
        srand(unsigned int(time(0)));
        int i = (rand()+j) % 4;
        if (i == 0)
        {
            pos.x -= 20;
            enemy->setFlippedX(true);
        }
        else if (i == 1)
        {
            pos.x += 20;
            enemy->setFlippedX(false);
        }
        else if (i == 2)
        {
            pos.y -= 20;
        }
        else if (i == 3)
        {
            pos.y += 20;
        }
        enemy->runAction(MoveTo::create(0.2, pos));
        j++;
    }


    if (Knight::choiceExit() == true)
    {
        auto scene = safeground::createScene(playerKnight->getAddcoin(), playerKnight);
        Director::getInstance()->replaceScene(scene);
    }

    if (Knight::choicePause() == true)
    {
        Scheduler* defaultScheduler = Director::getInstance()->getScheduler();
        defaultScheduler->pauseTarget(this); 
        mynode=Director::getInstance()->getActionManager()->pauseAllRunningActions();  
            
        
    }

    
}


void BattleGround::enemyCreate()
{


    Vec2 adjustEnemyAppearPlace;
    if (playerKnight->getPlaceType() == 1 && SCENE == 1)
        adjustEnemyAppearPlace = Vec2(0, 1650);
    else if (playerKnight->getPlaceType() == 2 && SCENE == 1)
        adjustEnemyAppearPlace = Vec2(0, 0);
    else if (playerKnight->getPlaceType() == 1 && SCENE == 2)
        adjustEnemyAppearPlace = Vec2(0, 0);
    else if (playerKnight->getPlaceType() == 2 && SCENE == 2)
        adjustEnemyAppearPlace = Vec2(0, 1650);
    
    if (playerKnight->getPlaceType() == 1)
    {
        auto enemy1 = Enemy::createWithSpriteName("enemyice1.png");//创建一个Enemy
        this->addChild(enemy1);
        enemy1->setEnemyType(1);
        enemyArray.pushBack(enemy1);//放进数组中

        auto enemy2 = Enemy::createWithSpriteName("enemyice2.png");//创建一个Enemy
        this->addChild(enemy2);
        enemy2->setEnemyType(2);
        enemyArray.pushBack(enemy2);//放进数组中

        auto enemy3 = Enemy::createWithSpriteName("enemyice3.png");//创建一个Enemy
        this->addChild(enemy3);
        enemy3->setEnemyType(3);
        enemyArray.pushBack(enemy3);//放进数组中

        auto enemy4 = Enemy::createWithSpriteName("enemyice4.png");//创建一个Enemy
        this->addChild(enemy4);
        enemy4->setEnemyType(4);
        enemyArray.pushBack(enemy4);//放进数组中

        auto enemy5 = Enemy::createWithSpriteName("enemyice3.png");//创建一个Enemy
        this->addChild(enemy5);
        enemy5->setEnemyType(3);
        enemyArray.pushBack(enemy5);//放进数组中

        auto enemy6 = Enemy::createWithSpriteName("enemyice4.png");//创建一个Enemy
        this->addChild(enemy6);
        enemy6->setEnemyType(4);
        enemyArray.pushBack(enemy6);//放进数组中

        auto enemy7 = Enemy::createWithSpriteName("enemyice2.png");//创建一个Enemy
        this->addChild(enemy7);
        enemy7->setEnemyType(2);
        enemyArray.pushBack(enemy7);//放进数组中

        auto enemy8 = Enemy::createWithSpriteName("enemyice1.png");//创建一个Enemy
        this->addChild(enemy8);
        enemy8->setEnemyType(1);
        enemyArray.pushBack(enemy8);//放进数组中
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    srand(unsigned int(time(0)));

    for (Enemy* sp : enemyArray)
    {
        sp->setVisible(true);
        int i = rand() % 400;
        sp->setPosition(Vec2(visibleSize.width / 2 - 200 + i, visibleSize.height / 2 - 200 + i) + adjustEnemyAppearPlace);
        sp->setHitPoints(20);
        sp->setAlive(true);
    }
}

void BattleGround::bossCreate()
{

    enemyBoss = Enemy::createWithSpriteName("boss.png");//创建一个Enemy
    this->addChild(enemyBoss);

    enemyBoss->setEnemyType(5);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    enemyBoss->setPosition(Vec2(visibleSize.width / 2 - 1700, visibleSize.height / 2));
    enemyBoss->setHitPoints(200);
    enemyBoss->setAlive(true);

}


//检测距离骑士最近的敌人，并返回该enemy
Enemy* BattleGround::nearestEnemy()
{
    if (playerKnight->getPlaceType() == 5)
        if (enemyBoss->getAlive() == true)
            return enemyBoss;

    return Enemy::NearestEnemy(getBulletType(), playerKnight->getPosition(), enemyArray);
}



void BattleGround::bloodprogressInit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* pBloodKongSp = Sprite::create("StatusBackground.png");//空血条
    pBloodKongSp->setPosition(Vec2(-visibleSize.width / 2 + 100, visibleSize.height / 2 - 20));
    playerKnight->addChild(pBloodKongSp);

    Sprite* pBloodManSp = Sprite::create("StatusBlood.png");//满血条
    pBloodProGress = ProgressTimer::create(pBloodManSp);

    pBloodProGress->setType(cocos2d::ProgressTimer::Type::BAR);
    pBloodProGress->setBarChangeRate(Vec2(1, 0));
    pBloodProGress->setMidpoint(Vec2(0, 0));
    pBloodProGress->setPosition(Vec2(-visibleSize.width / 2 + 109, visibleSize.height / 2 - 2));

    pBloodProGress->setPercentage(playerKnight->getHitPoints() / playerKnight->getInitHitPoints() * 100);
    playerKnight->addChild(pBloodProGress, 1, 1);



}

void BattleGround::manaprogressInit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
   // Sprite* pBloodKongSp = Sprite::create("StatusBackground.png");//空血条
   // pBloodKongSp->setPosition(Vec2(-visibleSize.width / 2 + 100, visibleSize.height / 2 - 20));
   // playerKnight->addChild(pBloodKongSp);

    Sprite* pManaManSp = Sprite::create("StatusMana.png");//满血条
    pManaProGress = ProgressTimer::create(pManaManSp);

    pManaProGress->setType(cocos2d::ProgressTimer::Type::BAR);
    pManaProGress->setBarChangeRate(Vec2(1, 0));
    pManaProGress->setMidpoint(Vec2(0, 0));
    pManaProGress->setPosition(Vec2(-visibleSize.width / 2 + 109, visibleSize.height / 2 - 19));

    pManaProGress->setPercentage(playerKnight->getManaPoints() / playerKnight->getInitManaPoints() * 100);
    playerKnight->addChild(pManaProGress, 1, 1);
}
void BattleGround::armorprogressInit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
   // Sprite* pBloodKongSp = Sprite::create("StatusBackground.png");//空血条
   // pBloodKongSp->setPosition(Vec2(-visibleSize.width / 2 + 100, visibleSize.height / 2 - 20));
   // playerKnight->addChild(pBloodKongSp);

    Sprite* pArmorManSp = Sprite::create("StatusArmor.png");//满血条
    pArmorProGress = ProgressTimer::create(pArmorManSp);

    pArmorProGress->setType(cocos2d::ProgressTimer::Type::BAR);
    pArmorProGress->setBarChangeRate(Vec2(1, 0));
    pArmorProGress->setMidpoint(Vec2(0, 0));
    pArmorProGress->setPosition(Vec2(-visibleSize.width / 2 + 109, visibleSize.height / 2 - 36 ));

    pArmorProGress->setPercentage(playerKnight->getArmorPoints() / playerKnight->getInitArmorPoints() * 100);
    playerKnight->addChild(pArmorProGress, 1, 1);
}

void BattleGround::updateEnemyAttackToKnight(float dt)
{

    Bullet* bullet;
    for (Enemy* enemy : enemyArray)
    {
        Vec2 knightPos = playerKnight->getPosition();
        Vec2 enemyPos = enemy->getPosition();
        if (enemy->getEnemyType() == 1 && enemy->getAlive() == true && pow((pow(fabs(knightPos.x - enemyPos.x), 2)) + (pow(fabs(knightPos.y - enemyPos.y), 2)), 0.5) < 300)
        {
            bullet = Bullet::createWithSpriteName("enemybullet1.png");
            addChild(bullet, 10);
            bullet->setPosition(enemyPos);

            bullet->runAction(MoveTo::create(0.5, knightPos));
            bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.5, 0, 0.5);

            if (playerKnight->getNoenemysteps() <= 0)
                playerKnight->setHitPoints(playerKnight->getHitPoints() - 1 * playerKnight->getMyGetHurt());
        }
        else if (enemy->getEnemyType() == 2 && enemy->getAlive() == true && pow((pow(fabs(knightPos.x - enemyPos.x), 2)) + (pow(fabs(knightPos.y - enemyPos.y), 2)), 0.5) < 300)
        {
            bullet = Bullet::createWithSpriteName("enemybullet2.png");
            addChild(bullet, 10);
            bullet->setPosition(enemyPos);

            bullet->runAction(MoveTo::create(0.5, knightPos));
            bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.5, 0, 0.5);

            if (playerKnight->getNoenemysteps() <= 0)
                playerKnight->setHitPoints(playerKnight->getHitPoints() - 0.8 * playerKnight->getMyGetHurt());
        }
        else if (enemy->getEnemyType() == 3 && enemy->getAlive() == true && pow((pow(fabs(knightPos.x - enemyPos.x), 2)) + (pow(fabs(knightPos.y - enemyPos.y), 2)), 0.5) < 100)
        {
            bullet = Bullet::createWithSpriteName("enemybullet3.png");
            addChild(bullet, 10);
            bullet->setPosition(enemyPos);

            bullet->runAction(MoveTo::create(0.5, knightPos));
            bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.5, 0, 0.5);

            if (playerKnight->getNoenemysteps() <= 0)
                playerKnight->setHitPoints(playerKnight->getHitPoints() - 0.4 * playerKnight->getMyGetHurt());
        }
        else if (enemy->getEnemyType() == 4 && enemy->getAlive() == true && pow((pow(fabs(knightPos.x - enemyPos.x), 2)) + (pow(fabs(knightPos.y - enemyPos.y), 2)), 0.5) < 100)
        {
            bullet = Bullet::createWithSpriteName("enemybullet4.png");
            addChild(bullet, 10);
            bullet->setPosition(enemyPos);

            bullet->runAction(MoveTo::create(0.5, knightPos));
            bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.5, 0, 0.5);

            if (playerKnight->getNoenemysteps() <= 0)
                playerKnight->setHitPoints(playerKnight->getHitPoints() - 0.2 * playerKnight->getMyGetHurt());
        }
    }


}

void BattleGround::updateBossAttackToKnight(float dt)
{
    if (playerKnight->getPlaceType() != 5)
        return;

    Vec2 knightPos = playerKnight->getPosition();
    Vec2 enemyPos = enemyBoss->getPosition();

    if (enemyBoss->getEnemyType() == 5 && enemyBoss->getAlive() == true && pow((pow(fabs(knightPos.x - enemyPos.x), 2)) + (pow(fabs(knightPos.y - enemyPos.y), 2)), 0.5) < 300)
    {
        bullet = Bullet::createWithSpriteName("bossBullet.png");
        addChild(bullet, 10);
        bullet->setPosition(enemyPos);

        bullet->runAction(MoveTo::create(0.3, knightPos));
        bullet->schedule(CC_SCHEDULE_SELECTOR(Bullet::bulletfalse), 0.3, 0, 0.3);

        if (playerKnight->getNoenemysteps() <= 0)
            playerKnight->setHitPoints(playerKnight->getHitPoints() - 0.6 * playerKnight->getMyGetHurt());
    }
}