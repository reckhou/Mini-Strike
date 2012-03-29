#include "HelloWorldScene.h"
#include "defines.h"
#include "WinScene.h"
#include "SimpleAudioEngine.h"
#include "GameMenuScene.h"
using namespace cocos2d;

CCScene* WinScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        WinScene *layer = WinScene::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WinScene::init()
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
            menu_selector(WinScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

		// Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCSprite* pSprite = CCSprite::spriteWithFile("win.jpg");
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

        // Add the menu to WinScene layer as a child layer.
        this->addChild(pMenu, 1);

		// add menu items for tests
		m_pItmeMenu = CCMenu::menuWithItems(NULL);
		CCLabelTTF* label = CCLabelTTF::labelWithString("RETURN TO MENU", "Tahoma", 30);
		label->setColor(ccc3(0xff, 0x00, 0x00));
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(WinScene::menuCallback));

		m_pItmeMenu->addChild(pMenuItem, 1);
		pMenuItem->setPosition( CCPointMake( SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT - 10 ));
		m_pItmeMenu->setPosition( CCPointZero );

 		//m_pItmeMenu->setContentSize(CCSizeMake(SCREEN_WIDTH, 400.f));

		addChild(m_pItmeMenu);

		//setIsTouchEnabled(true);

		//addChild(pMenu, 1);

        bRet = true;
    } while (0);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
    return bRet;
}

void WinScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void WinScene::menuCallback(CCObject* pSender)
{
    // "Game Test" menu item clicked
    CCDirector::sharedDirector()->replaceScene(GameMenuScene::scene());
}

