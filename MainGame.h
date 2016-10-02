#ifndef __MainGame_SCENE_H__
#define __MainGame_SCENE_H__

#include "cocos2d.h"
#include <stdio.h>
#include"StartScene.h"
#include "NewEnemyPlane.h"
#include "HeroPlane.h"

class EnemyPath;
class Bullet;
class NewEnemyPlane;



using namespace cocos2d;
using namespace std;


class MainGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	~MainGame();

	Size visibleSize;
	//����
	Sprite *bgImg;
	Sprite *bgTop;
	HeroPlane* heroPlaneG;

	Bullet* blt1;
	Bullet* blt2;
	Bullet* blt3;

	EventListenerPhysicsContact *m_event;

	//�������������ӵ�
	void mangerMainBullet(float time);
	//�Ƴ��ӵ�
	void removeBullet(Ref *object);
	void removeBuff(Ref * object);
	//�Ƴ��ҷ��ɻ�
	void removeHeroPlane(Ref *object);
	//�ҷ��ɻ�����
	void heroPlaneDie(Ref *object);

	//��������
	void updateBgImg(float time);

	void deleteEvent() { m_event->autorelease(); }


	//�������Ӻ���

	//�ı�λ��
	void changeBgImgPosition(Sprite *brImage_m);
	//��ת������ҳ��
	void changeToSetScene(Ref *object);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// �µĵл�������
	void managerEnemyPlanes(float time);

	void changeTheHP();

	void changeTheScore();

	void refreshTheScore();

	void refreshTheHP();

	void moveBullet(float time);

	
	///���Ƶл�����
	int enemyNumber;

	int addtionalScore;

	int scoreNum;



	Label* score;
	Label *healthPoint;



	///��Ҫ�Ƿ�������




	///ͳһʵ�����ǵ���Ϸ������ʼ��
	void initAllParamters();


    CREATE_FUNC(MainGame);


private:

	void manageBuff(float time);

	void removePlane(Node* pSender);
	void planeBlowup(Sprite* plane);

	void judgeWhetherGameIsOver(float time);

	void gameOver();

	void victory();

	Vector<Sprite*> mBullets;
	Vector<Sprite*> mPlanes;

	RenderTexture* render;
	RenderTexture* renderResult;
};

#endif // __MainGame_SCENE_H__
