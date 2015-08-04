//
//  NeuMap.h
//  Project
//
//  Created by sunjiawei on 15/5/14.
//
//

#ifndef __Project__NeuMap__
#define __Project__NeuMap__

#include "cocos2d.h"

class NeuMap : public cocos2d::Layer
{
public:
    static cocos2d:: Scene* createScene();
    virtual bool init();
    CREATE_FUNC(NeuMap);
    
    void menuCallback(Ref *psender);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event event);
    int isPass(int GID);
    void mainEvents();
    void infoEvents();
    void sportsEvents();
    void studyEvents();
    void friendEvents();
    void messageEvents();
    
    void JiaoxueEvents();
    void ErSheGymEvents();
    void LibraryEvents();
    void CaiKuangEvents();
    
private:
    cocos2d::TMXTiledMap* map;
    cocos2d::Sprite* Player;
    cocos2d::TMXLayer* buildings;
    cocos2d::TMXLayer* _events;
    
};
#endif /* defined(__Project__NeuMap__) */
