#include "SecondScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"AudioEngine.h"
#include "MainGamePauseLayer.h"
#include "EnemyPath.h"
#include "HeroPlane.h"
#include "NewEnemyPlane.h"
#include "Bullet.h"
#include"Gameover.h"
#include"Victory.h"
using namespace experimental;
using namespace cocostudio::timeline;
using namespace cocos2d;



USING_NS_CC;


Scene* SecondScene::createScene()
{

	auto scene = Scene::createWithPhysics();
	Vect gravity = Vect(0.0f, 0.0f);//0重力
	scene->getPhysicsWorld()->setGravity(gravity);

	// 'layer' is an autorelease object
	auto layer = SecondScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SecondScene::init()
{
   
    if ( !Layer::init() )
    {
        return false;
    }
	addtionalScore = 0;
	visibleSize = Director::getInstance()->getWinSize();

	//创建成绩标签
	score = Label::createWithTTF("Score: 0", "arial.ttf", 50);
	score->setAnchorPoint(Vec2(0, 1));
	score->setPosition(Vec2(0, 1024));
	score->setColor(Color3B(255,97,0));
	addChild(score,1);
	//血量HP标签
	Label *healthPoint = Label::createWithTTF("HP: 0", "arial.ttf", 50);
	healthPoint->setAnchorPoint(Vec2(0, 1));
	healthPoint->setPosition(Vec2(0, 954));
	healthPoint->setColor(Color3B(255, 97, 0));
	this->addChild(healthPoint, 1);

	word = FlyWord::create(5, Vec2(384, 512));
	this->addChild(word, 10);
	/*主要对象的生成 包括飞机和子弹*/
	{
		//定时随机产生敌机
		//schedule(schedule_selector(SecondScene::managerEnemyPlanes), 1.0f);

		//定时产生我方子弹并移动
		schedule(schedule_selector(SecondScene::mangerMainBullet), 0.2f);
		schedule(schedule_selector(SecondScene::moveBullet), 0.005f);


		//添加我方英雄飞机
		heroPlaneG = HeroPlane::createHeroPlane("heroPlane.png");
		heroPlaneG->setAnchorPoint(Vec2(0.5, 0.5));
		heroPlaneG->setPosition(Vec2(visibleSize.width / 2, 100));
		heroPlaneG->setTag(4);//我方飞机tag为10
		{
			//设置物理body
			auto body = PhysicsBody::createBox(heroPlaneG->getContentSize());
			//body->setContactTestBitmask(0xFFFFFFFF);
			//body->setCategoryBitmask(0x02);
			//body->setContactTestBitmask(0x08);
			body->setCollisionBitmask(0x0);
			body->setContactTestBitmask(0xFFFFFFFF);
			body->setCategoryBitmask(0xFFFFFFFF);
			heroPlaneG->setPhysicsBody(body);
		}
		addChild(heroPlaneG, 1);

		/*	产生队列 敌方飞机*/
		auto enemyPath1 = EnemyPath::create();
		enemyPath1->getHero(heroPlaneG);
		addChild(enemyPath1,1);
		enemyPath1->chapter1();

	}
	/*轮播背景 设置按钮*/
	{
		//背景
		bgImg = Sprite::create("gameBgp2.png");
		bgImg->setAnchorPoint(Vec2(0.5, 0.5));
		bgImg->setPosition(Vec2(384, 512));
		addChild(bgImg);
		//第二张背景图
		bgTop = Sprite::create("gameBgp2.png");
		bgTop->setAnchorPoint(Vec2(0.5, 0.5));
		bgTop->setPosition(Vec2(384, 1536));
		addChild(bgTop);
		schedule(schedule_selector(SecondScene::updateBgImg), 0.009);

		//设置按钮
		Sprite*normal1 = Sprite::create("setButtonNormal.png");
		Sprite*seleted1 = Sprite::create("setButtonSelected.png");
		MenuItemSprite*setBtn1 = MenuItemSprite::create(normal1, seleted1, CC_CALLBACK_1(SecondScene::changeToSetScene, this));
		Menu *btn1 = Menu::create(setBtn1, NULL);
		btn1->setAnchorPoint(Vec2(0.5, 0.5));
		btn1->setPosition(Vec2(721.5, 974));
		addChild(btn1);
	}

	/*移动我方飞机  边界检测响应事件*/
	{
		//创建触摸监听事件
		auto listener1 = EventListenerTouchOneByOne::create();
		//设置是否传递触摸
		listener1->setSwallowTouches(true);

		//通过 lambda 表达式实现触摸事件的回调函数
		listener1->onTouchBegan = [](Touch* touch, Event* event) {

			// target即为heroPlaneG精灵对象
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);

			// 点击精灵区域
			if (rect.containsPoint(locationInNode))
			{
				return true;
			}
			return false;
		};
		// 跟随鼠标点击移动
		listener1->onTouchMoved = [](Touch* touch, Event* event) {
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			CCSize planeSize = target->getContentSize();
			Size visibleSize = Director::getInstance()->getVisibleSize();

			// 分别判断四个边界
			if (target->getPositionX() > visibleSize.width - planeSize.width / 2) {
				target->setPositionX(visibleSize.width - planeSize.width / 2);
			}
			if (target->getPositionY() > visibleSize.height - planeSize.height / 2) {
				target->setPositionY(visibleSize.height - planeSize.height / 2);
			}
			if (target->getPositionX() < planeSize.width / 2)
			{
				target->setPositionX(planeSize.width / 2);
			}
			if (target->getPositionY() < planeSize.height / 2)
			{
				target->setPositionY(planeSize.height / 2);
			}
			// 移动精灵
			target->setPosition(target->getPosition() + touch->getDelta());
		};

		// 点击结束
		listener1->onTouchEnded = [=](Touch* touch, Event* event) {
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
		};
		// 绑定监听事件和精灵
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, heroPlaneG);
	}


	/*碰撞检测*/
	{
		// 注册物理碰撞事件监听
		auto listener = EventListenerPhysicsContact::create();
		listener->onContactBegin = [this](PhysicsContact& contact)
		{

			//scoreShowControl();

			log("onContactBegin");
			auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
			auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
			//我方子弹与敌方飞机的碰撞
			if (spriteA && spriteA->getTag() == 1
				&& spriteB && spriteB->getTag() == 0) {
				planeBlowup(spriteA);
				spriteB->removeFromParentAndCleanup(true);

			}
			if (spriteA &&spriteB &&spriteA->getTag() == 0
				&& spriteB->getTag() == 1) {
				planeBlowup(spriteB);
				spriteA->removeFromParentAndCleanup(true);
				
			}
			//

			else if (spriteA && spriteB &&spriteA->getTag() == 2
				&& spriteB->getTag() == 0) {
				planeBlowup(spriteA);
				spriteB->removeFromParentAndCleanup(true);

			}
		   else if (spriteA &&spriteB&&spriteA->getTag() == 0
				&& spriteB->getTag() == 2) {
				planeBlowup(spriteB);
				spriteA->removeFromParentAndCleanup(true);
			}
		   //
			else if (spriteA && spriteB &&spriteA->getTag() == 3
				&& spriteB->getTag() == 0) {
				planeBlowup(spriteA);
				spriteB->removeFromParentAndCleanup(true);

			}
			else if (spriteA &&spriteB&&spriteA->getTag() == 0
				&& spriteB->getTag() == 3) {
				planeBlowup(spriteB);
				spriteA->removeFromParentAndCleanup(true);

			}


			/*
			//我方飞机与敌方飞机的碰撞
			else if (spriteA && spriteB &&spriteA->getTag() == 3
				&& spriteB->getTag() == 10) {
				planeBlowup(spriteA);

			}
			else if (spriteA &&spriteB&&spriteA->getTag() == 10
				&& spriteB->getTag() == 3) {
				planeBlowup(spriteB);

			}
			else if (spriteA && spriteB &&spriteA->getTag() == 2
				&& spriteB->getTag() == 10) {
				planeBlowup(spriteA);

			}
			else if (spriteA &&spriteB&&spriteA->getTag() == 10
				&& spriteB->getTag() == 2) {
				planeBlowup(spriteB);

				else if (spriteA && spriteB &&spriteA->getTag() == 1
				&& spriteB->getTag() == 4) {
				planeBlowup(spriteA);

				}
				else if (spriteA &&spriteB&&spriteA->getTag() == 4
				&& spriteB->getTag() == 1) {
				planeBlowup(spriteB);
				}
		
			}
	
			*/




			return true;
		};

		listener->onContactPreSolve = [](PhysicsContact& contact,
			PhysicsContactPreSolve& solve) {
			return true;
		};
		listener->onContactPostSolve = [](PhysicsContact& contact,
			const PhysicsContactPostSolve& solve) {
		};

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(
			listener, 1);
	}
	return true;
}
//
void SecondScene::initAllParamters() {

	scoreNumber = 0;

	enemyNumber = 0;

}

	
void SecondScene::changeToSetScene(Ref *object) {

	/*截取当前场景的图片并保存*/

	auto size = Director::getInstance()->getWinSize();
	//RenderTexture是一个纹理渲染类，我们需要把要渲染的当前场景放进去，这是初始化它的大小
	render = RenderTexture::create(size.width, size.height);
	//开始获取内容
	render->begin();
	//是用节点的visit方法加入到渲染中
	Director::getInstance()->getRunningScene()->visit();
	//结束
	render->end();
	render->retain();

	//3.0 截屏需要在截完屏的下一帧才能处理RenderTexture
	auto _schedule = this->getScheduler();
	auto replaceScene = [&](float tm)
	{
		//最后切换场景
		Director::getInstance()->pushScene(MainGamePauseLayer::createScene(render));
	};
	_schedule->schedule(replaceScene, this, 0.0f, 0, 0.0f, false, "screenshot1");
	
}




