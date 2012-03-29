#ifndef __SCORE_H__
#define __SCORE_H__

#include "cocos2d.h"
#include "BaseActor.h"
#include "defines.h"

#define GAMELENGTHVAL 1

class HelloWorld;

class Score : public BaseActor
{
public:
	Score(cocos2d::CCLayer * a_layer, cocos2d::CCPoint & a_position, HelloWorld * a_game_play_field);
	~Score(void);

	void update_logic(cocos2d::ccTime dt);
	void init_score(void);
	void add_scroe(int a_score);

private:
	HelloWorld* m_game_play_field;
	int m_score;
};
#endif // __SCORE_H__