#ifndef __DEFINES_H__
#define __DEFINES_H__


// window size

#define SCREEN_WIDTH (cocos2d::CCDirector::sharedDirector()->getWinSize().width)
#define SCREEN_HEIGHT (cocos2d::CCDirector::sharedDirector()->getWinSize().height)
#define SCREEN_HALF_WIDTH (cocos2d::CCDirector::sharedDirector()->getWinSize().width * 0.5f)
#define SCREEN_HALF_HEIGHT (cocos2d::CCDirector::sharedDirector()->getWinSize().height * 0.5f)



// sprite defines
#define SPRITE_HEIGHT(sprite_point) (sprite_point->getContentSizeInPixels().height)
#define SPRITE_WIDTH(sprite_point) (sprite_point->getContentSizeInPixels().width)
#define SPRITE_HALF_HEIGHT(sprite_point) (sprite_point->getContentSizeInPixels().height * 0.5f)
#define SPRITE_HALF_WIDTH(sprite_point) (sprite_point->getContentSizeInPixels().width * 0.5f)
#define COLLIDE(a_sprite, a_point) (cocos2d::CCRect::CCRectContainsPoint(a_sprite->boundingBox(), *a_point))




// touch
// enum TouchState
// {
// 	START,		// down this frame
// 	END,		// up this frame
// 	PRESSED,	// pressed for more then one frame
// 	INACTIVE,	// neither of the above
// };



// point defines
#define NEW_POINT(p, x, y) cocos2d::CCPoint p = ccp(x, y)


// FPS
//#define DISPLAY_FPS 1
#define MAX_FPS 60.f
//#define MAX_FPS 36.f

// multi textures
#define MULTI_TEXTURES 1

// has tutorial
#define HAS_TUTORIAL 1

// language
#define ENGLISH 0
#define CHINESE 1

//#define LANGUAGE ENGLISH
#define LANGUAGE CHINESE

// data files
#define GAME_DATA_FILE "game_data.xml"
#define RECORD_DATA_FILE "record_data.xml"
#if (LANGUAGE == ENGLISH)
#define TEXT_DATA_FILE "text_english.xml"
#else
#define TEXT_DATA_FILE "text_chinese.xml"
#endif

// text and fonts
#define GET_TEXT(text_name) (GameState::DATA_MANAGER.get_value(text_name, TEXT_DATA_FILE).c_str())


// Util
// #define GET_SPRITE(a_name) (Util::TEXTURE_MANAGER.get_sprite(a_name))
// #define GET_RAND_INT(min, max) (Util::get_rand_int(min, max))

// debug
//#define DEBUG_SKIP_TUTORIAL 1

#endif // __DEFINES_H__