//创建我方飞机子弹
void SecondScene::mangerMainBullet(float time) {
	Bullet* blt = Bullet::createBullet("heroBullet.png");
	Vec2 planeLocal = heroPlaneG->getPosition();
	blt->type = bullet_main;
	planeLocal = Vec2(planeLocal.x + 4, planeLocal.y + 65);
	blt->setPosition(planeLocal);
	blt->setTag(0);

	{
		//设置物理body
		auto body = PhysicsBody::createBox(blt->getContentSize());
		//body->setContactTestBitmask(0x08);
		body->setCollisionBitmask(0x0);
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setCategoryBitmask(0xFFFFFFFF);

		blt->setPhysicsBody(body);

	}
	addChild(blt, 1);
	/*
	//子弹飞行
	MoveTo * to = MoveTo::create(1, Vec2(planeLocal.x, planeLocal.y + 1024));
	CallFuncN *fun = CallFuncN::create(CC_CALLBACK_1(SecondScene::removeBullet, this));
	Sequence *seq = Sequence::create(to, fun, NULL);
	blt->runAction(seq);
	*/
}

//移除子弹
void SecondScene::removeBullet(Ref *object) {
	Bullet *blt = (Bullet *)object;
	blt->stopAllActions();
	removeChild(blt);
}

void SecondScene::removeHeroPlane(Ref * object)
{

}

