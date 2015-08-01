//
//  MessageLayer.h
//  Project
//
//  Created by sunjiawei on 15/5/26.
//
//

#ifndef __Project__MessageLayer__
#define __Project__MessageLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "sqlite3.h"
#include "SqlLite3Utils.h"
#include <time.h>
#include "HttpRequest.h"
#include "HttpResponse.h"

class MessageLayer: public cocos2d::Layer {
    
    
public:
    virtual bool init();
    CREATE_FUNC(MessageLayer);
    void closeEvent(Ref*,cocos2d::ui::TouchEventType type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender,cocos2d::network::HttpResponse *response);
    std::vector<std::string> split(std::string str,std::string pattern);    //处理字符串分隔的函数
private:
    cocos2d::network::HttpRequest* request;
    cocos2d::ui::Text * tMessage;
};

#endif /* defined(__Project__MessageLayer__) */
