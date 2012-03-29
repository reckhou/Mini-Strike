#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "score.h"
#include "WinScene.h"
#include "GameOverScene.h"

using namespace cocos2d;
//using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

HelloWorld::~HelloWorld()
{
    if (_targets)
    {
        _targets->release();
        _targets = NULL;
    }
    
    if (_projectiles)
    {
        _projectiles->release();
        _projectiles = NULL;
    }
    
    // cpp don't need to call super dealloc
    // virtual destructor will do this
}

HelloWorld::HelloWorld()
:_targets(NULL)
,_projectiles(NULL)
{
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    _targetsKilled = 0;
    this->setIsTouchEnabled(true);
    _targets = new CCMutableArray<CCSprite*>;
    _projectiles = new CCMutableArray<CCSprite*>;
    
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
    
	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
                                                                       "CloseNormal.png",
                                                                       "CloseSelected.png",
                                                                       this,
                                                                       menu_selector(HelloWorld::menuCloseCallback) );
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);
    
	/////////////////////////////
	// 3. add your codes below...
    
	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::spriteWithFile("gamescenebg.jpg");
    
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
    // Add player
    CCSprite *pPlayer = CCSprite::spriteWithFile("player.png", CCRect(0, 0, 77, 95) );
    pPlayer->setPosition( ccp(50, size.height/2) );
    this->addChild(pPlayer);
    
    // add score table.
    CCPoint a_position = ccp(SCREEN_HALF_WIDTH, SCREEN_HEIGHT - 30);
	m_score = new Score(this, a_position, this);
    m_score->init_score();
	this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
	this->schedule( schedule_selector(HelloWorld::update) );

	return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::addTarget()
{
    CCSprite *target = CCSprite::spriteWithFile("target.png", 
                                                CCRect(0,0,31,46) );
    //CCLOG("ADD!\n");
    // Determine where to spawn the target along the Y axis
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minY = target->getContentSize().height/2;
    int maxY = winSize.height - target->getContentSize().height/2;
    int rangeY = maxY - minY;
    srand( (unsigned)time(NULL) );
    int actualY = ( rand() % 10 * (maxY/10)) + minY;
    int actualYfinal = ( rand() % 10 * (maxY/10)) + minY;
    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated
    target->setPosition( 
                        ccp(winSize.width + (target->getContentSize().width/2), 
                            actualY) );
    this->addChild(target);
    
    // Determine speed of the target
    int minDuration = 1;
    int maxDuration = 3;
    int rangeDuration = maxDuration - minDuration;
    srand((unsigned)time(NULL) );
    int actualDuration = ( rand() % rangeDuration ) + minDuration;
    
    // Create the actions
    CCFiniteTimeAction* actionMove = 
    CCMoveTo::actionWithDuration( (ccTime)actualDuration, 
                                 ccp(0 - target->getContentSize().width/2, actualYfinal) );
    CCFiniteTimeAction* actionMoveDone = 
    CCCallFuncN::actionWithTarget( this, 
                                  callfuncN_selector(HelloWorld::spriteMoveFinished));
    target->runAction( CCSequence::actions(actionMove, 
                                           actionMoveDone, NULL) );
    target->setTag(1);
    _targets->addObject(target);
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
    
	if (sprite->getTag() == 1)  // target
	{
		_targets->removeObject(sprite);
		CCDirector::sharedDirector()->replaceScene(GameOverScene::scene());
	}
    else if (sprite->getTag() == 2) // projectile
	{
		_projectiles->removeObject(sprite);
	}
}

void HelloWorld::gameLogic(float dt)
{
    this->addTarget();
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->locationInView(touch->view());
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    // Set up initial location of projectile
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *projectile = CCSprite::spriteWithFile("projectile.png", 
                                                    CCRectMake(0, 0, 32, 6));
    projectile->setPosition( ccp(100, winSize.height/2+20) );
    
    // Determinie offset of location to projectile
    int offX = location.x - projectile->getPosition().x;
    int offY = location.y - projectile->getPosition().y;
    
    // Bail out if we are shooting down or backwards
    if (offX <= 0) return;
    
    // Ok to add now - we've double checked position
    projectile->setTag(2);
    _projectiles->addObject(projectile);
    this->addChild(projectile);  
    // Determine where we wish to shoot the projectile to
    int realX = winSize.width + (projectile->getContentSize().width/2);
    float ratio = (float)offY / (float)offX;
    int realY = (realX * ratio) + projectile->getPosition().y;
    CCPoint realDest = ccp(realX, realY);
    
    // Determine the length of how far we're shooting
    int offRealX = realX - projectile->getPosition().x;
    int offRealY = realY - projectile->getPosition().y;
    float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
    float velocity = 600/1;
    float realMoveDuration = length/velocity;
    
    // Move projectile to actual endpoint
    projectile->runAction( CCSequence::actions(
                                               CCMoveTo::actionWithDuration(realMoveDuration, realDest),
                                               CCCallFuncN::actionWithTarget(this, 
                                                                             callfuncN_selector(HelloWorld::spriteMoveFinished)), 
                                               NULL) );
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("fireak.wav");
}

void HelloWorld::update(float dt)
{
    CCMutableArray<CCSprite*> *projectilesToDelete =        
    new CCMutableArray<CCSprite*>;
    CCMutableArray<CCSprite*>::CCMutableArrayIterator it, jt, testt;
    
    for (it = _projectiles->begin(); it != _projectiles->end(); it++)
    {
        CCSprite *projectile =*it;
        CCRect projectileRect = CCRectMake(
                                           projectile->getPosition().x - (projectile->getContentSize().width/2),
                                           projectile->getPosition().y - (projectile->getContentSize().height/2),
                                           projectile->getContentSize().width,
                                           projectile->getContentSize().height);
        
        CCMutableArray<CCSprite*>*targetsToDelete =new CCMutableArray<CCSprite*>;
        //CCLOG("UPDATE2!!");            
        for (jt = _targets->begin(); jt != _targets->end(); jt++)
        {
            CCSprite *target =*jt;
            CCRect targetRect = CCRectMake(
                                           target->getPosition().x - (target->getContentSize().width/2),
                                           target->getPosition().y - (target->getContentSize().height/2),
                                           target->getContentSize().width,
                                           target->getContentSize().height);
            
            if (CCRect::CCRectIntersectsRect(projectileRect, targetRect))
            {
                targetsToDelete->addObject(target);
                //CCLOG("HIT!!");
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemydeath.wav");
                m_score->add_scroe(1);
                m_score->update_logic(dt);
            }
        }
        
        for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++)
        {
            CCSprite *target =*jt;
            _targets->removeObject(target);
            this->removeChild(target, true);
            _targetsKilled++;
            //CCLOG("%d killed!", _targetsKilled);
            if (_targetsKilled == GAMELENGTHVAL*10)
            {
                _targetsKilled = 0;
                CCDirector::sharedDirector()->replaceScene(WinScene::scene());
            }
        }
        
        if (targetsToDelete->count() >0)
        {
            projectilesToDelete->addObject(projectile);
        }
        targetsToDelete->release();
    }
    
    for (it = projectilesToDelete->begin(); it != projectilesToDelete->end(); it++)
    {
        CCSprite* projectile =*it;
        _projectiles->removeObject(projectile);
        this->removeChild(projectile, true);
    }
    projectilesToDelete->release();
}
