#ifndef __DATASTRUTURE_HPP__
#define __DATASTRUTURE_HPP__ 1
#include <iostream>
#include <vector>
#include <map>
struct value{
    int type;
    std::string charV;
    int intV;
    float floatV;
};

struct condition{
    int colunmID;
    std::string colunmName;
    bool isIndex;
    int type;
    int op;
    struct value key;
};


//暂时保存堆栈内的值
struct ConditionStack{
    int top = 0;
    std::vector<std::string> colunm;
    int tempInt;
    float tempFloat;
    std::string tempString;
    int stackTopType;
};
//-----------------------------------------------------
 
class IndexInfo{
public:
    IndexInfo() = default;
    ~IndexInfo() = default;
    int indexID;
    int type;
    std::string indexName;
    std::string tableName;
    std::string colunmName;
};

class TableInfo{
public:
    TableInfo(){
        tableName = "";
        attributeNum = 0;
        primary_key_id = -1;
    }
    std::string tableName;
    int attributeNum;
    std::vector<std::string> attributeName;
    std::vector<int> type;
    std::vector<int> constraint;
    std::map<std::string,int> getID;
    std::map<int,std::string> indexInfo;//<列序号,index名字>
    int primary_key_id;
};

class STMT{
public:
    // char type;
    bool is_select_all = false;
    std::string tableName;
    std::vector<std::string> *colunmList;
    std::vector<int> *colunmId;//select
    std::vector<struct value> *v_list;//insert
    std::vector<struct condition> *c_list;//select delete
};

#endif