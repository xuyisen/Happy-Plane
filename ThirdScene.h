#ifndef __ThirdScene_SCENE_H__
#define __ThirdScene_SCENE_H__

#include "cocos2d.h"
#include <stdio.h>
#include"StartScene.h"
#include "NewEnemyPlane.h"
#include "HeroPlane.h"
#include"FlyWord.h"

class EnemyPath;




using namespace cocos2d;
using namespace std;


class ThirdScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	Size visibleSize;
	//����
	Sprite *bgImg;
	Sprite *bgTop;
	//Sprite *heroPlaneG;
	HeroPlane* heroPlaneG;
	void MainMenuGame(Ref *object);
	//�������������ӵ�
	void mangerMainBullet(float time);
	//�Ƴ��ӵ�
	void removeBullet(Ref *object);
	//�Ƴ��ҷ��ɻ�
	void removeHeroPlane(Ref *object);
	//�ҷ��ɻ�����
	void heroPlaneDie(Ref *object);

	//��������
	void updateBgImg(float time);
	//�ı�λ��
	void changeBgImgPosition(Sprite *brImage_m);
	//��ת������ҳ��
	void changeToSetScene(Ref *object);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// �µĵл�������
	void managerEnemyPlanes(float time);
	
	///���Ƶл�����
	int enemyNumber;

	///��ʾ�ɼ�
	int scoreNumber;
	//���ӵķ���
	int addtionalScore;
	Label* score;



	///��Ҫ�Ƿ�������
	void scoreShowControl();

	void countScoreUse();

	void moveBullet(float time);

	///ͳһʵ�����ǵ���Ϸ������ʼ��
	void initAllParamters();

	//�µĵз��ɻ���������
	void newEnemyPlaneManage(float time);





    CREATE_FUNC(ThirdScene);




	void removePlane(Node* pSender);
	void planeBlowup(Sprite* plane);

	Vector<Sprite*> mBullets;
	Vector<Sprite*> mPlanes;

	RenderTexture* render;
	RenderTexture* renderResult;

	FlyWord* word;

	
};

#endif // __ThirdScene_SCENE_H__
