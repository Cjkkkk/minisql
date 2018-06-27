#ifndef __API_HPP__
#define __API_HPP__ 1

#include "./dataStructure.h"
#include "./catalogManager.h"
#include <iostream>

namespace API{
    void createTable(TableInfo *tableInfo);
    void dropTable(TableInfo *tableInfo);
    void createIndex(IndexInfo *indexInfo);
    void dropIndex(IndexInfo *indexInfo);
    void insert_value(STMT *stmt);
    //bool update_Value(STMT *stmt);
    void delete_Value(STMT *stmt);
    void select_value(STMT *stmt);
    void printStatement(STMT* stmt);
    bool checkInsert(STMT *stmt,int pos);
    bool checkDelete(STMT* stmt,int pos);
    bool checkSelect(STMT* stmt,int pos);
    bool add_ColID_Index(STMT* stmt,TableInfo* T);
    void init();
    void save();
    void showTable();
    void descTable(std::string tableName);
}

#endif