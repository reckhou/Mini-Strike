#include "HelloWorldScene.h"
#include "defines.h"
#include "GameMenuScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

static CCNode* menuTarget;
static int Bugcnt;

CCScene* GameMenuScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameMenuScene *layer = GameMenuScene::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMenuScene::init()
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
            menu_selector(GameMenuScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
        menuTarget = this;
        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to GameMenuScene layer as a child layer.
        this->addChild(pMenu, 1);

		// Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCSprite* pSprite = CCSprite::spriteWithFile("menubg.jpg");
        CC_BREAK_IF(! pSprite);
        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

		m_pItmeMenu = CCMenu::menuWithItems(NULL);
		CCLabelTTF* label = CCLabelTTF::labelWithString("Mini Strike", "Tahoma", 80);
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(GameMenuScene::menuCallback));
		m_pItmeMenu->addChild(pMenuItem, 1);
		pMenuItem->setPosition( CCPointMake( SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT ));
		m_pItmeMenu->setPosition( CCPointZero );
		addChild(m_pItmeMenu);
        bRet = true;
    } while (0);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menubg2.mp3", true);
    
    //this->schedule( schedule_selector(GameMenuScene::menuHint), 2.0 );

    return bRet;
}

void GameMenuScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameMenuScene::menuCallback(CCObject* pSender)
{
	CCLOG("%s", __FUNCTION__);
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void GameMenuScene::menuHint(void)
{
    // add a label shows "Hello World"
	// create and initialize a label
	CCLabelTTF* pLabel = CCLabelTTF::labelWithString("AAAAAAAAA", "Thonburi", 80);
    
	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
	// position the label on the center of the screen
	pLabel->setPosition( ccp(size.width / 2-150, size.height - 230) );
    
	// add the label as a child to this layer
    
    sleep(1);
    if (Bugcnt != 0) {
        menuTarget->removeChild(pLabel, true);
        Bugcnt--;
        CCLOG("menuHint()rmv \n");
    } else {
        menuTarget->addChild(pLabel);
        Bugcnt++;
        CCLOG("menuHint()add \n");
    }
}
