#ifndef __ThirdScene_SCENE_H__
#define __ThirdScene_SCENE_H__

#include "cocos2d.h"
#include <stdio.h>
#include"StartScene.h"
#include "NewEnemyPlane.h"
#include "HeroPlane.h"
#include"FlyWord.h"

class EnemyPath;




using namespace cocos2d;
using namespace std;


class ThirdScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	Size visibleSize;
	//背景
	Sprite *bgImg;
	Sprite *bgTop;
	//Sprite *heroPlaneG;
	HeroPlane* heroPlaneG;
	void MainMenuGame(Ref *object);
	//创建我们主机子弹
	void mangerMainBullet(float time);
	//移除子弹
	void removeBullet(Ref *object);
	//移除我方飞机
	void removeHeroPlane(Ref *object);
	//我方飞机死亡
	void heroPlaneDie(Ref *object);

	//背景更新
	void updateBgImg(float time);
	//改变位置
	void changeBgImgPosition(Sprite *brImage_m);
	//跳转到设置页面
	void changeToSetScene(Ref *object);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// 新的敌机产生器
	void managerEnemyPlanes(float time);
	
	///控制敌机数量
	int enemyNumber;

	///显示成绩
	int scoreNumber;
	//增加的分数
	int addtionalScore;
	Label* score;



	///主要是分数传递
	void scoreShowControl();

	void countScoreUse();

	void moveBullet(float time);

	///统一实现我们的游戏变量初始化
	void initAllParamters();

	//新的敌方飞机类生成器
	void newEnemyPlaneManage(float time);





    CREATE_FUNC(ThirdScene);




	void removePlane(Node* pSender);
	void planeBlowup(Sprite* plane);

	Vector<Sprite*> mBullets;
	Vector<Sprite*> mPlanes;

	RenderTexture* render;
	RenderTexture* renderResult;

	FlyWord* word;

	
};

#endif // __ThirdScene_SCENE_H__
