//
//  HelloWorldScene.h
//  Ministrike
//
//  Created by 帅英 侯 on 12-3-27.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "SimpleAudioEngine.h"
#include "score.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    
	~HelloWorld();
	HelloWorld();    
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
    
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
    
    void addTarget();
	void spriteMoveFinished(CCNode* sender);
    void gameLogic(float dt);
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void update(float dt);
protected:
	cocos2d::CCMutableArray<cocos2d::CCSprite*> *_targets;
	cocos2d::CCMutableArray<cocos2d::CCSprite*> *_projectiles;
	int _targetsKilled;
	Score* m_score;
};

#endif // __HELLOWORLD_SCENE_H__
