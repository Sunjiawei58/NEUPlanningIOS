//
//  JiaoXueLayer.h
//  Project
//
//  Created by sunjiawei on 15/5/23.
//
//

#ifndef __Project__JiaoXueLayer__
#define __Project__JiaoXueLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "sqlite3.h"
#include "SqlLite3Utils.h"
#include <time.h>
class JiaoXueLayer: public cocos2d::Layer {
    
    
public:
    virtual bool init();
    void closeEvent(Ref*,cocos2d::ui::TouchEventType type);
    void classEvent(Ref*,cocos2d::ui::TouchEventType type);
    void studyEvent(Ref*,cocos2d::ui::TouchEventType type);
    void inviteEvent(Ref*,cocos2d::ui::TouchEventType type);
    std::string getstring (const int n);
    
    CREATE_FUNC(JiaoXueLayer);
    
private:
    time_t tt;
    tm* t;
    sqlite3* db;
    
    int sStartHour;
    int sStartMin;
    int sEndHour;
    int sEndMin;
    int sDuration;
    int cStartHour;
    int cStartMin;
    int cEndHour;
    int cEndMin;
    int cDuration;
    int classTime;
    int studyTime;
    cocos2d::ui::Button * sStartButton;
    
    cocos2d::ui::Button * cStartButton;
    cocos2d::ui::Button * inviteButton;
    
    
    
};
#endif /* defined(__Project__JiaoXueLayer__) */