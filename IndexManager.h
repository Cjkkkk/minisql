#ifndef INDEXMANAGER_H
#define INDEXMANAGER_H 1
#include <map>
#include <set>
#include <string>
#include "BpTree2.h"
#include "dataStructure.h"
#include <iostream>
using namespace std;
class IndexManager
{
public:
	string Direction;
	map<string, BpTree<int> > BpTrees_I;
	map<string, BpTree<float> > BpTrees_F;
	map<string, BpTree<string> > BpTrees_S;
public:
	IndexManager();
	void CreateIndexFile(IndexInfo I);
	void DropIndexFile(IndexInfo I);
	BpTree<int>& FindBpTree_I(string filename);
	BpTree<float>& FindBpTree_F(string filename);
	BpTree<string>& FindBpTree_S(string filename);
	void InsertSuchKey(IndexInfo I, Addr p, value v);		//create indexʱ��
	set<Addr> FindSuchKey(STMT S,TableInfo T);							//select��deleteʱ��
	void DeleteSuchKey(IndexInfo I, Addr p, value v);		//deleteʱ��
	void SaveAllBpTree(void);
	void LoadAllBpTree(vector<IndexInfo> Is);
};

#endif