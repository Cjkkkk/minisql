#include "./API.h"
#include "catalogManager.h"

catalog CM;
Buffer blocks;
IndexManager IM;
RecordManager RM;


void API::init(){
    CM.LoadIM_RM(IM,RM);
}

void API::save(){
    IM.SaveAllBpTree();
    RM.SaveAllRecordSet();
    if(CM.anychangeornot)CM.writeBacktoFile();
    else{
        std::cout<<"no change on table or index since last time"<<std::endl;
    }
    blocks.SaveDataAll();
}

void API::createTable(TableInfo *tableInfo){
    if(CM.existTable(tableInfo->tableName) != -1){
        std::cout<<"table "<<tableInfo->tableName<<" already exists\n"<<std::endl;
        return;
    }
    if(!CM.newTable(tableInfo)){
        std::cout <<"create table "<<tableInfo->tableName<<" fail"<<"------------------\n";
        return;
    }
    for(int i = 0 ; i < CM.tableNumber ; i++){
        if(CM.TableInfoList[i]->tableName == tableInfo->tableName){
            //找到这个表,找到它所有的索引信息
            std::map<int,std::string>::iterator it;
            it = tableInfo->indexInfo.begin();
            while(it != tableInfo->indexInfo.end())
            {
                //遍历索引信息,构建IndexInfo对象
                IndexInfo idi;
                //idi.indexID = it->first;
                idi.type = CM.TableInfoList[i]->type[it->first];
                idi.indexName = it->second;
                idi.tableName = tableInfo->tableName;
                IM.CreateIndexFile(idi);//删除indexfile
                it ++;         
            }

        }
    }
    RM.CreateRecordFile(*tableInfo);
    //CM.print();
};
void API::dropTable(TableInfo *tableInfo){
    std::cout<<"begin drop table"<<std::endl;
    for(int i = 0 ; i < CM.tableNumber ; i++){
        if(CM.TableInfoList[i]->tableName == tableInfo->tableName){
            //找到这个表,找到它所有的索引信息
            tableInfo = CM.TableInfoList[i];
            std::map<int,std::string>::iterator it;
            it = CM.TableInfoList[i]->indexInfo.begin();
            while(it != CM.TableInfoList[i]->indexInfo.end())
            {   
                //遍历索引信息,构建IndexInfo对象
                IndexInfo idi;
                idi.type = CM.TableInfoList[i]->type[it->first];
                idi.indexName = it->second;
                idi.tableName = tableInfo->tableName;
                IM.DropIndexFile(idi);//删除indexfile
                it ++;         
            }

        }
    }
    
    RM.DropRecordFile(*tableInfo);//删除recordfile
    if(!CM.dropTable(tableInfo->tableName))return;//删除catalog
    std::cout<<"after drop table"<<std::endl;
    //CM.print();
};
void API::createIndex(IndexInfo *indexInfo){
    std::cout <<"create index ------------------\n";
    // idi.type = CM.TableInfoList[i]->type[it->first];
    // idi.indexName = it->second;
    // idi.tableName = tableInfo->tableName;
    // IM.CreateIndexFile(idi);//删除indexfile
    if(!CM.createIndex(indexInfo))return;//建立catalog索引
    int pos = CM.existTable(indexInfo->tableName);
    
    auto it = CM.TableInfoList[pos]->getID.find(indexInfo->colunmName);
    indexInfo->type = CM.TableInfoList[pos]->type[it->second];
    IM.CreateIndexFile(*indexInfo);//建立indexfile

    //将之前插入table的值插入indexfile
    Addr p;
    struct value v;
    int result = RM.ReturnKP(*indexInfo,p,v);
    std::cout <<"end index ------------------\n";
};
void API::dropIndex(IndexInfo *indexInfo){
    for(int i = 0 ; i < CM.tableNumber ; i ++){
        std::map<int,std::string>::iterator it;
        it = CM.TableInfoList[i]->indexInfo.begin();
        while(it != CM.TableInfoList[i]->indexInfo.end())
        {
            //检查每个表上indexName是否被占用
            std::cout<<"index:"<<it->second<<std::endl;
            std::cout<<indexInfo->indexName<<it->second<<std::endl;
            if(indexInfo->indexName == it->second){
                indexInfo->tableName = CM.TableInfoList[i]->tableName;
                // indexInfo->colunmName = CM.TableInfoList[i]->attributeName[it->first];
                indexInfo->type = CM.TableInfoList[i]->type[it->first];
                IM.DropIndexFile(*indexInfo);
                CM.dropIndex(indexInfo->indexName,i);
                return;
            }
            it ++;
        }
    }
};


