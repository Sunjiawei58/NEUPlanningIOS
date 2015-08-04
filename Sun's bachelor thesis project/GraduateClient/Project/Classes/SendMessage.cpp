//
//  SendMessage.cpp
//  Project
//
//  Created by sunjiawei on 15/5/27.
//
//

#include "SendMessage.h"
#include <string>
#include "stdio.h"
#include <iostream>
#include "HttpRequest.h"
#include "HttpClient.h"
#include <vector>
#include "cocos2d.h"
using namespace cocos2d::network;
using namespace std;
USING_NS_CC;
string SendMessage::getstring (const int n)
{
    std::stringstream newstr;
    newstr<<n;
    return newstr.str();
}

void SendMessage::message(std::string location)
{
    tt= time(NULL);
    t=localtime(&tt);
    month=t->tm_mon;
    day = t->tm_mday;
    hour = t->tm_hour;
    min = t->tm_min;
    
    std::string mess = "";
    std::string name=UserDefault::getInstance()->getStringForKey("username");
    std::string t = "";
    t = getstring(month+1)+"月"+getstring(day)+"日"+getstring(hour)+"时"+getstring(min)+"分";
    mess=t+" 邀请您一起来"+location;
    cout<<"message is "<<mess<<std::endl;
    
    std::string postdata = "";
    postdata="me="+name+"&message="+mess;
    request = new HttpRequest();
    
    request->setUrl("http://localhost:8080/Graduate/servlet/SendMessageServlet");
    request->setRequestType(HttpRequest::Type::POST);
    request->setTag("sendMessage");
    
    request->setResponseCallback(CC_CALLBACK_2(SendMessage::onHttpRequestCompleted, this));
    
    request->setRequestData(postdata.c_str(), strlen(postdata.c_str()));
    HttpClient::getInstance()->send(request);
    
    request->release();

    
}

void SendMessage::onHttpRequestCompleted(HttpClient *sender,HttpResponse *response)
{
    
    if(response==nullptr)
    {
        return;
    }
    log("回来了");
    if(!response->isSucceed())
    {
        log("failed...");
        return;
    }
    
    if (strcmp(response->getHttpRequest()->getTag(),"sendMessage")==0)
    {
        std::vector<char> *buffer = response->getResponseData();
        std::string content="";
        for (unsigned int i=0; i<buffer->size(); i++) {
            //        content.append(&(*buffer)[i]);
            content+=(*buffer)[i];
            //        log("%c",(*buffer)[i]);
        }
        log("content is %s",content.c_str());
        if(content=="1")
        {
            log("邀请成功");
        }
        else
        {
            log("邀请失败");
        }

    }
}