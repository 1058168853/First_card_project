#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "tcpclient.h"
#include "CocosGUI.h"

using namespace cocos2d::ui;


class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    CREATE_FUNC(GameScene);
	void initUI();
	void onTouchLogin(Ref* pSender);
private:
	uv::TCPClient* m_pClient;
	TextField* m_pInputAccount;
	TextField* m_pInputPassword;
};

#endif // __GAMESCENE_SCENE_H__
