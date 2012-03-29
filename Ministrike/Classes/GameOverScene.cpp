#include "HelloWorldScene.h"
#include "defines.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "GameMenuScene.h"
using namespace cocos2d;

CCScene* GameOverScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameOverScene *layer = GameOverScene::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(GameOverScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

		// Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCSprite* pSprite = CCSprite::spriteWithFile("gameover.jpg");
        CC_BREAK_IF(! pSprite);
        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));
        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

		// Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to GameOverScene layer as a child layer.
        this->addChild(pMenu, 1);

		// add menu items for tests
		m_pItmeMenu = CCMenu::menuWithItems(NULL);
		CCLabelTTF* label = CCLabelTTF::labelWithString("RETRY", "Tahoma", 20);
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(GameOverScene::menuCallback));

		m_pItmeMenu->addChild(pMenuItem, 1);
		pMenuItem->setPosition( CCPointMake( SCREEN_WIDTH - 100, 50 ));
		m_pItmeMenu->setPosition( CCPointZero );

 		//m_pItmeMenu->setContentSize(CCSizeMake(SCREEN_WIDTH, 400.f));

		addChild(m_pItmeMenu);

		//setIsTouchEnabled(true);

		//addChild(pMenu, 1);

        bRet = true;
    } while (0);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("gameover.wav");
    return bRet;
}

void GameOverScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameOverScene::menuCallback(CCObject* pSender)
{
    // "Game Test" menu item clicked
    CCDirector::sharedDirector()->replaceScene(GameMenuScene::scene());
}

