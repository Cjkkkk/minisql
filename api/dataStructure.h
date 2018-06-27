#ifndef __DATASTRUTURE_HPP__
#define __DATASTRUTURE_HPP__ 1
#include <iostream>
#include <vector>
#include <map>
 
struct value {
	int type;
	std::string charV;
	int intV;
	float floatV;
};

struct condition{
    int colunmID;
    std::string colunmName;
    bool isIndex;
    int type;			//datatype
    int op;				//== >= > <= < <>
	struct value key;
};

//暂时保存堆栈内的值
struct ConditionStack{
    std::string conditioncolunm;
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
    std::vector<std::string> attributeName;	//列名
    std::vector<int> type;
    std::vector<int> constraint;
    std::map<int,std::string> indexInfo;//<列序号,索引名字>
    int primary_key_id;
};

class STMT{
public:
    char type;					//operation type, 's','d','i'
    std::string tableName;
    std::vector<std::string> *colunmList;		//select用
    std::vector<int> *colunmId;					//select用
    std::vector<struct value> *v_list;			//insert用
    std::vector<struct condition> *c_list;		//select和delete用
};

#endif