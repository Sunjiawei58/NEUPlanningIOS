//
//  FriendLayer.cpp
//  Project
//
//  Created by sunjiawei on 15/5/26.
//
//

#include "FriendLayer.h"
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
string FriendLayer::getstring (const int n)
{
    std::stringstream newstr;
    newstr<<n;
    return newstr.str();
}

bool FriendLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
        
    }
    
    auto friendLayer=CSLoader::createNode("FriendLayer.csb");
    this->addChild(friendLayer);
    
    Button * closeButton = static_cast<Button*>(friendLayer->getChildByName("CloseButton"));
    
    Button * okButton = static_cast<Button*>(friendLayer->getChildByName("Button_OK"));
    
     fname = static_cast<TextField*>(friendLayer->getChildByName("TextField_Fname"));
    fshow = static_cast<Text*>(friendLayer->getChildByName("Text_show"));
    
    closeButton->addTouchEventListener(this, toucheventselector(FriendLayer::closeEvent));
    okButton->addTouchEventListener(this, toucheventselector(FriendLayer::okEvent));
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    EventListenerTouchOneByOne* listener= EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){return true;};
    listener->onTouchMoved = [](Touch* touch, Event* event){};
    listener->onTouchEnded = [](Touch* touch, Event* event){};
    listener->onTouchCancelled = [](Touch* touch , Event* event){};
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, friendLayer);   //代码为了设置模态窗口

    return true;
}
void FriendLayer::closeEvent(Ref*,TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            this->removeFromParent();
            break;      // close the layer
            
        default:
            break;
    }
}

void FriendLayer::okEvent(Ref*, TouchEventType type)
{
    std::string postdata="friend=";
    postdata=postdata+fname->getString()+"&me="+UserDefault::getInstance()->getStringForKey("username");
    std::cout<<UserDefault::getInstance()->getStringForKey("username")<<std::endl;
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            
            request = new HttpRequest();
            
            request->setUrl("http://localhost:8080/Graduate/servlet/AddFriendsServlet");
            request->setRequestType(HttpRequest::Type::POST);
            request->setTag("searchFriends");
            
            request->setResponseCallback(this, httpresponse_selector(FriendLayer::onHttpRequestCompleted));
            
            request->setRequestData(postdata.c_str(), strlen(postdata.c_str()));
            HttpClient::getInstance()->send(request);
            
            request->release();
            break;
            
        default:
            break;
    }
}
void FriendLayer::onHttpRequestCompleted(HttpClient *sender,HttpResponse *response)
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
    
    if (strcmp(response->getHttpRequest()->getTag(),"searchFriends")==0)
    {
        std::vector<char> *buffer = response->getResponseData();
        std::string content="";
        for (unsigned int i=0; i<buffer->size(); i++) {
            //        content.append(&(*buffer)[i]);
            content+=(*buffer)[i];
            //        log("%c",(*buffer)[i]);
        }
        if(content=="1")
        {
            fshow->setString("添加好友成功");
            fshow->setVisible(true);
        }
        else
        {
            fshow->setString("添加好友失败");
            fshow->setVisible(true);
        }
        log("content is %s",content.c_str());
    }
    
    
}