#include "Bullet.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

bool Bullet::initWithSpriteFrameName(const std::string&  spriteFrameName) {
	if (Sprite::initWithSpriteFrameName(spriteFrameName)) {
		type = bullet_def;
		return true;
	}
	return false;
}

Bullet* Bullet::createBullet(const std::string&  spriteFrameName) {
	Bullet *object = NULL;
	object = new Bullet();
	object->initWithSpriteFrameName(spriteFrameName);
	//object->autorelease();

	return object;
}
/*
//创建我方飞机子弹
void Bullet::mangerMainBullet(float time) {

	Bullet *blt = Bullet::createBullet("heroBullet.png");

	Vec2 planeLocal = tempObject->getPosition();
	blt->type = Bullet_main;
	planeLocal = Vec2(planeLocal.x + 4, planeLocal.y + 65);
	blt->setPosition(planeLocal);
	blt->setTag(0);

	{
		//设置物理body
		auto body = PhysicsBody::createBox(blt->getContentSize());
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setGroup(-1);
		blt->setPhysicsBody(body);

	}
	addChild(blt, 1);

}

void Bullet::moveBullet(float time) {
	Vector<Node*>allNodes = getChildren();
	for (int i = int(allNodes.size() - 1); i >= 0; i--) {
		auto node = allNodes.at(i);
		if (strcmp(typeid(*node).name(), typeid(Bullet).name()) == 0) {
			Bullet *Bullet_m = (Bullet*)node;
			if (Bullet_m->type == Bullet_main) {
				auto yy = Bullet_m->getPosition().y;
				if (yy <= 1024) {

					Bullet_m->setPositionY(yy + 3);
				}
				else
				{
					Bullet_m->stopAllActions();
					//removeBullet(Bullet_m);
				}
			}
		}
	}
}
	

//移除子弹
void Bullet ::removeBullet(Ref *object) {
	Bullet *blt = (Bullet *)object;
	blt->stopAllActions();
	blt->removeFromParentAndCleanup(true);
}
void Bullet::getObject(HeroPlane * object)
{
	tempObject = object;
}
*/
