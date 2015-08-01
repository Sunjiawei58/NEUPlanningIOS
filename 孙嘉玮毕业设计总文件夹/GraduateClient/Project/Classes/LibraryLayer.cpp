//
//  LibraryLayer.cpp
//  Project
//
//  Created by sunjiawei on 15/5/24.
//
//

#include "LibraryLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>
#include "stdio.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <SendMessage.h>
USING_NS_CC;
using namespace std;

#include "sqlite3.h"
#include "SqlLite3Utils.h"
using namespace cocos2d::ui;
string LibraryLayer::getstring (const int n)
{
    std::stringstream newstr;
    newstr<<n;
    return newstr.str();
}


bool LibraryLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
        
    }
    
    auto libraryLayer=CSLoader::createNode("LibraryLayer.csb");
    addChild(libraryLayer);
    
    tt = time(NULL);
    t =localtime(&tt);     //取到当前时间
    
    //    std::cout<<t->tm_hour<<std::endl;
    //    std::cout<<t->tm_min<<std::endl;
    
    Button * closeButton = static_cast<Button*>(libraryLayer->getChildByName("CloseButton"));
    inviteButton = static_cast<Button*>(libraryLayer->getChildByName("invite"));
    inviteButton->addTouchEventListener(this, toucheventselector(LibraryLayer::inviteEvent));
    
    
    sStartButton = static_cast<Button*>(libraryLayer->getChildByName("StudyStart"));
    
    
    
    closeButton->addTouchEventListener(this, toucheventselector(LibraryLayer::closeEvent));
    
    
    sStartButton->addTouchEventListener(this, toucheventselector(LibraryLayer::studyEvent));
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    EventListenerTouchOneByOne* listener= EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){return true;};
    listener->onTouchMoved = [](Touch* touch, Event* event){};
    listener->onTouchEnded = [](Touch* touch, Event* event){};
    listener->onTouchCancelled = [](Touch* touch , Event* event){};
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, libraryLayer);   //代码为了设置模态窗口

    return true;
}

void LibraryLayer::closeEvent(Ref*,cocos2d::ui::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            this->removeFromParent();
            break;      // close the layer
            
        default:
            break;
    }
}


void LibraryLayer::studyEvent(Ref*,cocos2d::ui::TouchEventType type)
{
    std::string name = UserDefault::getInstance()->getStringForKey("username");
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            
            if(sStartButton->getTitleText()=="开始自习")
            {
                tt = time(NULL);
                t =localtime(&tt);     //取到当前时间
                sStartHour=t->tm_hour;
                sStartMin=t->tm_min;
                sStartButton->setTitleText("结束自习");
                
            }
            else if (sStartButton->getTitleText()=="结束自习")
            {
                tt= time(NULL);
                t=localtime(&tt);
                sEndHour=t->tm_hour;
                sEndMin=t->tm_min;
                sDuration=(sEndHour-sStartHour)*60 + (sEndMin-sStartMin);   // 计算时间差,取出数据库中 上课时间 这一项，然后加上，再update
                std::cout<<"duration:"<<sDuration<<std::endl;
                db = SqlLite3Utils::getDBBase();
                sqlite3_stmt* stmt= SqlLite3Utils::getQueryStatementFromDBBase("select * from user where username='"+name+"'", db);
                while (sqlite3_step(stmt)== SQLITE_ROW){
                    studyTime = sqlite3_column_int(stmt, 6)+sDuration;
                    std::cout<<studyTime<<std::endl;
                }
                
                std::string sql="update user set studyTime=";
                sql=sql+getstring(studyTime)+" where username='"+name+"'";
                std::cout<<sql<<std::endl;
                bool isUpdated = SqlLite3Utils::updateDataFromDBBase(sql, db);
                if(isUpdated)
                {std::cout<<"更改成功"<<endl;}
                else std::cout<<"failed..."<<endl;
                SqlLite3Utils::closeDB(db);
                db=nullptr;
                sqlite3_finalize(stmt); // finalize after used..
                
                sStartButton->setTitleText("开始自习");
            }
            
            
            
            
            
            break;
        default:
            break;
    }
}
void LibraryLayer::inviteEvent(Ref *, TouchEventType type)
{
    SendMessage* sm = new SendMessage();
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            
            sm->message("图书馆");
            break;
            
        default:
            break;
    }
    
    
}
