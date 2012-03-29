//
//  BaseActor.h
//  Ministrike
//
//  Created by 帅英 侯 on 12-3-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Ministrike_BaseActor_h
#define Ministrike_BaseActor_h

#include "cocos2d.h"

class BaseActor
{
public:
	BaseActor();
	~BaseActor(void);
    
	// get the sprite from the BaseActor
	cocos2d::CCSprite* sprite() {return m_sprite;}
    
    
	virtual void update_logic(cocos2d::ccTime dt) = 0;
    
	//a_pos: position on map
	void set_position(const cocos2d::CCPoint& a_pos);
    
	const cocos2d::CCPoint& get_position();
    
	bool is_contain_point(const cocos2d::CCPoint& a_point);
    
	void update_sprite_position_with_camera();
    
private:
    
protected:
    
	// sprite
	cocos2d::CCSprite* m_sprite;
    
	// layer 
	cocos2d::CCLayer* m_layer;
    
	// label
	cocos2d::CCLabelTTF* m_label;
    
};

#endif
