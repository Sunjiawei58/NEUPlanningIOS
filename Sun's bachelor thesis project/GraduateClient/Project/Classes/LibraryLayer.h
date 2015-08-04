//
//  LibraryLayer.h
//  Project
//
//  Created by sunjiawei on 15/5/24.
//
//

#ifndef __Project__LibraryLayer__
#define __Project__LibraryLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "sqlite3.h"
#include "SqlLite3Utils.h"

class LibraryLayer : public cocos2d::Layer {
    
    
public:
    virtual bool init();
    void closeEvent(Ref*,cocos2d::ui::TouchEventType type);
    void studyEvent(Ref*,cocos2d::ui::TouchEventType type);
     void inviteEvent(Ref*,cocos2d::ui::TouchEventType type);
    std::string getstring (const int n);
    
    CREATE_FUNC(LibraryLayer);
    
private:
    time_t tt;
    tm* t;
    sqlite3* db;
    
    int sStartHour;
    int sStartMin;
    int sEndHour;
    int sEndMin;
    int sDuration;

    int studyTime;
    cocos2d::ui::Button * sStartButton;
    cocos2d::ui::Button * inviteButton;
    
    
    
    
};


#endif /* defined(__Project__LibraryLayer__) */