void API::showTable(){
    CM.showTable();
}

void API::descTable(std::string tableName){
    CM.descTable(tableName);
}
void API::insert_value(STMT *stmt){
    std::cout <<"insert value------------------\n";
    int pos = CM.existTable(stmt->tableName);
    if(!checkInsert(stmt,pos))return;
    //检查无误
    Addr p = {0,0};
    RM.InsertSuchRecord(*stmt,p);
    TableInfo* T = CM.TableInfoList[pos];
    std::map<int,std::string>::iterator it;
    it = T->indexInfo.begin();
    while(it != T->indexInfo.end())
    {
        //将每个索引插入b+树
        IndexInfo I;
        I.tableName = stmt->tableName;
        I.indexName = it->second;
        //插入B+树
        IM.InsertSuchKey(I,p,stmt->v_list->at(it->first));
        it ++;
    }
    printStatement(stmt);
}
// bool API::update_Value(STMT *stmt){};
void API::delete_Value(STMT *stmt){
    std::cout <<"delete value------------------\n";
    int pos = CM.existTable(stmt->tableName);
    if(!checkDelete(stmt,pos))return;
    TableInfo* T = CM.TableInfoList[pos];
    if(!add_ColID_Index(stmt,T))return;//增加colunmID 和 isindex
    //开始delete
    std::set<Addr> S;
    if(T->indexInfo.size() == 0){
        S = RM.FindandDelete(*stmt);
    }else{
        S = RM.FindandDelete(*stmt,S);
//        std::map<int,std::string>::iterator it;
//        it = T->indexInfo.begin();
//        while(it != T->indexInfo.end())
//        {
//            //将每个索引插入b+树
//            Addr p ={0,0};
//            IndexInfo I;
//            I.tableName = stmt->tableName;
//            I.indexName = it->second;
//            //插入B+树
//            IM.InsertSuchKey(I,p,stmt->v_list->at(it->first));
//            it ++;
//        }
    }
    printStatement(stmt);
    return;
};
bool API::add_ColID_Index(STMT* stmt,TableInfo* T){
    for(int i = 0 ; i < stmt->c_list->size();i++){
        auto it = T->getID.find(stmt->c_list->at(i).colunmName);
        //增加colunmID
        if(it == T->getID.end()){
            cout<<"select fail can not find colunm "<< stmt->c_list->at(i).colunmName<<std::endl;
            return false;
        }
        int colID = it->second;
        stmt->c_list->at(i).colunmID = colID;
        //查看是否是index
        auto I_iter = T->indexInfo.find(colID);
        if(I_iter != T->indexInfo.end()){
            //是index
            stmt->c_list->at(i).isIndex = true;
        }else stmt->c_list->at(i).isIndex = false;
    }
    return true;
}

void API::select_value(STMT *stmt){
    std::cout <<"select value------------------\n";
    int pos = CM.existTable(stmt->tableName);
    if(!checkSelect(stmt,pos))return;
    TableInfo* T = CM.TableInfoList[pos];
    if(!add_ColID_Index(stmt,T))return;
    //开始select
    printStatement(stmt);
};

void API::printStatement(STMT* stmt){
    for(int i = 0 ; i<stmt->colunmList->size();i++){
        std::cout<<stmt->colunmList->at(i)<<std::endl;
    }
    std::cout<<"constraint=-----------"<<std::endl;
    for(int i = 0 ;i < stmt->c_list->size() ; i++){
        if(stmt->c_list->at(i).type == 50000)std::cout << stmt->c_list->at(i).colunmName<< stmt->c_list->at(i).key.intV << stmt->c_list->at(i).op<<std::endl;
        else if(stmt->c_list->at(i).type == 90000)std::cout << stmt->c_list->at(i).colunmName<<stmt->c_list->at(i).key.floatV << stmt->c_list->at(i).op<<std::endl;
        else std::cout << stmt->c_list->at(i).colunmName<<stmt->c_list->at(i).key.charV <<stmt->c_list->at(i).op << std::endl;
    };
}

