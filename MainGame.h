#ifndef __MainGame_SCENE_H__
#define __MainGame_SCENE_H__

#include "cocos2d.h"
#include <stdio.h>
#include"StartScene.h"
#include "NewEnemyPlane.h"
#include "HeroPlane.h"

class EnemyPath;
class Bullet;
class NewEnemyPlane;



using namespace cocos2d;
using namespace std;


class MainGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	~MainGame();

	Size visibleSize;
	//背景
	Sprite *bgImg;
	Sprite *bgTop;
	HeroPlane* heroPlaneG;

	Bullet* blt1;
	Bullet* blt2;
	Bullet* blt3;

	EventListenerPhysicsContact *m_event;

	//创建我们主机子弹
	void mangerMainBullet(float time);
	//移除子弹
	void removeBullet(Ref *object);
	void removeBuff(Ref * object);
	//移除我方飞机
	void removeHeroPlane(Ref *object);
	//我方飞机死亡
	void heroPlaneDie(Ref *object);

	//背景更新
	void updateBgImg(float time);

	void deleteEvent() { m_event->autorelease(); }


	//分数增加函数

	//改变位置
	void changeBgImgPosition(Sprite *brImage_m);
	//跳转到设置页面
	void changeToSetScene(Ref *object);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// 新的敌机产生器
	void managerEnemyPlanes(float time);

	void changeTheHP();

	void changeTheScore();

	void refreshTheScore();

	void refreshTheHP();

	void moveBullet(float time);

	
	///控制敌机数量
	int enemyNumber;

	int addtionalScore;

	int scoreNum;



	Label* score;
	Label *healthPoint;



	///主要是分数传递




	///统一实现我们的游戏变量初始化
	void initAllParamters();


    CREATE_FUNC(MainGame);


private:

	void manageBuff(float time);

	void removePlane(Node* pSender);
	void planeBlowup(Sprite* plane);

	void judgeWhetherGameIsOver(float time);

	void gameOver();

	void victory();

	Vector<Sprite*> mBullets;
	Vector<Sprite*> mPlanes;

	RenderTexture* render;
	RenderTexture* renderResult;
};

#endif // __MainGame_SCENE_H__
