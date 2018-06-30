#include "./catalogManager.h"
#include "./dataStructure.h"
#include <fstream>
#include <string.h>
#include <unistd.h>



catalog::catalog(){
    tableNumber = 0;
    anychangeornot = false;
    std::ifstream tablelist("./file/catalog/table.dat", std::ios::in | std::ios::binary);
    std::ifstream IndexNamelist("./file/IndexNamelist.dat", std::ios::in | std::ios::binary);
    tablelist.seekg(0,std::ios::end); 
    // std::cout << tablelist.tellg() << std::endl;
    if(tablelist.tellg() == 0){
        return;//文件为空
    }
    else{
        tablelist.seekg(0,std::ios::beg);
        tablelist.read((char*)(&tableNumber),sizeof(int));
        std::cout<<tableNumber<<" tables in total"<<std::endl;
        int i = 0;
        while(i < tableNumber){
            //usleep(1*1000000);
            size_t pos = tablelist.tellg();
            //std::cout << "offset "<<pos<<std::endl;
            file_offset.push_back(pos);
            bool state;
            tablelist.read((char*)(&state),sizeof(bool));
            //std::cout<<state<<std::endl; 
            size_t len;
            tablelist.read((char*)(&len),sizeof(len));
            if(!state){
               std::cout<<"find deleted table"<<std::endl;
                tablelist.seekg(len,std::ios::cur);//跳过被删除的table
                std::cout<<tablelist.tellg()<<std::endl;//跳过被删除的table
                file_offset.pop_back();
                continue;
            }
            i++;
            TableInfo* tableInfo = new TableInfo();
            size_t size;
            //读入table的名字
            tablelist.read((char*)(&size),sizeof(size));
            char* buf = new char[size+1];
            tablelist.read(buf, size);
            buf[size] = '\0';
            tableInfo->tableName = buf;
            //读入colunm的数目
            tablelist.read((char*)(&(tableInfo->attributeNum)),sizeof(int));
            //读入列的信息
            for(int j = 0 ; j < tableInfo->attributeNum ; j ++){
                std::string attributeName;
                int type;
                int constraint;
                //
                tablelist.read((char*)(&size),sizeof(size));
                buf = new char[size+1];
                tablelist.read(buf, size);
                buf[size] = '\0';
                attributeName = buf;
                tablelist.read((char*)(&type),sizeof(int));
                tablelist.read((char*)(&constraint),sizeof(int));
                if(constraint == 4 || constraint == 3){
                    if(constraint == 3)tableInfo->primary_key_id = j;
                    //添加index信息
                    std::string indexName;
                    size_t len;
                    tablelist.read((char*)(&len),sizeof(len));
                    buf = new char[len+1];
                    tablelist.read(buf,len);
                    buf[size] = '\0';
                    indexName = buf;
                    std::pair<int,std::string> p = std::make_pair(j, indexName);
                    // tableInfo->indexInfo.push_back(p);
                    tableInfo->indexInfo.insert(p);  
                }
                tableInfo->type.push_back(type);
                tableInfo->attributeName.push_back(attributeName);
                tableInfo->constraint.push_back(constraint);
                std::pair<std::string,int> p = std::make_pair(attributeName,j);
                tableInfo->getID.insert(p); 
            }
            TableInfoList.push_back(tableInfo);//推入tablenfolist中
            std::cout<<"load table :"<<tableInfo->tableName<<std::endl;
        }
    }
    IndexNamelist.close();
    tablelist.close();
}

void catalog::LoadIM_RM(IndexManager& IM,RecordManager& RM){
    //load bptree record
    std::vector<IndexInfo> IndexList;
    for(int i = 0 ; i < tableNumber ; i ++){
        TableInfo* T = TableInfoList[i];
        auto it = T->indexInfo.begin();
        while(it!=T->indexInfo.end()){
            IndexInfo i;
            i.tableName = T->tableName;
            i.indexName = it->second;
            i.type = T->type[it->first];
            IndexList.push_back(i);
            it++;
        }
    }
    IM.LoadAllBpTree(IndexList);
    std::vector<TableInfo> TS;
    for(int i = 0 ; i < TableInfoList.size();i++){
        TS.push_back(*(TableInfoList[i]));
    }
    RM.LoadAllRecordSet(TS);
}

