#ifndef __Buff_SCENE_H__
#define __Buff_SCENE_H__

#include "cocos2d.h"
#include<stdio.h>
#include "HeroPlane.h"
using namespace cocos2d;
using namespace std;
typedef enum BuffType {
	//Ĭ���ӵ�
	buff_DoubleBullet,
	//�����ӵ�
	buff_LifeFull,
	//�л��ӵ�
	Buff_Rocket

}
Buff_Type;

class Buff : public Sprite
{
public:
	Buff_Type type;
	bool initWithSpriteFrameName(const std::string& spriteFrameName);
	static Buff* createBuff(const std::string& spriteFrameName);
	//
	void setTypeOfPlane(BuffType type);
	void setTypeOfPlane(int num);
	CREATE_FUNC(Buff);

	void moveBuff(float time);
	//�������������ӵ�
	void mangerMainBuff(float time);
	
};

#endif // __Buff_SCENE_H__