void SecondScene::heroPlaneDie(Ref * object)
{
}







//随机生成敌方飞机
void SecondScene::managerEnemyPlanes(float time) {

	if (this->enemyNumber < 1000) {
		this->enemyNumber++;


		char enemyName[1003];
		int rand = random(1, 3);
		log("%d", rand);

		sprintf(enemyName, "enemyPlane%d.png", rand);
		log(enemyName);
		//EnemyPlane* enemy = EnemyPlane::createEnemyPlane(enemyName);

		NewEnemyPlane *enemy = NewEnemyPlane::createNewEnemyPlane(enemyName);

		//Sprite* enemy = Sprite::create(enemyName);
		enemy->setTag(rand);

		int Xlocal = random(50, 600);
		int Ylocal = (1050);

		int ZXLocal = Xlocal;
		int ZYLocal = -150;

		enemy->setPosition(Vec2(Xlocal, Ylocal));
		{
			//设置物理body
			auto body = PhysicsBody::createBox(enemy->getContentSize());
			body->setContactTestBitmask(0xFFFFFFFF);
			body->setGroup(-2);
			enemy->setPhysicsBody(body);
		}
		this->addChild(enemy, 1);

		MoveTo* move = MoveTo::create(random(3, 5), Vec2(ZXLocal, ZYLocal));
		CallFuncN* fun = CallFuncN::create(CC_CALLBACK_1(SecondScene::removePlane, this));
		Sequence* seq = Sequence::create(move, fun, NULL);

		enemy->runAction(seq);

	}

}

