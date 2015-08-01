//
//  MyInfoLayer.cpp
//  Project
//
//  Created by sunjiawei on 15/5/23.
//
//

#include "MyInfoLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>
#include "stdio.h"
#include <iostream>
#include <sstream>
#include "EntryScene.h"
USING_NS_CC;
using namespace std;

#include "sqlite3.h"
#include "SqlLite3Utils.h"
using namespace cocos2d::ui;

string MyInfoLayer::getstring (const int n)
{
    std::stringstream newstr;
    newstr<<n;
    return newstr.str();
}
string MyInfoLayer::floatToString(float f)
{
    char buf[10];
    sprintf(buf, "%.2f",f);
    sscanf(buf, "%f", &f);
    std::stringstream newstr;
    newstr<<f;
    return newstr.str();
}
bool MyInfoLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
        
    }
    int id= 0;
    std::string username="";
    int totalStudyTime = 0;
    int totalSportsTime = 0;;
    int totalClassTime = 0;
    
    int studyTime = 0;
    int sportsTime = 0;
    int classTime = 0;
    string name = UserDefault::getInstance()->getStringForKey("username");

      db = SqlLite3Utils::getDBBase();
     
     sqlite3_stmt* stmt= SqlLite3Utils::getQueryStatementFromDBBase("select * from user where username='"+name+"'", db);
     
     while (sqlite3_step(stmt)== SQLITE_ROW) {
     
          id= sqlite3_column_int(stmt, 0);
          username= (const char*)sqlite3_column_text(stmt, 1);
          totalStudyTime = sqlite3_column_int(stmt, 3);
          totalSportsTime = sqlite3_column_int(stmt, 4);
          totalClassTime = sqlite3_column_int(stmt, 5);
         
          studyTime = sqlite3_column_int(stmt, 6);
          sportsTime = sqlite3_column_int(stmt, 7);
          classTime = sqlite3_column_int(stmt, 8);
         
     
         std::cout<<"the username is "<<username<<std::endl;
         std::cout<<"totalStudyTime:"<<totalStudyTime<<std::endl;
         std::cout<<"sports:"<<totalSportsTime<<std::endl;
         log(totalClassTime);
         std::cout<<"classT:"<<totalClassTime<<std::endl;
         log(studyTime);
         std::cout<<"stu"<<studyTime<<std::endl;
         log(sportsTime);
         std::cout<<"spo"<<sportsTime<<std::endl;
         log(classTime);
         std::cout<<"clas"<<classTime<<std::endl;
     
     
     }    //database setting and use
    
    
    
    
    
     SqlLite3Utils::closeDB(db);
     db=nullptr;
     sqlite3_finalize(stmt);
    
       //数据库的查询。可以取出数据
    
    
    auto infoLayer=CSLoader::createNode("InfoLayer.csb");
    addChild(infoLayer);
    
    std::cout<<floatToString(2.0)<<endl;
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    EventListenerTouchOneByOne* listener= EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    //listener->onTouchEnded = CC_CALLBACK_2(NeuMap::onTouchEnded,this);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){return true;};
    listener->onTouchMoved = [](Touch* touch, Event* event){};
    listener->onTouchEnded = [](Touch* touch, Event* event){};
    listener->onTouchCancelled = [](Touch* touch , Event* event){};
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, infoLayer);   //代码为了设置模态窗口
    
    Button* closeButton = static_cast<Button*>(infoLayer->getChildByName("CloseButton"));
    Button* logoutButton = static_cast<Button*>(infoLayer->getChildByName("Button_logout"));
    Button* clearButton = static_cast<Button*>(infoLayer->getChildByName("Button_clear"));
    Button* exitButton = static_cast<Button*>(infoLayer->getChildByName("Button_exit"));
    
    
    closeButton->addTouchEventListener(this, toucheventselector(MyInfoLayer::closeEvent));
    logoutButton->addTouchEventListener(this, toucheventselector(MyInfoLayer::logoutEvent));
    clearButton->addTouchEventListener(this, toucheventselector(MyInfoLayer::clearEvent));
    exitButton->addTouchEventListener(this, toucheventselector(MyInfoLayer::exitEvent));
    
    
    Text* nameText = static_cast<Text*>(infoLayer->getChildByName("Text_Name"));
    nameText->setString(username);
    
    Text* totalClassText = static_cast<Text*>(infoLayer->getChildByName("Text_TotalClass"));
    totalClassText->setString(getstring(totalClassTime));
    
    Text* totalStudyText = static_cast<Text*>(infoLayer->getChildByName("Text_TotalStudy"));
    totalStudyText->setString(getstring(totalStudyTime));
    
    Text* totalSportsText = static_cast<Text*>(infoLayer->getChildByName("Text_TotalSports"));
    totalSportsText->setString(getstring(totalSportsTime));
    
    Text* _classText = static_cast<Text*>(infoLayer->getChildByName("Text_Class"));
    _classText->setString(getstring(classTime));
    
    Text* _studyText = static_cast<Text*>(infoLayer->getChildByName("Text_Study"));
    _studyText->setString(getstring(studyTime));
    
    
    Text* _sportsText = static_cast<Text*>(infoLayer->getChildByName("Text_Sports"));
    _sportsText->setString(getstring(sportsTime));
    
    LoadingBar* loadingStudy = static_cast<LoadingBar*>(infoLayer->getChildByName("LoadingBar_s"));
    if(studyTime==0)
    {
        loadingStudy->setPercent(0);
        _studyText->setString("0");
    }
    else {
        
            loadingStudy->setPercent(studyTime/(float)totalStudyTime*100);
        _studyText->setString(floatToString(loadingStudy->getPercent())+"%");
        log("loading bar success...");
        std::cout<<studyTime/5.0*100<<std::endl;
        }
    
    LoadingBar* loadingClass = static_cast<LoadingBar*>(infoLayer->getChildByName("LoadingBar_c"));
    if(classTime==0)
    {
        loadingClass->setPercent(0);
        _classText->setString("0");
    }
    else
    {
        loadingClass->setPercent(classTime/(float)totalClassTime*100);
        _classText->setString(floatToString(loadingClass->getPercent())+"%");
    }
    
    LoadingBar* loadingSport = static_cast<LoadingBar*>(infoLayer->getChildByName("LoadingBar_spo"));
    if(sportsTime==0)
    {
        loadingSport->setPercent(0);
        _sportsText->setString("0");
        
    }
    else
    {
        loadingSport->setPercent(sportsTime/(float)totalSportsTime*100);
        _sportsText->setString(floatToString(loadingSport->getPercent())+"%");
    }
    return true;
    
}

