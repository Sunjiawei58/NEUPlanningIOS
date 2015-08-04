//
//  StudyLayer.cpp
//  Project
//
//  Created by sunjiawei on 15/5/19.
//
//

#include "StudyLayer.h"
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


bool StudyLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    
    
    std::cout<<sql<<std::endl;
    /*auto wsize=Director::getInstance()->getWinSize();
    Sprite * stulayer=Sprite::create("NEU.jpg");
    //stulayer->setAnchorPoint(Point(0.5,0.5));
    //stulayer->setContentSize(Size(400,200));
    this->addChild(stulayer);
    stulayer->setPosition(wsize/2);
    //stulayer->setPosition(Point(wsize.height/2,wsize.width/2));
    stulayer->setOpacity(180);   //scale is from 0 to 255
    EventListenerTouchOneByOne* listener= EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);    // 触点禁用
    
    Button* exitButton=Button::create();
    exitButton->setTouchEnabled(true);
    exitButton->loadTextureNormal("close.png");
    exitButton->setAnchorPoint(Point(0.5,0.5));
    exitButton->setPosition(Point(stulayer->getPositionX()+40,stulayer->getPositionY()-40));
    exitButton->setScale(0.5, 0.5);  // set the image scale
    //exitButton->setPosition(wsize/2);
    exitButton->addTouchEventListener(this, toucheventselector(StudyLayer::touchEvent));
    stulayer->addChild(exitButton,2);
    
    // the exit button
    
    
    auto labelClass = LabelTTF::create("上课的时间：", "Helvetica", 25);
    //lableClass->setString("上课时间：");
    
    stulayer->addChild(labelClass,2);
    
    labelClass->setPosition(Point(stulayer->getPositionX()-450,stulayer->getPositionY()/2));// need adjust
    labelClass->setColor(Color3B(255,0,0));
    labelClass->setOpacity(255);
    
    TextField* textField1 = TextField::create();
    textField1->setPlaceHolder("hour");
    textField1->setFontSize(25);
    textField1->setTouchEnabled(true);
    textField1->setPosition(Point(stulayer->getPositionX(),stulayer->getPositionY()/2));
    stulayer->addChild(textField1);
    
    
    MenuItemLabel* LClass = MenuItemLabel::create(labelClass);
     */
    
    auto stuLayer=CSLoader::createNode("Layer.csb");
    
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

    EventListenerTouchOneByOne* listener= EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){return true;};
    listener->onTouchMoved = [](Touch* touch, Event* event){};
    listener->onTouchEnded = [](Touch* touch, Event* event){};
    listener->onTouchCancelled = [](Touch* touch , Event* event){};
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, stuLayer);   //代码为了设置模态窗口

    
    
    Button* okButton = static_cast<Button*>(stuLayer->getChildByName("OkButton"));
    Button* closeButton = static_cast<Button*>(stuLayer->getChildByName("CloseButton")); //获取成员变量
    textfield1 = static_cast<TextField*>(stuLayer->getChildByName("TextField_1"));
    textfield2 = static_cast<TextField*>(stuLayer->getChildByName("TextField_2"));
    Button* okButton2 = static_cast<Button*>(stuLayer->getChildByName("OkButton2"));
    
    
        okButton->addTouchEventListener(this, toucheventselector(StudyLayer::OkEvent));
    okButton2->addTouchEventListener(this, toucheventselector(StudyLayer::OkEvent2));
    closeButton->addTouchEventListener(this, toucheventselector(StudyLayer::touchEvent));
    
    addChild(stuLayer);
    
    
    
    
    return true;
}

void StudyLayer::touchEvent(Ref*,TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            this->removeFromParent();    // close the layer
            break;
            
        default:
            break;
    }
    
}
void StudyLayer::OkEvent(Ref*,TouchEventType type)
{
    std::string username = UserDefault::getInstance()->getStringForKey("username");
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            studyTime =  textfield1->getString();
            db=SqlLite3Utils::getDBBase();
            sql="update user set totalStudyTime=";
            sql=sql+studyTime+" where username='"+username+"'";
            std::cout<<studyTime<<endl;
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

void StudyLayer::OkEvent2(Ref*,TouchEventType type)
{
    std::string username = UserDefault::getInstance()->getStringForKey("username");
    
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            classTime =  textfield2->getString();
            db=SqlLite3Utils::getDBBase();
            sql="update user set totalClassTime=";
            sql=sql+classTime+" where username='"+username+"'";
            std::cout<<classTime<<endl;
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

