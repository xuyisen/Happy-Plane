
#include "Victory.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include"MainGame.h"
#include "StartScene.h"
using namespace cocos2d::ui;
using namespace cocos2d::extension;

USING_NS_CC;


Scene* Victory::createScene(RenderTexture* rt)
{
	Scene* scene = Scene::create();
	Victory* layer = Victory::create();



	auto sprite = Sprite::createWithTexture(rt->getSprite()->getTexture());
	sprite->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	sprite->setFlippedY(true);
	scene->addChild(sprite, 0);

	scene->addChild(layer);

	return scene;
}

bool Victory::init() {

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}
	this->pause();
	
	bgImg = Sprite::create("gameWinBox.png");
	bgImg->setAnchorPoint(Vec2(0.5, 0.5));
	bgImg->setPosition(Vec2(384, 512));
	addChild(bgImg);

	//对话框中得两个菜单按钮，在正常状态、点击状态下的图片
	auto  winNextLevelButtonNormal = Sprite::create("winNextLevelButtonNormal.png");
	auto  winNextLevelButtonSelected = Sprite::create("winNextLevelButtonSelected.png");
	auto menuButtonNormal = Sprite::create("menuButtonNormal.png");
	auto menuButtonSelected = Sprite::create("menuButtonSelected.png");
	auto itemSureMenu = MenuItemSprite::create(winNextLevelButtonNormal, winNextLevelButtonSelected, CC_CALLBACK_1(Victory::nextLevel, this));
	itemSureMenu->setAnchorPoint(Point(0.5, 0.5));
	itemSureMenu->setPosition(Vec2(290,430));
	itemSureMenu->setTag(1);

	//
	auto itemCancelMenu = MenuItemSprite::create(menuButtonNormal, menuButtonSelected, CC_CALLBACK_1(Victory::backToStartScene, this));
	itemCancelMenu->setAnchorPoint(Point(0.5, 0.5));
	itemCancelMenu->setPosition(Vec2(520,430));
	itemCancelMenu->setTag(2);

	auto menu = Menu::create(itemSureMenu, itemCancelMenu, nullptr);
	menu->setPosition(Point::ZERO);
	bgImg->addChild(menu);

	return true;
}
void Victory::nextLevel(Ref *object) {
	Director *dir = Director::getInstance();
	dir->replaceScene(MainGame::createScene());
}
void Victory::backToStartScene(Ref *object) {
	Director *dir = Director::getInstance();
	dir->replaceScene(StartScene::createScene());
}


