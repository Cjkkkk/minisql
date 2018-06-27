#pragma once
#include <map>
#include <set>
#include <string>
#include "BpTree2.h"
#include "dataStructure.h"
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
	void InsertSuchKey(IndexInfo I, Addr p, value v);		//create index时用
	set<Addr> FindSuchKey(STMT S);							//select和delete时用
	void DeleteSuchKey(IndexInfo I, Addr p, value v);		//delete时用
	void SaveAllBpTree(void);
	void LoadAllBpTree(vector<IndexInfo> Is);
};