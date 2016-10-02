#ifndef __Bullet_SCENE_H__
#define __Bullet_SCENE_H__

#include "cocos2d.h"
#include<stdio.h>
#include "HeroPlane.h"
using namespace cocos2d;
using namespace std;
typedef enum BulletType {
	//Ĭ���ӵ�
	bullet_def,
	//�����ӵ�
	bullet_main,
	//�л��ӵ�
	bullet_enemy
    
}
Bullet_Type;

class Bullet : public Sprite
{
public:
	Bullet_Type type;
	bool initWithSpriteFrameName(const std::string& spriteFrameName);
	static Bullet* createBullet(const std::string& spriteFrameName);
    CREATE_FUNC(Bullet);

	void moveBullet(float time);
	//�������������ӵ�
	void mangerMainBullet(float time);
	//void removeBullet(Ref *object);

	//Sprite* tempObject;

	//void getObject(HeroPlane* object);



};

#endif // __Bullet_SCENE_H__
