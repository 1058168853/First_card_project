#include "GameScene.h"
#include <mswsockdef.h>
#include <string>
#include "Protocol.h"

USING_NS_CC;
using namespace ui;

#define DEFAULT_PORT 8341
#define DEFAULT_IP "127.0.0.1"

GameScene::GameScene()
	:m_pClient(NULL)
	,m_pInputPassword(NULL)
	,m_pInputAccount(NULL)
{

}

GameScene::~GameScene()
{
	delete m_pClient;
}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
    return true;
}

void GameScene::initUI()
{
	int maxLength = 10;
	float desWidth = 100;
	Point origion = Director::getInstance()->getVisibleOrigin();
	Size sizeVisible = Director::getInstance()->getVisibleSize();
	Text* pAccount = Text::create("账号", "", 24);
	this->addChild(pAccount);
	pAccount->setPosition(Vec2(origion.x+sizeVisible.width/2, origion.y+sizeVisible.height/2));
	m_pInputAccount = TextField::create();
	this->addChild(m_pInputAccount);
	m_pInputAccount->setPosition(Vec2(pAccount->getPositionX()+desWidth, 
								pAccount->getPositionY()));
	m_pInputAccount->setMaxLengthEnabled(true);
	m_pInputAccount->setMaxLength(maxLength);
	m_pInputAccount->setString("123");
	Text* pPassword = Text::create("密码", "", 24);
	this->addChild(pPassword);
	pPassword->setPosition(Vec2(origion.x+sizeVisible.width/2, origion.y+sizeVisible.height/3));
	m_pInputPassword = TextField::create();
	this->addChild(m_pInputPassword);
	m_pInputPassword->setPosition(Vec2(pPassword->getPositionX()+desWidth, 
		pPassword->getPositionY()));
	m_pInputPassword->setMaxLengthEnabled(true);
	m_pInputPassword->setMaxLength(maxLength);
	m_pInputPassword->setPasswordEnabled(true);
	m_pInputPassword->setPasswordStyleText("#");
	m_pInputPassword->setString("123");
	Button* pButton = Button::create();
	pButton->setTitleText("登录");
	this->addChild(pButton);
	pButton->setPosition(Vec2(origion.x+sizeVisible.width/2, origion.y+sizeVisible.height/5));
	pButton->addClickEventListener(CC_CALLBACK_1(GameScene::onTouchLogin, this));
}

void GameScene::onEnter()
{
	Layer::onEnter();
	initUI();
}

void GameScene::onExit()
{
	Layer::onExit();
}

void GameScene::onTouchLogin( Ref* pSender )
{
	if (NULL == m_pClient)
	{
		m_pClient = new uv::TCPClient();
		bool bConnect = m_pClient->connect(DEFAULT_IP, DEFAULT_PORT);
	}
	std::string strAccount = m_pInputAccount->getStringValue();
	std::string strPassword = m_pInputPassword->getStringValue();
	if (strAccount.empty() || strPassword.empty())
	{
		return ;
	}

	char cBuffer[128];
	memset(cBuffer, 0, sizeof(cBuffer));
	sprintf_s(cBuffer, "%s, %s", strAccount.c_str(), strPassword.c_str());//strAccount+","+strPassword;
	CommonDataStruct data;
	data.data = cBuffer;
	data.type = eLogin;
	std::string strSend = Protocol::createProtocol(data);
	//m_pClient->send(&cBuffer[0], strSend.length());
	m_pClient->send(&strSend[0], strSend.length());
}
