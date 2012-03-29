#include "score.h"
#include "cocos2d.h"
#include <math.h>
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Score::Score(cocos2d::CCLayer* a_layer, cocos2d::CCPoint & a_position, HelloWorld * a_game_play_field)
: m_game_play_field(a_game_play_field)
, m_score(0)
{
	//CCLOG("Score");
	m_layer = a_layer;

	m_label = CCLabelTTF::labelWithString("", "Tahoma", 30);
	m_label->setPosition(a_position);
	m_label->setColor(ccc3(0xff, 0x00, 0x00));
	a_layer->addChild(m_label);
}


Score::~Score(void)
{
	//CCLOG("~Score");

}

void Score::init_score(void)
{
    char buff[100];
	sprintf(buff, "%d terriosts left", 10*GAMELENGTHVAL - m_score);
	m_label->setString(buff);
}

void Score::update_logic( cocos2d::ccTime dt )
{
	//CCLOG("Update Score");
	char buff[100];
	sprintf(buff, "%d terriosts left", 10*GAMELENGTHVAL - m_score);
	m_label->setString(buff);
	if ( m_score == 1 )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("firstblood.wav");
	}
	
	if ( m_score == 1*GAMELENGTHVAL )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("doublekill.wav");
	}

	if ( m_score == 2*GAMELENGTHVAL )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tripplekill.wav");
	}

	if ( m_score == 3*GAMELENGTHVAL )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("killingspree.wav");
	}

	if ( m_score == 4*GAMELENGTHVAL )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("dominating.wav");

	}

	if ( m_score == 5*GAMELENGTHVAL )
	{		
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("megakill.mp3");
	}

	if ( m_score == 6*GAMELENGTHVAL )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("unstoppable.mp3");

	}

	if ( m_score == 7*GAMELENGTHVAL )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("whickedsick.mp3");

	}

	if ( m_score == 8*GAMELENGTHVAL )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("monsterkill.mp3");
	}

	if ( m_score == 9*GAMELENGTHVAL )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("godlike.mp3");	}

	if ( m_score == 10*GAMELENGTHVAL )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("holyshit.mp3");
	}
}

void Score::add_scroe(int a_score)
{
	m_score += a_score;
}