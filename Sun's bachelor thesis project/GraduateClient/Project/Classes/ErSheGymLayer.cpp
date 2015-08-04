//
//  ErSheGymLayer.cpp
//  Project
//
//  Created by sunjiawei on 15/5/24.
//
//

#include "ErSheGymLayer.h"
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

string ErSheGymLayer::getstring (const int n)
{
    std::stringstream newstr;
    newstr<<n;
    return newstr.str();
}
bool ErSheGymLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
        
    }
    
    auto erSheGymLayer=CSLoader::createNode("ErSheGymLayer.csb");
    addChild(erSheGymLayer);
    
    tt = time(NULL);
    t =localtime(&tt);     //取到当前时间
    
    //    std::cout<<t->tm_hour<<std::endl;
    //    std::cout<<t->tm_min<<std::endl;
    
    Button * closeButton = static_cast<Button*>(erSheGymLayer->getChildByName("CloseButton"));
    
    spoStartButton = static_cast<Button*>(erSheGymLayer->getChildByName("SportsStart"));
    inviteButton = static_cast<Button*>(erSheGymLayer->getChildByName("invite"));
    inviteButton->addTouchEventListener(this, toucheventselector(ErSheGymLayer::inviteEvent));
    
    closeButton->addTouchEventListener(this, toucheventselector(ErSheGymLayer::closeEvent));
    
    spoStartButton->addTouchEventListener(this, toucheventselector(ErSheGymLayer::sportsEvent));
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    EventListenerTouchOneByOne* listener= EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){return true;};
    listener->onTouchMoved = [](Touch* touch, Event* event){};
    listener->onTouchEnded = [](Touch* touch, Event* event){};
    listener->onTouchCancelled = [](Touch* touch , Event* event){};
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, erSheGymLayer);   //代码为了设置模态窗口

    
    return true;
}

void ErSheGymLayer::closeEvent(Ref*,cocos2d::ui::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            this->removeFromParent();
            break;      // close the layer
            
        default:
            break;
    }
}

void ErSheGymLayer::sportsEvent(Ref*,cocos2d::ui::TouchEventType type)
{
    std::string name = UserDefault::getInstance()->getStringForKey("username");
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            
            if(spoStartButton->getTitleText()=="开始运动")
            {
                tt = time(NULL);
                t =localtime(&tt);     //取到当前时间
                spoStartHour=t->tm_hour;
                spoStartMin=t->tm_min;
                spoStartButton->setTitleText("结束");
                
            }
            else if (spoStartButton->getTitleText()=="结束")
            {
                tt= time(NULL);
                t=localtime(&tt);
                spoEndHour=t->tm_hour;
                spoEndMin=t->tm_min;
                spoDuration=(spoEndHour-spoStartHour)*60 + (spoEndMin-spoStartMin);   // 计算时间差,取出数据库中 上课时间 这一项，然后加上，再update
                std::cout<<"duration:"<<spoDuration<<std::endl;
                db = SqlLite3Utils::getDBBase();
                sqlite3_stmt* stmt= SqlLite3Utils::getQueryStatementFromDBBase("select * from user where username='"+name+"'", db);
                while (sqlite3_step(stmt)== SQLITE_ROW){
                    sportsTime = sqlite3_column_int(stmt, 7)+spoDuration;
                    std::cout<<sportsTime<<std::endl;
                }
                
                std::string sql="update user set sportsTime=";
                sql=sql+getstring(sportsTime)+" where username='"+name+"'";
                std::cout<<sql<<std::endl;
                bool isUpdated = SqlLite3Utils::updateDataFromDBBase(sql, db);
                if(isUpdated)
                {std::cout<<"更改成功"<<endl;}
                else std::cout<<"failed..."<<endl;
                SqlLite3Utils::closeDB(db);
                db=nullptr;
                sqlite3_finalize(stmt); // finalize after used..
                
                spoStartButton->setTitleText("开始运动");
            }
            
            break;
        default:
            break;
    }
}

void ErSheGymLayer::inviteEvent(Ref *, TouchEventType type)
{
    SendMessage* sm = new SendMessage();
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            
            sm->message("二舍运动场");
            break;
            
        default:
            break;
    }
    
    
}


