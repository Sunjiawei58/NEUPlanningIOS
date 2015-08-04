//
//  SportsLayer.cpp
//  Project
//
//  Created by sunjiawei on 15/5/24.
//
//

#include "SportsLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>
#include "stdio.h"
#include <iostream>
USING_NS_CC;
using namespace std;

#include "sqlite3.h"
#include "SqlLite3Utils.h"
using namespace cocos2d::ui;

template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}   //   配合#include<sstream>可以把string 转化成float类型！！！！

bool SportsLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
//    std::cout<<sql<<std::endl;
    
    auto spoLayer=CSLoader::createNode("Layer3.csb");
    //Sprite* cSprite = static_cast<Sprite*>(stuLayer->getChildByName("CloseItem"));
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    EventListenerTouchOneByOne* listener= EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    //listener->onTouchEnded = CC_CALLBACK_2(NeuMap::onTouchEnded,this);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){return true;};
    listener->onTouchMoved = [](Touch* touch, Event* event){};
    listener->onTouchEnded = [](Touch* touch, Event* event){};
    listener->onTouchCancelled = [](Touch* touch , Event* event){};
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, spoLayer);   //代码为了设置模态窗口
    
    
    
    Button* okButton = static_cast<Button*>(spoLayer->getChildByName("OkButton"));
    Button* closeButton = static_cast<Button*>(spoLayer->getChildByName("CloseButton")); //获取成员变量
    textfield1 = static_cast<TextField*>(spoLayer->getChildByName("TextField_1"));
    
    okButton->addTouchEventListener(this, toucheventselector(SportsLayer::OkEvent));
    closeButton->addTouchEventListener(this, toucheventselector(SportsLayer::touchEvent));
    
    addChild(spoLayer);

    
    return true;
}

void SportsLayer::touchEvent(Ref*,TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            this->removeFromParent();    // close the layer
            break;
            
        default:
            break;
    }
    
}

void SportsLayer::OkEvent(Ref*,TouchEventType type)
{
    std::string name = UserDefault::getInstance()->getStringForKey("username");
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            sportsTime =  textfield1->getString();
            db=SqlLite3Utils::getDBBase();
            sql="update user set totalSportsTime=";
            sql=sql+sportsTime+" where username='"+name+"'";
            std::cout<<sportsTime<<endl;
            std::cout<<sql<<endl;
            isUpdated = SqlLite3Utils::updateDataFromDBBase(sql, db);
            if(isUpdated)
            {std::cout<<"更改成功"<<endl;}
            else std::cout<<"failed..."<<endl;
            SqlLite3Utils::closeDB(db);
            
            break;
            
        default:
            break;
    }
}






