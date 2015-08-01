//
//  MyInfoLayer.h
//  Project
//
//  Created by sunjiawei on 15/5/23.
//
//

#ifndef __Project__MyInfoLayer__
#define __Project__MyInfoLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "sqlite3.h"
#include "SqlLite3Utils.h"
// 查看个人的信息

class MyInfoLayer : public cocos2d::Layer {
    
    
public:
    virtual bool init();
    CREATE_FUNC(MyInfoLayer);
    
    void closeEvent(Ref*,cocos2d::ui::TouchEventType type);
    void logoutEvent(Ref*,cocos2d::ui::TouchEventType type);
    void clearEvent(Ref*,cocos2d::ui::TouchEventType type);
    void exitEvent(Ref*,cocos2d::ui::TouchEventType type);
    
    std::string getstring (const int n);
    std::string floatToString(const float f);
//    void OkEvent(Ref*,cocos2d::ui::TouchEventType type);
private:
    sqlite3* db;
    std::string sql;
    bool isUpdated;
    
};


#endif /* defined(__Project__MyInfoLayer__) */