void catalog::writeTabletoFile(TableInfo* tableInfo,std::ofstream& tablelist){
    //从尾巴开始写
    tablelist.seekp(0,std::ios::end);
    file_offset.push_back(tablelist.tellp());
   // std::cout <<"i am at" <<tablelist.tellp() << std::endl;
    //写入当前状态
    bool state = true;//还未被删除
    //std::cout<<"write state here>> "<<tablelist.tellp()<<std::endl;
    tablelist.write(reinterpret_cast<char*>(&state), sizeof(bool));
    //写入table的长度
    size_t size = tableInfo->tableName.size();
    size_t len = size + sizeof(size);
    len += sizeof(int);//attributeNum的size
    for(int i = 0 ; i < tableInfo->attributeNum ; i++){
        size_t size = (tableInfo->attributeName)[i].size();
        len += size + sizeof(size);
        len += 2 * sizeof(int) ;//type和constraint的字节长度
    }
    // std::cout << len<<"--------s\n";
    //写入size
    tablelist.write(reinterpret_cast<char*>(&len), sizeof(len));
    //写入表格名字
    tablelist.write(reinterpret_cast<char*>(&size), sizeof(size));
    tablelist.write(tableInfo->tableName.c_str(), size);
    //写入列的数目
    tablelist.write(reinterpret_cast<char*>(&(tableInfo->attributeNum)), sizeof(int));
    //写入列名 类型 约束
    for(int i = 0 ; i < tableInfo->attributeNum ; i++){
        size = (tableInfo->attributeName)[i].size();
        tablelist.write(reinterpret_cast<char*>(&size), sizeof(size));
        tablelist.write((tableInfo->attributeName)[i].c_str(), size); 
        tablelist.write(reinterpret_cast<char*>(&((tableInfo->type)[i])), sizeof(int));
        tablelist.write(reinterpret_cast<char*>(&((tableInfo->constraint)[i])), sizeof(int));
        //int indexoffset = -1;//默认没有indexName 所以设置它在文件中的偏移-1
        if((tableInfo->constraint)[i] == 4 ){
            std::map<int, std::string>::iterator iter;  
            iter = tableInfo->indexInfo.find(i);
            if(iter != tableInfo->indexInfo.end())  
            std::cout<<"Find index, the value is "<<iter->second<<std::endl;
            size_t len = iter->second.size();
            tablelist.write(reinterpret_cast<char*>(&len), sizeof(len));
            tablelist.write(iter->second.c_str(), len);
        }else if((tableInfo->constraint)[i] == 3){
            std::cout<<"Find primary key, the colunm is "<< tableInfo->attributeName[i]<<std::endl;
            size_t len = tableInfo->attributeName[i].size();
            tablelist.write(reinterpret_cast<char*>(&len), sizeof(len));
            tablelist.write(tableInfo->attributeName[i].c_str(), len);
        }
        //留出位置给indexName
    }
    // return tablelist;
}
bool catalog::newTable(TableInfo* tableInfo){
    tableNumber++; 
    if(anychangeornot == false)anychangeornot = true;
    std::ofstream tablelist("./file/catalog/table.dat", std::ios::out | std::ios::binary | std::ios::in);
    std::cout<<"current table number : "<<tableNumber<<std::endl;
    //增加文件中标明的table数目
    tablelist.write(reinterpret_cast<char*>(&tableNumber), sizeof(int));
    writeTabletoFile(tableInfo,tablelist);
    tablelist.close();
    addInfoToList(tableInfo);
    std::cout<<"create table successfully!"<<std::endl;
    return true;
}

void catalog::descTable(std::string tableName){
    int pos = existTable(tableName);
    if(pos < 0){
        std::cout<<"no such table"<<std::endl;
        return;
    }
    std::cout<<"tableName : "<<TableInfoList[pos]->tableName;
    std::cout<<"\tattributeNum : "<<TableInfoList[pos]->attributeNum<<std::endl;
    for(int j = 0 ; j < TableInfoList[pos]->attributeNum; j ++){
        std::cout<<TableInfoList[pos]->attributeName[j] << "\t"<<TableInfoList[pos]->type[j] << "\t"<<TableInfoList[pos]->constraint[j];
        if(TableInfoList[pos]->constraint[j] == 3)std::cout<<"\tprimary key ";
        if(TableInfoList[pos]->constraint[j] == 4)std::cout<<"\tindex "<<TableInfoList[pos]->indexInfo.find(j)->second;
        std::cout<<"\n";
    }

}
void catalog::addInfoToList(TableInfo *tableInfo){
    TableInfo* newTableInfo = tableInfo;
    TableInfoList.push_back(newTableInfo);
}

void catalog::showTable(){
    for(int i = 0 ; i < tableNumber ; i ++){
        std::cout<<TableInfoList[i]->tableName<<std::endl;
    }
}
void catalog::print(){
    for(int i = 0 ; i < tableNumber ; i ++){
        std::cout<<"tableName : "<<TableInfoList[i]->tableName;
        std::cout<<"\tattributeNum : "<<TableInfoList[i]->attributeNum<<std::endl;
        for(int j = 0 ; j < TableInfoList[i]->attributeNum; j ++){
            std::cout<<TableInfoList[i]->attributeName[j] << "\t"<<TableInfoList[i]->type[j] << "\t"<<TableInfoList[i]->constraint[j];
            if(TableInfoList[i]->constraint[j] == 3)std::cout<<"\tprimary key ";
            if(TableInfoList[i]->constraint[j] == 4)std::cout<<"\tindex "<<TableInfoList[i]->indexInfo.find(j)->second;
            std::cout<<"\n";
        }
        //std::cout <<"file_offset :"<<file_offset[i]<<std::endl;
    }
}

