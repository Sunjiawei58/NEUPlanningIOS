//
//  SportsLayer.h
//  Project
//
//  Created by sunjiawei on 15/5/24.
//
//

#ifndef __Project__SportsLayer__
#define __Project__SportsLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "sqlite3.h"
#include "SqlLite3Utils.h"

class SportsLayer: public cocos2d::Layer {
    
    
public:
    virtual bool init();
    CREATE_FUNC(SportsLayer);
    
    void touchEvent(Ref*,cocos2d::ui::TouchEventType type);   // 处理关闭按钮
    void OkEvent(Ref*,cocos2d::ui::TouchEventType type);    //处理统计运动时间
private:
    sqlite3* db;
    bool isUpdated;
    std::string sportsTime;
    std::string sql;
    cocos2d::ui::TextField* textfield1;
};

#endif /* defined(__Project__SportsLayer__) */
