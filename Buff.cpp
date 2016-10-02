#include "Buff.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

bool Buff::initWithSpriteFrameName(const std::string&  spriteFrameName) {
	if (Sprite::initWithSpriteFrameName(spriteFrameName)) {
		return true;
	}
	return false;
}

Buff* Buff::createBuff(const std::string&  spriteFrameName) {
	Buff *object = NULL;
	object = new Buff();
	object->initWithSpriteFrameName(spriteFrameName);
	object->autorelease();

	return object;
}
//设定敌方飞机类型 类型对应血量
void Buff::setTypeOfPlane(BuffType  type)
{
	switch (type)
	{
	case buff_DoubleBullet:
		this->setTag(5);
	case buff_LifeFull:
		this->setTag(6);
//	case Buff_Rocket:
//		this->setTag(7);
		

	default:
		break;
	}
}
//设定敌方飞机类型 类型对应血量
void Buff::setTypeOfPlane(int  num)
{
	switch (num)
	{
	case 5:
		this->setTag(5);
	case 6:
		this->setTag(6);
	case 7:
		this->setTag(7);

	default:
		break;
	}
}
