#ifndef __NewEnemyPlane_SCENE_H__
#define __NewEnemyPlane_SCENE_H__

#include "cocos2d.h"
#include<stdio.h>
using namespace cocos2d;
using namespace std;
typedef enum EnemyPlaneType {
	//默认飞机
	ememy_min,
	//本机飞机
	enemy_middle,
	//敌方飞机
	enemy_max,
	//Boss1
	enemy_Boss1,

	//分为6种，小中大三种飞机，是否可以发射子弹
	
	ememy_min_without_bullet,
	ememy_middle_without_bullet,
	ememy_max_without_bullet,

	ememy_min_with_bullet,
	ememy_middle_with_bullet,
	ememy_max_with_bullet
}
EnemyPlane_Type;

class NewEnemyPlane : public Sprite
{
public:
	EnemyPlane_Type type;

	bool initWithSpriteFrameName(const std::string& spriteFrameName);
	static NewEnemyPlane* createNewEnemyPlane(const std::string& spriteFrameName);

	int currentHp;
	void setTypeOfPlane(EnemyPlane_Type type);
	void setTypeOfPlane(int num);
	bool IsDead;



	CREATE_FUNC(NewEnemyPlane);



};

#endif // __Bullet_SCENE_H__