void MyInfoLayer::closeEvent(Ref*,cocos2d::ui::TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            this->removeFromParent();
            break;      // close the layer
            
        default:
            break;
    }
}
void MyInfoLayer::logoutEvent(Ref*, TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            UserDefault::getInstance()->setStringForKey("username", "");
            UserDefault::getInstance()->flush();
            Director::getInstance()->replaceScene(EntryScene::createScene());
            break;
            
        default:
            break;
    }
}
void MyInfoLayer::clearEvent(Ref*, TouchEventType type)
{
    std::string username = UserDefault::getInstance()->getStringForKey("username");
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            db=SqlLite3Utils::getDBBase();
            sql="update user set totalClassTime=0, totalStudyTime=0, totalSportsTime=0, classTime=0, studyTime=0, sportsTime=0 where username='";
            sql=sql+username+"'";
            std::cout<<sql<<endl;
            isUpdated = SqlLite3Utils::updateDataFromDBBase(sql, db);
            if(isUpdated)
            {std::cout<<"清零成功"<<endl;}
            else std::cout<<"failed..."<<endl;
            SqlLite3Utils::closeDB(db);
            
            MyInfoLayer::init();
            break;
            
        default:
            break;
    }
}
void MyInfoLayer::exitEvent(Ref*, TouchEventType type)
{
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            exit(0);
            break;
            
        default:
            break;
    }
}
