//
//  BaseActor.cpp
//  Ministrike
//
//  Created by 帅英 侯 on 12-3-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "BaseActor.h"
#include "cocos2d.h"
#include <math.h>

using namespace cocos2d;

BaseActor::BaseActor()
: m_sprite(NULL)
, m_layer(NULL)
, m_label(NULL)
{
	CCLOG("BaseActor");
}

BaseActor::~BaseActor(void)
{
	if (m_sprite)
	{
		m_layer->removeChild(m_sprite, true);
	}
    
	if (m_label)
	{
		m_layer->removeChild(m_label, true);
	}
	
}

void BaseActor::update_logic( cocos2d::ccTime dt )
{
	//
}

void BaseActor::set_position( const cocos2d::CCPoint& a_pos )
{
	if (m_sprite != NULL)
	{
		m_sprite->setPosition(a_pos);
	}
    
	if (m_label != NULL)
	{
		m_label->setPosition(a_pos);
	}
}

const cocos2d::CCPoint& BaseActor::get_position()
{
	if (m_sprite != NULL)
	{
		return m_sprite->getPosition();
	}
    
	if (m_label != NULL)
	{
		return m_label->getPosition();
	}
    
	return (ccp(0.f, 0.f));
}

bool BaseActor::is_contain_point(const cocos2d::CCPoint& a_point)
{
	if (m_sprite != NULL)
	{
		return cocos2d::CCRect::CCRectContainsPoint(m_sprite->boundingBox(), a_point);
	}
	else if (m_label != NULL)
	{
		return cocos2d::CCRect::CCRectContainsPoint(m_label->boundingBox(), a_point);
	}
	else
	{
		return false;
	}
}