void catalog::writeBacktoFile(){
    if(anychangeornot){
        std::ofstream tablelist("./file/catalog/table.dat", std::ios::out | std::ios::binary | std::ios::trunc);
        tablelist.write(reinterpret_cast<char*>(&tableNumber), sizeof(int));
        for(int i = 0 ; i < tableNumber ; i++){
            std::cout<<"writing back table  -------------------------"<<TableInfoList[i]->tableName<<std::endl;
            writeTabletoFile(TableInfoList[i],tablelist);
        }
        tablelist.close();
    }
    return;
}

int catalog::existTable(std::string tableName){
    for(int i = 0 ; i < tableNumber ; i++){
        // std::cout << "check "<<tableName<<std::endl;
        // std::cout << "find "<<TableInfoList[i]->tableName<<std::endl;
        if(TableInfoList[i]->tableName == tableName){
            return i;
        }
    }
    return -1;
}


bool catalog::dropTable(std::string tableName){
    int tablePos = existTable(tableName);
    if(tablePos != -1){//在tableinfolist中的位置
        //目前存在这个table
        //修改数据结构
        tableNumber --;
        std::vector<TableInfo*>::iterator iter1 = TableInfoList.begin() + tablePos;
        TableInfoList.erase(iter1);
        std::vector<size_t>::iterator iter2 = file_offset.begin() + tablePos;
        file_offset.erase(iter2);
        if(anychangeornot == false)anychangeornot = true;
        std::cout<<"table "<<tableName<<"  was sucessfully dropped"<<std::endl;
        return true;
    }
    std::cout<<"table "<<tableName<<" does not exist!"<<std::endl;
    return false;
}


bool catalog::createIndex(IndexInfo *indexinfo){
    int pos = -1;
    for(int i = 0 ; i < tableNumber ; i ++){
        std::map<int,std::string>::iterator it;
        it = TableInfoList[i]->indexInfo.begin();
        while(it != TableInfoList[i]->indexInfo.end())
        {
            //检查每个表上indexName是否被占用
            // std::cout << it->second <<std::endl;
            // if(indexinfo->indexID == TableInfoList[])
            if(indexinfo->indexName == it->second){
                 std::cout<<"index "<<indexinfo->indexName <<" already exists in "<<TableInfoList[i]->tableName<<std::endl;
                 return false;
            }
            it ++;         
        }
        //
        if(TableInfoList[i]->tableName == indexinfo->tableName){
            pos = i;
        }
    }

    //
    if(pos == -1){
        std::cout<<"can not find table in list"<<std::endl;
        return false;
    }
    std::cout<<"i find table in list"<<std::endl;
    auto it = TableInfoList[pos]->getID.find(indexinfo->colunmName);
    if(it!=TableInfoList[pos]->getID.end()){
        //这个列名存在
        auto x = TableInfoList[pos]->indexInfo.find(it->second);
        if(x!=TableInfoList[pos]->indexInfo.end()){
            //这个列已经被建立索引
            std::cout<<"index already exists in "<<TableInfoList[pos]->tableName<<std::endl;
            return false;
        }

    }else{
        std::cout<<"can not find colunm "<<indexinfo->colunmName <<" in list"<<std::endl;
        return false;
    }
    //先修改constraint
    TableInfoList[pos]->constraint[it->second] = 4;
    //修改indexInfo
    std::pair<int,std::string> p = std::make_pair(it->second, indexinfo->indexName);      
    TableInfoList[pos]->indexInfo.insert(p);
    std::cout<<"create index "<<indexinfo->indexName<<std::endl;
    if(!anychangeornot)anychangeornot = true;
    return true;
}

void catalog::dropIndex(std::string indexName,int tableID){
    std::map<int,std::string>::iterator it;
    it = TableInfoList[tableID]->indexInfo.begin();
    while(it != TableInfoList[tableID]->indexInfo.end())
    {
        //检查每个表上indexName是否被占用
        if(indexName == it->second){
            std::cout<<"find index in "<<TableInfoList[tableID]->tableName<<std::endl;
            TableInfoList[tableID]->constraint[it->first] = 0;
            TableInfoList[tableID]->indexInfo.erase(it);//删除map上的这个元素
            if(anychangeornot == false)anychangeornot = true;
            return;
        }
        it ++;
    }
    
    std::cout<<"can not find index "<<indexName<<std::endl;
}


