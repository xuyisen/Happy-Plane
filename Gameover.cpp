
#include "Gameover.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include"MainGame.h"
#include "StartScene.h"
using namespace cocos2d::ui;
using namespace cocos2d::extension;

USING_NS_CC;


Scene* Gameover::createScene(RenderTexture* rt)
{
	Scene* scene = Scene::create();
	Gameover* layer = Gameover::create();



	auto sprite = Sprite::createWithTexture(rt->getSprite()->getTexture());
	sprite->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	sprite->setFlippedY(true);
	scene->addChild(sprite, 0);

	scene->addChild(layer);

	return scene;
}

bool Gameover::init() {

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}
	this->pause();
	bgImg = Sprite::create("gameOverBox.png");
	bgImg->setAnchorPoint(Vec2(0.5, 0.5));
	bgImg->setPosition(Vec2(384, 512));
	addChild(bgImg);

	//对话框中得两个菜单按钮，在正常状态、点击状态下的图片
	auto  restartButtonNormal = Sprite::create("restartButtonNormal.png");
	auto  restartButtonSelected = Sprite::create("restartButtonSelected.png");
	auto menuButtonNormal = Sprite::create("menuButtonNormal.png");
	auto menuButtonSelected = Sprite::create("menuButtonSelected.png");
	auto itemSureMenu = MenuItemSprite::create(restartButtonNormal, restartButtonSelected, CC_CALLBACK_1(Gameover::reStart, this));
	itemSureMenu->setAnchorPoint(Point(0.5, 0.5));
	itemSureMenu->setPosition(Vec2(270,430));
	itemSureMenu->setTag(1);

	//
	auto itemCancelMenu = MenuItemSprite::create(menuButtonNormal, menuButtonSelected, CC_CALLBACK_1(Gameover::backToStartScene, this));
	itemCancelMenu->setAnchorPoint(Point(0.5, 0.5));
	itemCancelMenu->setPosition(Vec2(510, 430));
	itemCancelMenu->setTag(2);

	auto menu = Menu::create(itemSureMenu, itemCancelMenu, nullptr);
	menu->setPosition(Point::ZERO);
	bgImg->addChild(menu);

	//  9999999999999999999999999999999999int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, i).c_str(), 0);
	return true;
}
void Gameover::reStart(Ref *object) {
	Director *dir = Director::getInstance();
	dir->replaceScene(MainGame::createScene());
}
void Gameover::backToStartScene(Ref *object) {
	Director *dir = Director::getInstance();
	dir->replaceScene(StartScene::createScene());
}