#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "sqlite3.h"
#include "iostream"
#include "stdio.h"
#include "SqlLite3Utils.h"
USING_NS_CC;
using namespace std;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    
    addChild(rootNode);
    
    
    /*sqlite3* database;
    std::string dataPath="mybata.db";
    dataPath=FileUtils::getInstance()->getWritablePath()+dataPath;
    
    int result = sqlite3_open(dataPath.c_str(), &database);
    
    if(result == SQLITE_OK)
    {
        std::cout<<"成功打开数据库"<<endl;
    }
        // 数据库的打开和创建流程
    
    sqlite3_close(database);
    database=nullptr;    //一定要记住关闭数据库
    */       // 创建打开操作关闭数据库的一般流程
    
    
    sqlite3* db = SqlLite3Utils::getDBBase();
    
    sqlite3_stmt* stmt= SqlLite3Utils::getQueryStatementFromDBBase("select * from XXX", db);
    
    while (sqlite3_step(stmt)== SQLITE_ROW) {
        
        int id= sqlite3_column_int(stmt, 0);
        
    }
    
    SqlLite3Utils::closeDB(db);
    
    return true;
}
