//
//  SendMessage.h
//  Project
//
//  Created by sunjiawei on 15/5/27.
//
//

#ifndef __Project__SendMessage__
#define __Project__SendMessage__

#include <stdio.h>
#include <time.h>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SendMessage {
    
public:
    
    void message(std::string location);
    std::string getstring(const int n);
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender,cocos2d::network::HttpResponse *response);
private:
    time_t tt;
    tm* t;
    cocos2d::network::HttpRequest* request;
    
    int month;
    int day;
    int hour;
    int min;
    
};

#endif /* defined(__Project__SendMessage__) */
