#pragma once
#include <string>
#include <list>
#define BLOCK_SIZE  4096
#define MAX_BLOCKS 64
using namespace std;

typedef struct {
	int BlockNum;
	int FileOff;
}Addr;

enum DataType {
	INT = '0',
	FLOAT,
	STRING,
	N_A
};

class Block
{
public:
	string FileName;			//到哪个文件找数据
	int FileOff;				//在文件当中的哪一块找数据
	char data[BLOCK_SIZE];
public:
	Block(void);
	void BlockClear(void);
	void BlockClear_Back(void);
	void BlockSet(string FileName, int FileOff);
	void ReadFile(void);
	void WriteFile(void);
};

class Buffer
{
public:
	Block buffer[MAX_BLOCKS];
	list<int> Empty_Block;			//空闲块
	list<int> Occupy_Block;			//占用块，并通过修改时间排好序
	int Dirty[MAX_BLOCKS];
	int Pin[MAX_BLOCKS];
public:
	Buffer(void);
	list<int>::iterator Find(int BlockNum);
	int Find(string FileName, int FileOff);
	int Allocate(string FileName, int FileOff);
	void Update(list<int>::iterator it);
	void LoadData(int BlockNum);
	void SaveData(int BlockNum);
	void SaveDataAll(void);
	void Lock(int BlockNum);
	void UnLock(int BlockNum);
	void Dirt(int BlockNum);
	void UnDirt(int BlockNum);
	void Free(int BlockNum);
	void FreeAll(void);
	void CreateFile(string filename);
	void DeleteFile(string filename);
};