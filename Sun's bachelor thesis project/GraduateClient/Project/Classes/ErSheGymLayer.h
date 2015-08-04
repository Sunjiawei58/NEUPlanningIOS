//
//  ErSheGymLayer.h
//  Project
//
//  Created by sunjiawei on 15/5/24.
//
//

#ifndef __Project__ErSheGymLayer__
#define __Project__ErSheGymLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "sqlite3.h"
#include "SqlLite3Utils.h"
#include <time.h>

class ErSheGymLayer:public cocos2d::Layer {
    
    
public:
    virtual bool init();
    void closeEvent(Ref*,cocos2d::ui::TouchEventType type);
    void sportsEvent(Ref*,cocos2d::ui::TouchEventType type);
    void inviteEvent(Ref*,cocos2d::ui::TouchEventType type);
    std::string getstring (const int n);
    
    CREATE_FUNC(ErSheGymLayer);
    
private:
    time_t tt;
    tm* t;
    sqlite3* db;
    
    
    int spoStartHour;
    int spoStartMin;
    int spoEndHour;
    int spoEndMin;
    int spoDuration;
    int sportsTime;
    cocos2d::ui::Button * spoStartButton;
    cocos2d::ui::Button * inviteButton;
    
};

#endif /* defined(__Project__ErSheGymLayer__) */
