//
//  SqlLite3Utils.cpp
//  Project
//
//  Created by sunjiawei on 15/5/21.
//
//

#include "SqlLite3Utils.h"
#include "stdio.h"
#include <iostream>
using namespace std;

#define DB_NAME "graduate.db3"

sqlite3* SqlLite3Utils::getDBBase()
{
    
    sqlite3* database = nullptr;
    std::string db= FileUtils::getInstance()->getWritablePath()+DB_NAME;     // 获取可写的路径，这个很重要
    int ret= sqlite3_open(db.c_str(), &database);
    
    if (ret == SQLITE_OK) {
        log("打开数据库成功");
    }
    
    return database;
    
}

 void SqlLite3Utils::closeDB(sqlite3 * db)
{
    if(db!=nullptr)
    {
        sqlite3_close(db);
        db=nullptr;
    }
    
    
}
/**
 创建一个表
 **/
bool SqlLite3Utils::create_table(std::string sql, sqlite3* db)
{
    CCASSERT(db!=nullptr, "数据库指针为空，请检查问题");
    int ret = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if(ret == SQLITE_OK)
    {
        return true;
    }
    return false;
}
bool SqlLite3Utils::insertDataIntoDBBase (std::string sql,sqlite3* db)
{
    CCASSERT(db!=nullptr, "数据库指针为空，请检查问题");
    int ret = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if(ret == SQLITE_OK)
    {
        //std::cout<<"数据插入成功"<<endl;
        return true;
    }
    //else std::cout<<"插入失败"<<endl;
    return false;
}

bool SqlLite3Utils::deleteDataFromDBBase (std::string sql,sqlite3* db)
{
    CCASSERT(db!=nullptr, "数据库指针为空，请检查问题");
    int ret = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if(ret == SQLITE_OK)
    {
        return true;
    }
    return false;
}

bool SqlLite3Utils::updateDataFromDBBase (std::string sql,sqlite3* db)
{
    CCASSERT(db!=nullptr, "数据库指针为空，请检查问题");
    int ret = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    if(ret == SQLITE_OK)
    {
        return true;
    }
    return false;
}
/**
 根据传入的sql语句来去获取相应的查询结果集
 **/
sqlite3_stmt* SqlLite3Utils::getQueryStatementFromDBBase(std::string sql,sqlite3* db)
{
    CCASSERT(db!=nullptr, "数据库指针为空，请检查问题");
    sqlite3_stmt * stmt = nullptr;
    int ret = sqlite3_prepare_v2(db, sql.c_str(), (int)strlen(sql.c_str()), &stmt, nullptr);
    
    if(ret == SQLITE_OK)
    {
        log("获取结果集成功");
        
    }
    //CCASSERT(stmt!=nullptr, "结果集获取为空，请检查问题");
    return stmt;
    
}
/**
 
 释放查询结果集的指针
 
 **/
void SqlLite3Utils::closeStatement(sqlite3_stmt* stmt)
{
    if(stmt!=nullptr)
    {
        sqlite3_finalize(stmt);
        stmt=nullptr;
    }
}
