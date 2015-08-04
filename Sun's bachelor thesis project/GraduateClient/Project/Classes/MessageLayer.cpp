//
//  MessageLayer.cpp
//  Project
//
//  Created by sunjiawei on 15/5/26.
//
//

#include "MessageLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>
#include "stdio.h"
#include <iostream>
#include "HttpRequest.h"
#include "HttpClient.h"
#include <vector>
USING_NS_CC;
using namespace std;

#include "sqlite3.h"
#include "SqlLite3Utils.h"
using namespace cocos2d::ui;
using namespace cocos2d::network;
std::vector<std::string> MessageLayer::split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;//扩展字符串以方便操作
    unsigned long size=str.size();
    
    for(unsigned long i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}
bool MessageLayer::init()
{
    
    if ( !Layer::init() )
    {
        return false;
        
    }
    auto wsize=Director::getInstance()->getWinSize();
    
    auto messageLayer=CSLoader::createNode("MessageShow.csb");
    this->addChild(messageLayer);
    
    Button * closeButton = static_cast<Button*>(messageLayer->getChildByName("CloseButton"));
    
    tMessage = static_cast<Text*>(messageLayer->getChildByName("Text_3"));
    closeButton->addTouchEventListener(this, toucheventselector(MessageLayer::closeEvent));
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    EventListenerTouchOneByOne* listener= EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){return true;};
    listener->onTouchMoved = [](Touch* touch, Event* event){};
    listener->onTouchEnded = [](Touch* touch, Event* event){};
    listener->onTouchCancelled = [](Touch* touch , Event* event){};
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, messageLayer);   //代码为了设置模态窗口

    
    std::string postdata="me=";
    postdata=postdata+UserDefault::getInstance()->getStringForKey("username");
    
    request = new HttpRequest();
    
    request->setUrl("http://localhost:8080/Graduate/servlet/SearchMessageServlet");
    request->setRequestType(HttpRequest::Type::POST);
    request->setTag("searchMessage");
    request->setResponseCallback(this, httpresponse_selector(MessageLayer::onHttpRequestCompleted));
    request->setRequestData(postdata.c_str(), strlen(postdata.c_str()));
    
    HttpClient::getInstance()->send(request);
    
    request->release();
    return true;
    
}
void MessageLayer::closeEvent(Ref*,TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            this->removeFromParent();
            break;      // close the layer
            
        default:
            break;
    }
}
void MessageLayer::onHttpRequestCompleted(HttpClient *sender,HttpResponse *response)
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
    if (strcmp(response->getHttpRequest()->getTag(),"searchMessage")==0)
    {
        
        std::vector<char> *buffer = response->getResponseData();
        std::string content="";
        std::string tmessage="";
        for (unsigned int i=0; i<buffer->size(); i++) {
            //        content.append(&(*buffer)[i]);
            content+=(*buffer)[i];
            //        log("%c",(*buffer)[i]);
        }
        log("content is %s",content.c_str());   //后面应该有文本的处理
        std::vector<std::string> result=split(content,"|");
        for(int i=0; i<result.size(); i++)
        {
            if(i%2==0)  //用户名
            
            { tmessage=tmessage+result[i];}
//            std::cout<<result[i]<<std::endl;
            if(i%2==1)   // 输入的地点
            {
                tmessage=tmessage+result[i]+"\n";
            }
            
        }
        log("%s",tmessage.c_str());
        tMessage->setString(tmessage);
    }
    

}
