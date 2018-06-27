#pragma once
#include <map>
#include <set>
#include <string>
#include "Record.h"
#include "dataStructure.h"
using namespace std;
class RecordManager
{
public:
	string Direction;
	map<string, RecordSet> Total_Record;
public:
	RecordManager();
	void CreateRecordFile(TableInfo T);
	void DropRecordFile(TableInfo T);
	RecordSet& FindRecordSet(string filename);
	int ReturnKP(IndexInfo I, Addr p, value& v);	//p在内部会自增；返回状态：1是成功返回，0是遇到被删记录，-1是遍历完整个文件
	set<Addr> FindSuchRecord(STMT S);				//当没有索引条件时，只能把记录文件从头扫描一遍
	set<Addr> FindSuchRecord(STMT S, set<Addr>ps);	//有索引第一遍过滤，API把过滤后的地址集合发过来进行第二遍筛选
	void InsertSuchRecord(STMT S, Addr& p);			//插入一个记录,传回该记录在文件中的地址信息
	void PrintRecord(STMT S, set<Addr> ps);			//把ps中所有位置的记录输出至屏幕
	void DeleteSuchRecord(STMT S, set<Addr> ps);	//把ps中所有位置的记录删除了
	set<Addr> FindandDelete(STMT S);				//删除的封装函数
	set<Addr> FindandDelete(STMT S, set<Addr>ps);	//删除的封装函数，经过了索引查找之后
	void FindandPrint(STMT S);						//查找的封装函数
	void FindandPrint(STMT S, set<Addr>ps);			//查找的封装函数，经过了索引查找之后
	void LoadAllRecordSet(vector<TableInfo> Ts);
	void SaveAllRecordSet(void);
};