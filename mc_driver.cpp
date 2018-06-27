#include <cctype>
#include <fstream>
#include <cassert>
#include "mc_driver.hpp"
#include "API.h"
// #include "catalogManager.h"
// extern catalog c;
MC::MC_Driver::MC_Driver(){
    indexInfo = new IndexInfo();
    tableInfo = new TableInfo();
    stmt = new STMT();
    stmt->colunmList = new std::vector<std::string>();
    stmt->colunmId = new std::vector<int>();
    stmt->v_list = new std::vector<struct value>();
    stmt->c_list = new std::vector<struct condition>();
    struct ConditionStack s;
    condStack = s;
}
MC::MC_Driver::~MC_Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void 
MC::MC_Driver::parse( const char * const filename )
{
   /**
    * Remember, if you want to have checks in release mode
    * then this needs to be an if statement 
    */
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() )
   {
       exit( EXIT_FAILURE );
   }
   parse_helper( in_file );
   return;
}

void
MC::MC_Driver::parse( std::istream &stream )
{
   if( ! stream.good()  && stream.eof() )
   {
       return;
   }
   //else
   parse_helper( stream ); 
   return;
}


void 
MC::MC_Driver::parse_helper( std::istream &stream )
{
   
   delete(scanner);
   try
   {
      scanner = new MC::MC_Scanner( &stream );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" << ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   
   delete(parser); 
   try
   {
      parser = new MC::MC_Parser( (*scanner) /* scanner */, (*this) /* driver */ );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" << ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   const int accept( 0 );
   if( parser->parse() != accept)
   {
      std::cerr << "Parse failed!!\n";
       API::save();
   }
   return;
}


void
MC::MC_Driver::error(const std::string &message){
    std::cout << "ERROR: "<< message << std::endl;
}

void 
MC::MC_Driver::emit(const std::string &message){
    std::cout << "rpn "<< message << std::endl;
}

void MC::MC_Driver::addIndexParam(std::string indexName, std::string tableName, std::string colunmName){
    indexInfo->indexName = indexName;
    indexInfo->tableName = tableName;
    indexInfo->colunmName = colunmName;
}


//清理table

    // void createTable(MC::TableInfo *tableInfo){
    // bool dropTable();
    // void createIndex(MC::IndexInfo *indexInfo)
    // bool dropIndex();
    // bool insert_value(MC::InsertSTMT *insertStmt)
    // bool update_Value();
    // bool delete_Value();
    // bool select_value();
void MC::MC_Driver::Clear(int commandType){
    switch (commandType){
        case 0:
            std::cout<<"clear create table statement"<<std::endl;
            tableInfo = new TableInfo();
            break;
        case 1:
        //droptable
            std::cout<<"clear drop table statement"<<std::endl;
            tableInfo = new TableInfo();
            break;
        case 2:
            //createIndex
            std::cout<<"clear create index statement"<<std::endl;
            indexInfo->indexID = -1;
            indexInfo->type = 0;
            indexInfo->indexName = "";
            indexInfo->tableName = "";
            indexInfo->colunmName = "";
            break;
        case 3:
        //insert_value
            std::cout<<"clear insert statement"<<std::endl;
            condStack.top = 0;
            condStack.colunm.clear();
            stmt->v_list->clear();
            stmt->tableName = "";
            break;
        case 4:
        //select value
            std::cout<<"clear select statement"<<std::endl;
            condStack.top = 0;
            condStack.colunm.clear();
            stmt->is_select_all = false;
            stmt->c_list->clear();
            stmt->tableName = "";
            stmt->colunmList->clear();
            stmt->colunmId->clear();
            break;
        case 5:
            std::cout <<"clear delete statement"<<std::endl;
            condStack.top = 0;
            condStack.colunm.clear();
            stmt->c_list->clear();
            stmt->tableName = "";
            break;
        case 6:
            //dropIndex
            indexInfo->indexID = -1;
            indexInfo->type = 0;
            indexInfo->indexName = "";
            indexInfo->tableName = "";
            indexInfo->colunmName = "";
            break;
    }
    
}
//建表添加属性
void MC::MC_Driver::addColunm(std::string colunmName,int attributype,int constraint){
    //是否超过最大属性数目
    if(tableInfo->attributeNum == 32){
        std::cout<<"exceed maximum number of attribute\n";
    }
    //是否重名
    for(int i = 0 ; i < tableInfo->attributeNum ; i++){
        if(tableInfo->attributeName[i] == colunmName){//已经存在这个属性
            std::cout << "attribute name "<< colunmName <<" occupied\n";
            return;
        }
    }
    
    //检查类型是否没有错误
    if(attributype == 50000 || attributype == 90000 || attributype > 120000){
        //检查属性限制是否错误
        //0代表没有限制 1代表not null 2代表unique 3代表primary key
        if(constraint == 0 || constraint == 1 || constraint == 2 || constraint == 3){
            //类型和限制都没有错误
            tableInfo->attributeName.push_back(colunmName);
            tableInfo->type.push_back(attributype);
            tableInfo->constraint.push_back(constraint);
            std::pair<std::string,int> p = std::make_pair(colunmName,tableInfo->attributeNum);
            tableInfo->getID.insert(p);
            //如果是primary key需要加上它建立在的列的id
            if(constraint == 3){
                tableInfo->primary_key_id =  tableInfo->attributeNum;
                std::pair<int,std::string> p = std::make_pair(tableInfo->attributeNum, colunmName);
                tableInfo->indexInfo.insert(p);
            }

            tableInfo->attributeNum++;
        }
        else{
            std::cout << "attribute constraint of " <<colunmName<<" unrecognized\n";
            return;
        }
        //tableInfo->type_and_constraint.
    }else{
        //输入类型错误
        std::cout << "attributetype of " <<colunmName<<" unrecognized\n";
        return;
    }
}

//建表限制
//create table xx(a int,b int,@primary key(a)@);
void MC::MC_Driver::addConstraint(std::string colunmname,int constraint){
    if(constraint != 3 && constraint != 4){
        std::cout << "constraint type of colunm "<< colunmname <<" unrecognized\n";
        return;
    }
    for(int i = 0 ; i < tableInfo->attributeNum ; i++){
        if(tableInfo->attributeName[i] == colunmname){
            //属性存在
            tableInfo->constraint[i] = constraint;
            tableInfo->primary_key_id = i;//建立primary key
            std::pair<int,std::string> p = std::make_pair(i, colunmname);
            tableInfo->indexInfo.insert(p);
//            std::map<int,std::string>::iterator it;
//            it = tableInfo->indexInfo.begin();
//            std::cout<<it->first<<std::endl;
//            std::cout<<it->second<<std::endl;
//            while(it != tableInfo->indexInfo.end())
//            {
//                std::cout<<"22"<<it->first<<std::endl;
//                std::cout<<"33"<<it->second<<std::endl;
//            }
            return;
        }
    }
}


void MC::MC_Driver::addValue(int value){
    struct value val;
    val.intV = value;
    val.type = 50000;
    stmt->v_list->push_back(val);
}
void MC::MC_Driver::addValue(float value){
    struct value val;
    val.floatV = value;
    val.type = 90000;
    stmt->v_list->push_back(val);
}
void MC::MC_Driver::addValue(std::string value)
{
    struct value val;
    val.charV = value;
    //std::cout<<"sizeof "<<value <<" is "<<value.size()<<std::endl;
    val.type = 120000 + value.size() - 2;
    stmt->v_list->push_back(val);
}


