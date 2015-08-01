//
//  EntryScene.h
//  Project
//
//  Created by sunjiawei on 15/5/8.
//
//

#ifndef __EntryScene_SCENE_H__
#define __EntryScene_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

class EntryScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void enterMain();
    
    void OkEvent(Ref*,cocos2d::ui::TouchEventType type);
    void regEvent(Ref*,cocos2d::ui::TouchEventType type);
    void initlize_data();
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender,cocos2d::network::HttpResponse *response);

    // implement the "static create()" method manually
    CREATE_FUNC(EntryScene);
private:
    cocos2d::ui::TextField* username;
    cocos2d::ui::TextField* password;
    cocos2d::network::HttpRequest* request;
    cocos2d::ui::Text* resText;
    std::string name;
    std::string pwd;
    
    
};

#endif // __HELLOWORLD_SCENE_H__