bool API::checkInsert(STMT *stmt,int pos){
    if(pos < 0){
        std::cout<<"insert fail,table "<<stmt->tableName<<" does not exist"<<std::endl;
        return false;
    }
    //检查数据列数目 和数据类型
    TableInfo* info = CM.TableInfoList[pos];
    if(stmt->v_list->size() != info->attributeNum){
        //数目不匹配
        std::cout<<"some colunm missing"<<std::endl;
        std::cout <<"insert statement has "<<stmt->v_list->size()<<" ,but table "<<stmt->tableName<<" require "<<info->attributeNum<<std::endl; 
        return false;
    }
    //检查数据类型
    bool error = false;
    for(int i = 0 ; i <stmt->v_list->size() ; i++){
        int insertType = stmt->v_list->at(i).type;
        int checkType = info->type[i];
        if(insertType != checkType ){
            if(checkType > 120000 && insertType > 120000 && insertType <= checkType)continue;
            std::cout<<info->attributeName[i]<<" type does not match"<< std::endl;
            std::cout << "insert type is "<<insertType<<" while check type is "<<checkType<<std::endl;
            error = true;
        }
    }
    if(error){
        std::cout<<"error occured"<<std::endl;
        return false;
    }
    return true;
}


bool API::checkDelete(STMT* stmt,int pos){
    if(pos < 0){
        std::cout<<"delete fail,table "<<stmt->tableName<<" does not exist"<<std::endl;
        return false;
    }
    TableInfo* info = CM.TableInfoList[pos];
    //增加id 增加类型检查
    bool error = false;
    for(int i = 0 ; i < stmt->c_list->size() ; i ++){
        //先检查类型
        int insertType = stmt->c_list->at(i).type;
        int checkType = info->type[i];
        if(insertType != checkType ){
            if(checkType > 120000 && insertType > 120000 && insertType <= checkType)continue;
            std::cout<<info->attributeName[i]<<" type does not match"<< std::endl;
            std::cout << "insert type is "<<insertType<<" while check type is "<<checkType<<std::endl;
            error = true;
        }
        if(error){
            std::cout<<"error occured"<<std::endl;
            return false;
        }
        //增加colunmid
        auto it = info->getID.find(stmt->c_list->at(i).colunmName);
        if(it==info->getID.end()){
            cout<<" not found 2"<<endl;
            std::cout<<"colunm "<< stmt->c_list->at(i).colunmName << "does not exist"<<std::endl;
            return false;
        }
        else{
            std::cout<<"id："<< it->second <<std::endl;
            stmt->c_list->at(i).colunmID = it->second;
        }
    }
    std::cout<<"id loaded"<<std::endl;
    return true;
}

bool API::checkSelect(STMT* stmt,int pos){
    if(pos < 0){
        std::cout<<"select fail,table "<<stmt->tableName<<" does not exist"<<std::endl;
        return false;
    }
    TableInfo* info = CM.TableInfoList[pos];
    //增加c_list id 增加类型检查
    bool error = false;
    for(int i = 0 ; i < stmt->c_list->size() ; i ++){
        //先检查c_list类型
        int insertType = stmt->c_list->at(i).type;
        int checkType = info->type[i];
        if(insertType != checkType ){
            if(checkType > 120000 && insertType > 120000 && insertType <= checkType)continue;
            std::cout<<info->attributeName[i]<<" type does not match"<< std::endl;
            std::cout << "insert type is "<<insertType<<" while check type is "<<checkType<<std::endl;
            error = true;
        }
        if(error){
            std::cout<<"error occured"<<std::endl;
            return false;
        }
        //增加colunmid
        auto it = info->getID.find(stmt->c_list->at(i).colunmName);
        if(it==info->getID.end()){
            std::cout<<"colunm "<< stmt->c_list->at(i).colunmName << "does not exist"<<std::endl;
            return false;
        }
        else{
            std::cout<<"id："<< it->second <<std::endl;
            stmt->c_list->at(i).colunmID = it->second;
        }
    }

    //增加colunmID
    //检查是不是selectall
    if(stmt->is_select_all){
        //do nothing
        //不需要加colunmlistID
    }else{
        for(int i = 0 ; i < stmt->colunmList->size() ; i ++){
            //增加colunmid
            auto it = info->getID.find(stmt->colunmList->at(i));
            if(it==info->getID.end()){
                std::cout<<"can not select colunm "<< stmt->colunmList->at(i) << ",it does not exist"<<std::endl;
                return false;
            }
            else{
                std::cout<<"id："<< it->second <<std::endl;
                stmt->colunmId->push_back(it->second);
            }
        }
        //
        std::cout<< "show colunm id"<<std::endl;
        for(int i = 0 ; i < stmt->colunmList->size() ; i ++){
            std::cout<< stmt->colunmId->at(i)<<std::endl;
        }
        std::cout<< "end colunm id"<<std::endl;
        std::cout<<"id loaded"<<std::endl;
    }

    return true;
}