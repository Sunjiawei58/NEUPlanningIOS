//
//  NeuMap.cpp
//  Project
//
//  Created by sunjiawei on 15/5/14.
//
//

#include "NeuMap.h"
#include "stdio.h"
#include <iostream>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StudyLayer.h"
#include "MyInfoLayer.h"
#include "JiaoXueLayer.h"
#include "SportsLayer.h"
#include "ErSheGymLayer.h"
#include "LibraryLayer.h"
#include "CaiKuangLayer.h"
#include "FriendLayer.h"
#include "MessageLayer.h"
USING_NS_CC;
//using namespace std;
using namespace cocostudio::timeline;
#define MAPTILESIZE 32
enum MENUENUM
{
    TOPMENUITEM=100,BUTTOMMENUITEM,LEFTMENUITEM,RIGHTMENUITEM,FILEMENUITEM,STUDYMENUITEM,SPORTMENUITEM,INFOMENUITEM,FRIENDMENUITEM,MESSAGEMENUITEM
};

Scene* NeuMap::createScene()
{
    auto s = Scene::create();
    
    auto layer= NeuMap::create();
    
    s->addChild(layer);
    
    
    
    return s;
}
bool NeuMap::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visiblesize= Director::getInstance()->getVisibleSize();
    
    
    map=TMXTiledMap::create("NEUmap.tmx");
    addChild(map,0,1);
    
    //map->setNormalizedPosition(Point(0.5,0.5));
    map->setAnchorPoint(Point(0,0));
    //map->setPosition(Point(-1280,0));   //-1280,800可以居中。移动视角是通过移动像素的单位来实现的，此处让地图居中显示
    
    
    Player=Sprite::create("player.jpg");
    Player->setAnchorPoint(Point(0,0));
    Player->setPosition(Point(0,0));   //左下角开始
    map->addChild(Player);
    
    auto actionBy=ScaleBy::create(2.0f, 1.5f,1.5f);
    Player->runAction(Sequence::create(actionBy,actionBy->reverse(), NULL));
    
    
    MenuItemImage * pTopItem = MenuItemImage::create("top.png", "top_press.png", this,menu_selector(NeuMap::menuCallback));
    
    MenuItemImage * pRightItem = MenuItemImage::create("right.png", "right_press.png", this,menu_selector(NeuMap::menuCallback));
    
    
    MenuItemImage * pLeftItem = MenuItemImage::create("left.png", "left_press.png", this,menu_selector(NeuMap::menuCallback));
    
    MenuItemImage * pButtomItem = MenuItemImage::create("buttom.png", "buttom_press.png", this,menu_selector(NeuMap::menuCallback));
    MenuItemImage * pFireItem = MenuItemImage::create("fire.png","fire_press.png",this,menu_selector(NeuMap::menuCallback));
    Menu* pMenu=Menu::create(pTopItem,pRightItem,pLeftItem,pButtomItem,pFireItem,NULL);
    pMenu->setPosition(Point(0,0));
    
    MenuItemFont * fStudy = MenuItemFont::create("Study", this, menu_selector(NeuMap::menuCallback));
    MenuItemFont * fSports = MenuItemFont::create("Sports", this, menu_selector(NeuMap::menuCallback));
    MenuItemFont * fMyInfo = MenuItemFont::create("我的信息", this, menu_selector(NeuMap::menuCallback));
    MenuItemFont * fFriend = MenuItemFont::create("好友",this,menu_selector(NeuMap::menuCallback));
    MenuItemFont * fMessage = MenuItemFont::create("消息",this,menu_selector(NeuMap::menuCallback));
    Menu* fMenu=Menu::create(fStudy,fSports,fMyInfo,fFriend,fMessage, NULL);
    fMenu->setPosition(Point(0,0));
    this->addChild(pMenu);
    this->addChild(fMenu);
    
    pTopItem->setPosition(Point(visiblesize.width/2,visiblesize.height-50));
    pButtomItem->setPosition(Point(visiblesize.width/2,50));
    pLeftItem->setPosition(Point(50,visiblesize.height/2));
    pRightItem->setPosition(Point(visiblesize.width-50,visiblesize.height/2));
    pFireItem->setPosition(Point(50,visiblesize.height-50));
    
    fStudy->setPosition(Point(visiblesize.width/2-100,visiblesize.height-30));
    fSports->setPosition(Point(visiblesize.width/2+100,visiblesize.height-30));
    fMyInfo->setPosition(Point(visiblesize.width-80,visiblesize.height-30));
    fFriend->setPosition(Point(50,visiblesize.height-130));
    fMessage->setPosition(Point(50,visiblesize.height-180));
    //之后需要设置tag处理不同的触碰事件
    pTopItem->setTag(TOPMENUITEM);
    pButtomItem->setTag(BUTTOMMENUITEM);
    pLeftItem->setTag(LEFTMENUITEM);
    pRightItem->setTag(RIGHTMENUITEM);
    pFireItem->setTag(FILEMENUITEM);
    
    fStudy->setTag(STUDYMENUITEM);
    fSports->setTag(SPORTMENUITEM);
    fMyInfo->setTag(INFOMENUITEM);
    fFriend->setTag(FRIENDMENUITEM);
    fMessage->setTag(MESSAGEMENUITEM);
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    EventListenerTouchOneByOne* listener= EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    //listener->onTouchEnded = CC_CALLBACK_2(NeuMap::onTouchEnded,this);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){std::cout<<"touch began...";return true;};
    listener->onTouchMoved = [](Touch* touch, Event* event){std::cout<<"touch moved...";};
    listener->onTouchEnded = [](Touch* touch, Event* event){std::cout<<"touch ended...";};
    listener->onTouchCancelled = [](Touch* touch , Event* event){};
    /*
    listener->onTouchBegan= CC_CALLBACK_2(NeuMap::touchBegan, this);
    listener->onTouchMoved=CC_CALLBACK_2(NeuMap::touchMoved, this);
    
    listener->onTouchEnded = CC_CALLBACK_2(NeuMap::touchEnded, this);
    listener->onTouchCancelled=CC_CALLBACK_2(NeuMap::touchCancelled, this);
     */   // 这个写法会报错
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener,map);
    return true;
    
}

