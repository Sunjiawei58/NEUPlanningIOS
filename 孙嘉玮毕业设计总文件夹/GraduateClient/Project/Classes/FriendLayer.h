//
//  FriendLayer.h
//  Project
//
//  Created by sunjiawei on 15/5/26.
//
//

#ifndef __Project__FriendLayer__
#define __Project__FriendLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "sqlite3.h"
#include "SqlLite3Utils.h"
#include <time.h>
#include "HttpRequest.h"
#include "HttpResponse.h"

class FriendLayer: public cocos2d:: Layer {
    
    
public:
    virtual bool init();
    CREATE_FUNC(FriendLayer);
    std::string getstring(const int n);
    void closeEvent(Ref*,cocos2d::ui::TouchEventType type);
    void okEvent(Ref*,cocos2d::ui::TouchEventType type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender,cocos2d::network::HttpResponse *response);
private:
    sqlite3* db;
    cocos2d::network::HttpRequest* request;
    cocos2d::ui::TextField * fname;
    cocos2d::ui::Text * fshow;
    
};

#endif /* defined(__Project__FriendLayer__) */
