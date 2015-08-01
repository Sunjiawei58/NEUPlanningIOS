//
//  StudyLayer.h
//  Project
//
//  Created by sunjiawei on 15/5/19.
//
//

#ifndef __Project__StudyLayer__
#define __Project__StudyLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "sqlite3.h"
#include "SqlLite3Utils.h"

class StudyLayer : public cocos2d::Layer {
    
    
public:
    virtual bool init();
    CREATE_FUNC(StudyLayer);
    
    void touchEvent(Ref*,cocos2d::ui::TouchEventType type);   // 处理关闭按钮
    void OkEvent(Ref*,cocos2d::ui::TouchEventType type);    //处理统计学习时间
    void OkEvent2(Ref*,cocos2d::ui::TouchEventType type); //处理统计自习时间
private:
    sqlite3* db;
    bool isUpdated;
    std::string studyTime;
    std::string classTime;
    std::string sportsTime;
    std::string sql;
    cocos2d::ui::TextField* textfield1;
    cocos2d::ui::TextField* textfield2;
};

#endif /* defined(__Project__StudyLayer__) */
