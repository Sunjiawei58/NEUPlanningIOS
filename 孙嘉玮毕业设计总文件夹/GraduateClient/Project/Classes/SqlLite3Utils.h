//
//  SqlLite3Utils.h
//  Project
//
//  Created by sunjiawei on 15/5/21.
//
//

#ifndef __Project__SqlLite3Utils__
#define __Project__SqlLite3Utils__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#include "sqlite3.h";
#include <string>

class SqlLite3Utils{

public:
    static sqlite3* getDBBase();
    
    static void closeDB(sqlite3 * db);
    
    static bool create_table(std::string sql, sqlite3* db);
    
    static bool insertDataIntoDBBase (std::string sql,sqlite3* db);
    
    static bool deleteDataFromDBBase (std::string sql,sqlite3* db);
    
    static bool updateDataFromDBBase (std::string sql,sqlite3* db);
    
    static sqlite3_stmt* getQueryStatementFromDBBase(std::string,sqlite3* db);
    
    static void closeStatement(sqlite3_stmt* );
    
    
    
    
    
    
};

#endif /* defined(__Project__SqlLite3Utils__) */