void NeuMap::menuCallback(cocos2d::Ref *psender)
{
    
    
    Size visiblesize= Director::getInstance()->getVisibleSize();
    MenuItemImage* item =(MenuItemImage*)psender;
    buildings = map->getLayer("buildings");
    _events = map->getLayer("events");
    int GID=0;
    int eventGID=0;
    bool happend=false;
    Point playerCur=Point((int)Player->getPositionX()/MAPTILESIZE,map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE));
    
//    std::cout<<"tiled map size is "<<map->getTileSize().width<<"*"<<map->getTileSize().height<<std::endl;
    Point playerNext=playerCur;
    
    switch (item->getTag()) {
        case TOPMENUITEM:
                        //map的锚点在0,0。如果player坐标没有超过屏幕，则移动player，反之则移动地图。
            
            playerNext.y-=1;
            if(playerNext.y<1)return;      // 临界判断
            GID = buildings->getTileGIDAt(playerNext);
            eventGID = _events->getTileGIDAt(playerNext);
            std::cout<<"gid is"<<GID<<std::endl;
            //if(GID!=30&&GID!=14&&GID!=40) return;
            //if(!NeuMap::isPass(GID)) return;
            if(eventGID)
            {
                happend = true;
            }
            if(GID) return;    //碰撞检测
            
            
            
            
            /*if(Player->getPositionY()+map->getPositionY()<visiblesize.height/2-MAPTILESIZE)
            {
                Player->setPosition(Point(Player->getPositionX(),Player->getPositionY()+MAPTILESIZE));
            }
            else map->setPosition(Point(map->getPositionX(),map->getPositionY()-MAPTILESIZE));*/
            
            if(map->getContentSize().height+map->getPositionY()>visiblesize.height+MAPTILESIZE)
            {
                if(Player->getPositionY()+map->getPositionY()>visiblesize.height/2)
                {
                    map->setPosition(Point(map->getPositionX(),map->getPositionY()-MAPTILESIZE));
                    std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
                }
                Player->setPosition(Point(Player->getPositionX(),Player->getPositionY()+MAPTILESIZE));
                std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
            }
            else if(Player->getPositionY()<map->getContentSize().height-MAPTILESIZE)
            {
                Player->setPosition(Point(Player->getPositionX(),Player->getPositionY()+MAPTILESIZE));
                std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;            }
            
            
            break;
        case BUTTOMMENUITEM:
            /*if(map->getPositionY()<0)
            {
                if(visiblesize.height/2-map->getPositionY()>Player->getPositionY())
                {
                    map->setPosition(Point(map->getPositionX(),map->getPositionY()+32));
                }
                Player->setPosition(Point(Player->getPositionX(),Player->getPositionY()-32));
            }
            else  if(Player->getPositionY()>32)
            {
                Player->setPosition(Point(Player->getPositionX(),Player->getPositionY()-32));
            }*/
            playerNext.y+=1;
            if((playerNext.y)>map->getMapSize().height-1) return;
            GID = buildings->getTileGIDAt(playerNext);
            eventGID = _events->getTileGIDAt(playerNext);
            std::cout<<"gid is"<<GID<<std::endl;
            //if(!NeuMap::isPass(GID)) return;
            if(eventGID)
            {
                happend = true;
            }

            if(GID) return;
            /*if(Player->getPositionY()+map->getPositionY()/2> MAPTILESIZE )
            {
                Player->setPosition(Point(Player->getPositionX(),Player->getPositionY()-MAPTILESIZE));
            }
            else map->setPosition(Point(map->getPositionX(),map->getPositionY()+MAPTILESIZE));*/
            
            if(map->getPositionY()<0)
            {
                if(Player->getPositionY()+map->getPositionY()<visiblesize.height/2)
                {
                    map->setPosition(Point(map->getPositionX(),map->getPositionY()+MAPTILESIZE));
                    std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
                }
                Player->setPosition(Point(Player->getPositionX(),Player->getPositionY()-MAPTILESIZE));
                    std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
            }
            else if(Player->getPositionY()>MAPTILESIZE)
            {
                Player->setPosition(Point(Player->getPositionX(),Player->getPositionY()-MAPTILESIZE));
                std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
            }

            break;
        case LEFTMENUITEM:
            playerNext.x-=1;
            if(playerNext.x<1) return;
            GID = buildings->getTileGIDAt(playerNext);
            eventGID = _events->getTileGIDAt(playerNext);
            std::cout<<"gid is"<<GID<<std::endl;
            //if(!NeuMap::isPass(GID)) return;
            if(eventGID)
            {
                happend = true;
            }

            if(GID) return;
           /* if(map->getPositionX()<0)
            {
                if(visiblesize.width/2-map->getPositionX()>Player->getPositionX())
                {
                    map->setPosition(Point(map->getPositionX()+32,map->getPositionY()));
                }
                Player->setPosition(Point(Player->getPositionX()-32,Player->getPositionY()));
            }
            else  if(Player->getPositionX()>32)
            {
                Player->setPosition(Point(Player->getPositionX()-32,Player->getPositionY()));
            }*/
        
            if(map->getPositionX()< 0 )
            {
                if(Player->getPositionX()+map->getPositionX()<visiblesize.width/2)
                {
                    map->setPosition(Point(map->getPositionX()+MAPTILESIZE,map->getPositionY()));
                    std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
                }
                Player->setPosition(Point(Player->getPositionX()-MAPTILESIZE,Player->getPositionY()));
                std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
            }
            else if(Player->getPositionX()>MAPTILESIZE)
            {
                Player->setPosition(Point(Player->getPositionX()-MAPTILESIZE,Player->getPositionY()));
                std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
            }
            break;
        case RIGHTMENUITEM:
        
        
            playerNext.x+=1;
            if(playerNext.x>map->getMapSize().width-1) return;
            GID = buildings->getTileGIDAt(playerNext);
            eventGID = _events->getTileGIDAt(playerNext);
            std::cout<<"gid is"<<GID<<std::endl;
            //if(!NeuMap::isPass(GID)) return;
            if(eventGID)
            {
                happend = true;
            }

            if(GID) return;
           /* if(map->getContentSize().width+map->getPositionX()-32>visiblesize.width)
            {

                if(visiblesize.width/2-map->getPositionX()<map->getPositionX())
                {
                    map->setPosition(Point(map->getPositionX()-32,map->getPositionY()));
                }
                Player->setPosition(Point(Player->getPositionX()+32,Player->getPositionY()));
            }
            else if(Player->getPositionX()<map->getContentSize().width-2*32)
            {
                Player->setPosition(Point(Player->getPositionX()+32,Player->getPositionY()));
            }
        */
            
            if(map->getContentSize().width+map->getPositionX()>visiblesize.width+MAPTILESIZE)
            {
                if(Player->getPositionX()+map->getPositionX()>visiblesize.width/2)
                {
                    map->setPosition(Point(map->getPositionX()-MAPTILESIZE,map->getPositionY()));
                    std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
                }
                Player->setPosition(Point(Player->getPositionX()+MAPTILESIZE,Player->getPositionY()));
                std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
            }
            else if(Player->getPositionX()<map->getContentSize().width-MAPTILESIZE)
            {
                Player->setPosition(Point(Player->getPositionX()+MAPTILESIZE,Player->getPositionY()));
                std::cout<<"the player position is "<<(int)Player->getPositionX()/MAPTILESIZE<<","<<map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE)<<std::endl;
            }

            
            break;
        case STUDYMENUITEM:
           
            studyEvents();
            break;
        case SPORTMENUITEM:
            sportsEvents();
            break;
        case FILEMENUITEM:
            std::cout<<"the Event is happend..."<<std::endl;
            mainEvents();
            break;
        case INFOMENUITEM:
            
            std::cout<<"My info show..."<<std::endl;
            infoEvents();
            
            break;
        case FRIENDMENUITEM:
            
            std::cout<<"friend show"<<std::endl;
            friendEvents();
            break;
        case MESSAGEMENUITEM:
            messageEvents();
            std::cout<<"message show"<<std::endl;
            break;
        default:
            break;
        
    
            //处理主角移动的视角函数
    }

}
void NeuMap::mainEvents()
{
    auto actionBy=ScaleBy::create(2.0f, 1.5f,1.5f);
    Player->runAction(Sequence::create(actionBy,actionBy->reverse(), NULL));
    
    Point playerCur=Point((int)Player->getPositionX()/MAPTILESIZE,map->getMapSize().height-1-(int)(Player->getPositionY()/MAPTILESIZE));  // 先获得当前位置的坐标。再根据坐标去判断触发哪个事件
    if(playerCur==Point(36,35))
    {
        std::cout<<"调用教学管的Layer"<<std::endl;
        JiaoxueEvents();
    }
    else if(playerCur==Point(47,35))
    {
        std::cout<<"调用篮球场的Layer"<<std::endl;
        ErSheGymEvents();
    }
    else if(playerCur==Point(36,29))
    {
        std::cout<<"调用采矿馆的Layer"<<std::endl;
        CaiKuangEvents();
    }
    else if(playerCur==Point(47,30))
    {
        std::cout<<"调用图书馆的Layer"<<std::endl;
        LibraryEvents();
    }
    
}
/*int NeuMap::isPass(int GID)
{
    if(GID==0||GID==1||GID==2||GID==8||GID==9||GID==10||GID==16||GID==17||GID==18||GID==19||GID==20||GID==27||GID==28||GID==45||GID==33)
    {
        return 0;
    }
    else return 1;
}*/

