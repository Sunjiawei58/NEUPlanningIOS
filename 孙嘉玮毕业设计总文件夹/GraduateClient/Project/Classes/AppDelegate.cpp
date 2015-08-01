#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "EntryScene.h"
#include "NeuMap.h"
USING_NS_CC;
#include "SqlLite3Utils.h"
#include <vector>
#include <string>
#include "stdio.h"
#include <iostream>
#include <sstream>
using namespace std;

template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}   //   配合#include<sstream>可以把string 转化成float类型！！！！

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("Project", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }
 
    initlize_data();
//    string str("1.2");
//    cout << stringToNum<float>(str) << endl;
    
    
    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    
    auto scene = EntryScene::createScene();   // 在这里改入口场景

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void AppDelegate::initlize_data(){
//    std::cout<<"the path is "<<FileUtils::getInstance()->getWritablePath()<<std::endl;
    std::vector<std::string> vs;
    //vs.push_back("CREATE TABLE user (id integer PRIMARY KEY AUTOINCREMENT,username text,password text,totalStudyTime int,totalSportsTime int,totalClassTime int,studyTime int,sportsTime int,classTime int);");
    vs.push_back("INSERT INTO user ( id,username,password,totalStudyTime,totalSportsTime,totalClassTime,studyTime,sportsTime,classTime ) VALUES ( '1','sjw','321','12’,’8’,’6’,’1’,’2’,’1’ );");
//    vs.push_back("");
//    vs.push_back("");
//    vs.push_back("");
//    vs.push_back("");
    
    
//    auto it=  vs.begin();
//    std::cout<<"size is "<<vs.size()<<std::endl;
//    sqlite3* db = SqlLite3Utils::getDBBase();
//    while (it!= vs.end()) {
//        
//        auto& v= *it;
//        bool isOk= SqlLite3Utils::insertDataIntoDBBase(v, db);
////        std::cout<<isOk<<endl;
//        if (isOk) {
//            log("插入数据库成功");
//        }
//        it++;
//        
//        
//        
//    }
    sqlite3* db = SqlLite3Utils::getDBBase();
    std::string sql="INSERT INTO user (id,username,password,totalStudyTime,totalSportsTime,totalClassTime,studyTime,sportsTime,classTime ) VALUES (1,'sjw','321',12,8,6,1,2,1);";
    bool isOk =  SqlLite3Utils::insertDataIntoDBBase(sql.c_str(), db);
    if(isOk)
    {
        log("插入成功");
    }
    else log("失败");
    SqlLite3Utils::closeDB(db);
    db=nullptr;
    
}