//
//  EntryScene.cpp
//  Project
//
//  Created by sunjiawei on 15/5/8.
//
//

#include "EntryScene.h"
#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "NeuMap.h"
#include "HttpRequest.h"
#include "HttpClient.h"
#include <vector>
#include "SqlLite3Utils.h"

USING_NS_CC;
using namespace std;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace cocos2d::network;

Scene* EntryScene::createScene()
{
    auto s = Scene::create();
    
    auto layer= EntryScene::create();
    
    s->addChild(layer);
    return s;
}
bool EntryScene::init()
{
    if(!Layer::init())return false;
    
    auto wsize=Director::getInstance()->getWinSize();
    name="";
    pwd="";
//    auto bg_sprite = Sprite::create("NEU.jpg");
//    this->addChild(bg_sprite,0);
//    bg_sprite->setPosition(wsize/2);
//    
//    Button* enterButton=Button::create();
//    enterButton->setTouchEnabled(true);
//    enterButton->loadTextureNormal("7.jpg");
//    enterButton->setTitleText("Enter the software");
//    enterButton->setPosition(wsize/2);
//   enterButton->addTouchEventListener(this, toucheventselector(EntryScene::touchEvent));
//    
//    
//    this->addChild(enterButton,1);
    
    auto entryLayer = CSLoader::createNode("Entry.csb");
    this->addChild(entryLayer);
    
    Button* okButton = static_cast<Button*>(entryLayer->getChildByName("Button_Login"));
    
    Button* regButton = static_cast<Button*>(entryLayer->getChildByName("Button_Regist"));
    
    resText =  static_cast<Text*>(entryLayer->getChildByName("Text_res"));
    
    username = static_cast<TextField*>(entryLayer->getChildByName("TextField_username"));
    password = static_cast<TextField*>(entryLayer->getChildByName("TextField_password"));
    
    
    okButton->addTouchEventListener(this, toucheventselector(EntryScene::OkEvent));
    regButton->addTouchEventListener(this, toucheventselector(EntryScene::regEvent));
    
   
    
    return true;
}

void EntryScene::enterMain()
{
    
            Director::getInstance()->replaceScene(NeuMap::createScene());  //Enter the main
    
}
void EntryScene::OkEvent(Ref *, TouchEventType type)
{
    std::string postdata = "name=";
    name = username->getString();
    pwd = password->getString();
    postdata=postdata+name+"&password="+pwd;
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            request = new cocos2d::network::HttpRequest();
            
            request->setUrl("http://localhost:8080/Graduate/servlet/SearchUserServlet");
            request->setRequestType(HttpRequest::Type::POST);
            
            request->setResponseCallback(this, httpresponse_selector(EntryScene::onHttpRequestCompleted));
            
            request->setTag("login");
            
            request->setRequestData(postdata.c_str(), strlen(postdata.c_str()));
            
            cocos2d::network::HttpClient::getInstance()->send(request);
            
            request->release();
            break;
            
        default:
            break;
    }
}
void EntryScene::regEvent(Ref *, TouchEventType type)
{
    std::string postdata = "username=";
    name = username->getString();
    pwd = password->getString();
    postdata=postdata+name+"&password="+pwd;
    switch (type) {
        case cocos2d::ui::TOUCH_EVENT_ENDED:
            request = new cocos2d::network::HttpRequest();
            
            request->setUrl("http://localhost:8080/Graduate/servlet/AddUserServlet");
            request->setRequestType(HttpRequest::Type::POST);
            
            request->setResponseCallback(this, httpresponse_selector(EntryScene::onHttpRequestCompleted));
            
            request->setTag("regist");
            
            request->setRequestData(postdata.c_str(), strlen(postdata.c_str()));
            
            cocos2d::network::HttpClient::getInstance()->send(request);
            
            request->release();
            break;
            
        default:
            break;
    }

}

void EntryScene::onHttpRequestCompleted(cocos2d::network::HttpClient *sender,cocos2d::network::HttpResponse *response)
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
    if (strcmp(response->getHttpRequest()->getTag(),"login")==0) {
        
    
    std::vector<char> *buffer = response->getResponseData();
    std::string content="";
    for (unsigned int i=0; i<buffer->size(); i++) {
//        content.append(&(*buffer)[i]);
        content+=(*buffer)[i];
//        log("%c",(*buffer)[i]);
    }
    
    if(content=="1")
    {
        resText->setString("登录成功");
        resText->setVisible(true);
        
        UserDefault::getInstance()->setStringForKey("username", name);     // 把登录成功后的用户名暂时存在本地，以便后面的场景调用
         Director::getInstance()->replaceScene(NeuMap::createScene());
    }
    else
    {
        resText->setString("登录失败");
        resText->setVisible(true);
    }
        log("content is %s",content.c_str());
    }
    
    else if(strcmp(response->getHttpRequest()->getTag(),"regist")==0)
    {
        std::vector<char> *buffer = response->getResponseData();
        std::string content="";
        
        for(unsigned int i=0;i<buffer->size();i++)
        {
            content+=(*buffer)[i];
        }
        if(content=="1")
        {
            resText->setString("注册成功");
            resText->setVisible(true);
            UserDefault::getInstance()->setStringForKey("tname", username->getString());
            UserDefault::getInstance()->setStringForKey("tpwd", password->getString());
            initlize_data();
        }
        else
        {
            resText->setString("注册失败");
            resText->setVisible(true);
        }
        log("content is %s",content.c_str());
    }
    
    
}
void EntryScene::initlize_data(){
    //  注册之后初始化数据
    std::string tname = UserDefault::getInstance()->getStringForKey("tname");
    std::string tpwd = UserDefault::getInstance()->getStringForKey("tpwd");
    sqlite3* db = SqlLite3Utils::getDBBase();
    std::string sql="INSERT INTO user (username,password,totalStudyTime,totalSportsTime,totalClassTime,studyTime,sportsTime,classTime ) VALUES ('"+tname+"','"+tpwd+"',0,0,0,0,0,0);";
    bool isOk =  SqlLite3Utils::insertDataIntoDBBase(sql.c_str(), db);
    if(isOk)
    {
        log("插入成功");
    }
    else log("失败");
    SqlLite3Utils::closeDB(db);
    db=nullptr;
    
}