void NeuMap::infoEvents()
{
    Layer * infoLayer=MyInfoLayer::create();
    this->addChild(infoLayer,1);
    
}
void NeuMap::sportsEvents()
{
    Layer* spoLayer = SportsLayer::create();
    this->addChild(spoLayer);
}
void NeuMap::studyEvents()
{
    Layer* stuLayer=StudyLayer::create();
    this->addChild(stuLayer);
}
void NeuMap::JiaoxueEvents()
{
    Layer * jiaoXueLayer =JiaoXueLayer::create();
    this->addChild(jiaoXueLayer);
}
    

void NeuMap::ErSheGymEvents()
{
    Layer* erSheGymLayer=ErSheGymLayer::create();
    this->addChild(erSheGymLayer);
}
void NeuMap::LibraryEvents()
{
    Layer* libraryLayer = LibraryLayer::create();
    this->addChild(libraryLayer);
}
void NeuMap::CaiKuangEvents()
{
    Layer* caiKuangLayer = CaiKuangLayer::create();
    this->addChild(caiKuangLayer);
    
}
void NeuMap::friendEvents()
{
    Layer* friendLayer = FriendLayer::create();
    this->addChild(friendLayer);
}
void NeuMap::messageEvents()
{
    Layer* messageLayer = MessageLayer::create();
    this->addChild(messageLayer);
}