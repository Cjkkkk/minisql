#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Buffer.h"
#include "dataStructure.h"
using namespace std;

enum Record_State {
	EMPTY = '0',
	VALID
};

struct Keyi {
	int Column;
	int Value;
	Keyi(int c) { this->Column = c; }
};

struct Keyf {
	int Column;
	float Value;
	Keyf(int c) { this->Column = c; }
};

struct Keys {
	int Column;
	string Value;
	Keys(int c) { this->Column = c; }
};

class Record{
public:
	char RecordState;			//�����¼��ɾ����
	Addr self;
	vector<Keyi>KI;
	vector<Keyf>KF;
	vector<Keys>KS;
public:
	Record();
	void clear();
	int Findi(int c);
	float Findf(int c);
	string Finds(int c);
	bool Check(condition C);
};

#define MAX_RECORD (BLOCK_SIZE/this->RECORD_SIZE)

class RecordSet {
public:
	string Record_FileName;
	Addr Top;
	vector<Addr> FreeAddr;
	vector<char> TypeTable;
	int RECORD_SIZE;
	int Columns;
	
public:
	RecordSet(string RecordFileName, vector<int> Cato_TypeTable);
	RecordSet(string RecordFileName);
	void DisposeSet(void);
	void UpdateSet(void);
	int FindRecord(Addr p, Record& R);
	void LoadTestRecord(string filename);
	void Test(string filename);
	void SaveRecord(Record& R);
	Addr InsertRecord(Record& R);
	void DeleteRecord(Addr p);
	void DeleteRecord(set<Addr> ps);
	void Addp(Addr& p);
	void Subp(Addr& p);
	bool Equalp(Addr p, int BlockNum, int FileOff);
	bool Greaterp(Addr p, int BlockNum, int FileOff);
	bool Lessp(Addr p, int BlockNum, int FileOff);
};