void SecondScene::planeBlowup(Sprite* plane) {

	auto animation = Animation::create();
	//设置两帧之间的时间间隔
	animation->setDelayPerUnit(0.3f);
	switch (plane->getTag())
	{
	case 1:
		animation->addSpriteFrameWithFile("enemyPlaneBoom1.png");
		addtionalScore = 1;
		break;
	case 2:
		animation->addSpriteFrameWithFile("enemyPlaneBoom2.png");
		addtionalScore = 2;

		break;
	case 3:
		animation->addSpriteFrameWithFile("enemyPlaneBoom3.png");
		addtionalScore = 4;

		break;
	case 10:
		animation->addSpriteFrameWithFile("heroPlane.png");
		break;
	default:
		break;
	}


	countScoreUse();

	auto animate = Animate::create(animation);
	auto remove = CallFunc::create(
		CC_CALLBACK_0(SecondScene::removePlane, this, plane));
	auto sequence = Sequence::create(animate, remove, nullptr);
	plane->runAction(sequence);

	//animation->addSpriteFrameWithFile("enermyPlaneBoom2.png");



}

void SecondScene::removePlane(Node* pTarget) {
	auto plane = (Sprite*)pTarget;
	if (plane != nullptr) {
		log("removePlane");
		//this->removeChild(plane);
		plane->removeFromParentAndCleanup(true);
	}
}

/*背景轮播*/

void SecondScene::changeBgImgPosition(Sprite *brImage_m) {
	if (brImage_m->getPosition().y <= -512) {
		brImage_m->setPosition(Vec2(384, 1534));
	}
	else {
		float yy = brImage_m->getPosition().y;
		yy -= 1;
		brImage_m->setPosition(Vec2(384, yy));
	}
}
void SecondScene::updateBgImg(float time) {
	changeBgImgPosition(this->bgImg);
	changeBgImgPosition(this->bgTop);
}


void SecondScene::MainMenuGame(Ref*object) {
	//跳转至主菜单页面
	Director *dir = Director::getInstance();
	dir->replaceScene(StartScene::createScene());
}

void SecondScene::scoreShowControl() {

	scoreNumber = scoreNumber + addtionalScore;
	log("scoreNumber: %d",scoreNumber);
	char scoreFormat[20];
	sprintf(scoreFormat, "Score: %d", scoreNumber);
	score->setString(scoreFormat);
	log(scoreFormat);
	
}
//分数
void SecondScene::countScoreUse() {
	//ScaleTo * max = ScaleTo::create(0.25, 1.5);
	//ScaleTo * min = ScaleTo::create(0.25, 0.5);
	//ScaleTo * start = ScaleTo::create(0.25, 1);
	CallFunc* textShow = CallFunc::create(CC_CALLBACK_0(SecondScene::scoreShowControl, this));
	Sequence* list = Sequence::create(textShow, NULL);

	score->runAction(list);



}

void SecondScene::moveBullet(float time) {
	Vector<Node*>allNodes = getChildren();
	for (int i = int(allNodes.size() - 1); i >= 0; i--) {
		auto node = allNodes.at(i);
		if (strcmp(typeid(*node).name(), typeid(Bullet).name()) == 0) {
			Bullet *Bullet_m = (Bullet*)node;
			if (Bullet_m->type == bullet_main) {
				auto yy = Bullet_m->getPosition().y ;
				if (yy <= 1024) {

					Bullet_m->setPositionY(yy + 8);
				}
				else
				{
					Bullet_m->stopAllActions();
					removeBullet(Bullet_m);
				}
			}
		}
	}
}