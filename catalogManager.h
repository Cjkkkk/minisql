#ifndef __CATALOG_HPP__
#define __CATALOG_HPP__ 1

#include "./dataStructure.h"
#include "./RecordManager.h"
#include "./IndexManager.h"
#include "./Buffer.h"
#include <fstream>
class catalog{
public:
    catalog();
    ~catalog() = default;
    void print();
    bool newTable(TableInfo* tableInfo);
    void addInfoToList(TableInfo *tableInfo);
    int existTable(std::string tableName);
    bool dropTable(std::string tableName);
    void writeTabletoFile(TableInfo* tableInfo,std::ofstream& tablelist);
    void writeBacktoFile();
    bool createIndex(IndexInfo *indexinfo);
    void dropIndex(std::string indexName,int tableID);
    void LoadIM_RM(IndexManager& IM,RecordManager& RM);
    void showTable();
    void descTable(std::string tableName);
    bool anychangeornot;
    int tableNumber;
    std::vector<TableInfo*> TableInfoList;
    std::vector<size_t> file_offset;
};

#endif /* END __MCDRIVER_HPP__ */