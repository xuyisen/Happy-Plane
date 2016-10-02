#pragma once
#include"cocos2d.h"
#include"MainGame.h"
#include"HeroPlane.h"
#include"NewEnemyPlane.h"
#include<stdio.h>
using namespace std;
using namespace cocos2d;

USING_NS_CC;
#ifndef __EnemyPath__H__
#define __EnemyPath__H__


class EnemyPath : public Layer
{

public:
	void getHero(Node* hero);
	void runPath1();
	void runPath2();
	void runPath3();
	void runPath4();
	void runPath5();
	void runPath6();
	void runPath7();

	//void chapter1(float time);
	void manageEnemyBullet(float time);
	void EnemyBulletMove(float time);
	void removeBullet(Ref *object);
	//设置物理body
	void setPlaneBody(float time);

	CREATE_FUNC(EnemyPath);

public:
	Node* plane;
	void enemyRemove(Node* pNode);
	void SPath(float time);
	void TwicePath(float time);
	void TwicePath2(float time);
	void RandomPath(float time);
	void RandomPath2(float time);
	void TransversePath1(float time);
	void TransversePath2(float time);
	void TransversePath3(float time);
	void TransversePath4(float time);
	void modelOfEnemy1(float time);
	void modelOfEnemy2(float time);
	void modelOfEnemy3(float time);
	void modelOfEnemy4(float time);
	void modelOfEnemy5(float time);
	void modelOfEnemy6(float time);
	void modelOfEnemy7(float time);
	void AIPath1(float time);
	void AIPath2(float time);
	void BossMove(float time);
	void MangerBoss();
	void chapter1();
	NewEnemyPlane*boss;
	void runBoss();
	void BossBulletMove(float time);
	void BossBullet(float time);
	void BossBullet1(float time);
	void BossBullet2(float time);
	void BossBullet3(float time);
	void BossBullet4(float time);
	void BossBullet5(float time);
	void BossBullet6(float time);
	void BossBullet7(float time);
	void BossBullet21(float time);
	void BossBullet22(float time);
	void BossBullet23(float time);
	void BossBullet24(float time);
	void BossBullet25(float time);
	void BossBullet26(float time);
	void BossBullet27(float time);
	//关卡二
	void setBulletBody(float time);
	void chapter2();
	void chapter3();
};


#endif