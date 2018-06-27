#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H 1
#include <map>
#include <set>
#include <string>
#include "./Record.h"
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
	int ReturnKP(IndexInfo I, Addr p, value& v);	//p���ڲ�������������״̬��1�ǳɹ����أ�0��������ɾ��¼��-1�Ǳ����������ļ�
	set<Addr> FindSuchRecord(STMT S);				//��û����������ʱ��ֻ�ܰѼ�¼�ļ���ͷɨ��һ��
	set<Addr> FindSuchRecord(STMT S, set<Addr>ps);	//��������һ����ˣ�API�ѹ��˺�ĵ�ַ���Ϸ��������еڶ���ɸѡ
	void InsertSuchRecord(STMT S, Addr& p);			//����һ����¼,���ظü�¼���ļ��еĵ�ַ��Ϣ
	void PrintRecord(STMT S, set<Addr> ps);			//��ps������λ�õļ�¼�������Ļ
	void DeleteSuchRecord(STMT S, set<Addr> ps);	//��ps������λ�õļ�¼ɾ����
	set<Addr> FindandDelete(STMT S);				//ɾ���ķ�װ����
	set<Addr> FindandDelete(STMT S, set<Addr>ps);	//ɾ���ķ�װ��������������������֮��
	void FindandPrint(STMT S);						//���ҵķ�װ����
	void FindandPrint(STMT S, set<Addr>ps);			//���ҵķ�װ��������������������֮��
	void LoadAllRecordSet(vector<TableInfo> Ts);
	void SaveAllRecordSet(void);
};

#endif