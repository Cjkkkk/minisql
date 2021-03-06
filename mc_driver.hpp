#ifndef __MCDRIVER_HPP__
#define __MCDRIVER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>

#include "mc_scanner.hpp"
#include "mc_parser.tab.hh"
#include "./dataStructure.h"
#include <string>
#include <map>
namespace MC{

class MC_Driver{
public:
    MC_Driver();
    virtual ~MC_Driver();
   /** 
    * parse - parse from a file
    * @param filename - valid string with input file
    */
    void parse( const char *filename );
   /** 
    * parse - parse from a c++ input stream
    * @param is - std::istream&, valid input stream
    */
    void parse( std::istream &iss );
    void error(const std::string &message);
    void emit(const std::string &message);
    std::ostream& print(std::ostream &stream);

    void addIndexParam(std::string indexName, std::string tableName, std::string colunmName);
    bool addColunm(std::string colunmName,int attributype,int constraint);
    void addConstraint(std::string colunmname,int constraint);
    void addTableInfoTableName(std::string n){
        tableInfo->tableName = n;
    }


//---------------------------------------------
    //SQL CRUD
    void addValue(int value);
    void addValue(float value);
    void addValue(std::string value);
    void selectAll(){
        stmt->is_select_all = true;
    }
    void addTableName(std::string t){
        stmt->tableName = t;
    }
    //
    void addcolunm(int colunmnumber){
        // stmt->colunmList->push_back();
        // std::cout<<"-------"<<colunmName<<std::endl;
        for(int i = 0 ; i < colunmnumber ; i++){
            stmt->colunmList->push_back(condStack.colunm[i]);
            condStack.top--;
        }
    }
    //
    void Clear(int commandType);
    void pushCol(std::string colunmName){
        //std::cout<<"xx:"<<colunmName<<std::endl;
        condStack.colunm.push_back(colunmName);
        condStack.top++;
       // std::cout<<"colunm:"<<colunmName<<" "<<condStack.top<<std::endl;
    }
    void pushValue(std::string v){
        condStack.tempString = v;
        condStack.stackTopType = 120000 + v.size() - 2;
        std::cout<<"size is "<< condStack.stackTopType<<std::endl;
    }
    void pushValue(int v){
        condStack.tempInt = v;
        condStack.stackTopType = 50000;
    }
    void pushValue(float v){
        condStack.tempFloat = v;
        condStack.stackTopType = 90000;
    }

    void oppop(int op){
        std::string c = condStack.colunm[condStack.top-1];
        struct condition cl;
        cl.colunmName = c;
        cl.op = op;
        cl.type = condStack.stackTopType;
        cl.key.type = condStack.stackTopType;
        if(condStack.stackTopType == 50000){
            //int
            cl.key.intV = condStack.tempInt;
            stmt->c_list->push_back(cl);
            //std::cout<<cl.key.type<<" "<<cl.key.intV<<std::endl;
        }else if(condStack.stackTopType == 90000){
            //float
            cl.key.floatV = condStack.tempFloat;
            stmt->c_list->push_back(cl);
            //std::cout<<cl.key.type<<" "<<cl.key.floatV<<std::endl;
        }else{
            //string
            cl.key.charV = condStack.tempString;
            stmt->c_list->push_back(cl);
            //std::cout<<cl.key.type<<" "<<cl.key.charV<<std::endl;
        }
        
    }


    IndexInfo *indexInfo;
    TableInfo *tableInfo;
    STMT *stmt;
    int number = 0;
    //处理逆波兰的堆栈
    struct ConditionStack condStack;
private:

    void parse_helper( std::istream &stream );
    MC::MC_Parser  *parser  = nullptr;
    MC::MC_Scanner *scanner = nullptr;
   
//    /** define some pretty colors **/
//     const std::string red   = "\033[1;31m";
//     const std::string blue  = "\033[1;36m";
//     const std::string norm  = "\033[0m";
   
};

} /* end namespace MC */
#endif /* END __MCDRIVER_HPP__ */