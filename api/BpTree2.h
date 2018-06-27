#pragma once
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstring>
#include "Buffer.h"
#define  NODE_SIZE			BLOCK_SIZE
#define  MIN_KEY_LEAF		(min_key_leaf(this->N))
#define  MIN_POINTS_NONLEAF	(min_points_nonleaf(this->N))
#define  MIN_POINTS_ROOT	2
using namespace std;
extern Buffer blocks;			//引入缓冲区，B+树的结点信息皆与缓冲区直接交互
extern enum DataType;

int min_key_leaf(int n) {
	int temp = (n - 1) / 2;
	if (temp * 2 < n - 1)
		temp++;
	return temp;
}

int min_points_nonleaf(int n) {
	int temp = n / 2;
	if (temp * 2 < n)
		temp++;
	return temp;
}

enum status {
	INTERNAL = '0',
	LEAF
};

template<class K>
class IndexNode {
public:
	char NodeState;	/* Internal/Leaf */
	vector<K> k;
	vector<char> v;
	vector<Addr> p;
	Addr parent;
	Addr self;
public:
	IndexNode(int N);
};

template<class K>
IndexNode<K>::IndexNode(int N) {
	int i;
	k = vector<K>(N);
	v = vector<char>(N);
	p = vector<Addr>(N);
	this->NodeState = INTERNAL;
	this->parent = { -1, -1 };
	this->self = { -1, -1 };
	for (i = 0; i < N - 1; i++) {
		this->v[i] = '0';
		this->p[i] = { -1, -1 };
	}
	this->p[N - 1] = { -1, -1 };
}

template<class K>
struct Ext_IndexNode {
	vector<K> k;
	vector<char> v;
	vector<Addr> p;
	Ext_IndexNode(int N) {
		k = vector<K>(N);
		v = vector<char>(N);
		p = vector<Addr>(N + 1);
	}
};

template<class K>
class BpTree
{
private:
	char Data_Type;
	string Index_FileName;
	int Current_Off;
	int N;
	vector<int> FileOff_bin;			//回收被删结点的FileOff值，使可重用
	Addr RootAddr;
public:
	BpTree(string IndexFileName, char datatype);
	BpTree(string IndexFileName);
	void DisposeTree(void);
	int SeekN(void);
	void Test(string filename);
	int CurrentOff(void);
	int RootFileOff(void);
	void Node2Block(IndexNode<K> Node);
	void Block2Node(int BlockNum, IndexNode<K>& Node);
	void UpdateBlock(IndexNode<K> Node);
	void UpdateTree(void);
	void InsertNode(IndexNode<K> &Node);
	void DeleteNode(IndexNode<K> &Node);
	void LockNode(IndexNode<K> Node);
	int IsRoot(IndexNode<K> Node);
	int IsLeaf(IndexNode<K> Node);
	int IsFew(IndexNode<K> Node);
	int CanFit(IndexNode<K> A, IndexNode<K> B);
	void FindNode(Addr p, IndexNode<K>& Node);
	int HaveK(IndexNode<K> C, K k);
	int FindKey(K k, IndexNode<K>& C);
	int FindFirstKey(K k, Addr& p);
	int FindNextKey(K k, Addr& p);
	Addr FindLeafAddr(K k, Addr p);
	set<Addr> FindEQ(K k);					//equal
	set<Addr> FindNEQ(K k);					//not equal
	set<Addr> FindLess(K k, bool EQ);		//less than (or equal)
	set<Addr> FindGreater(K k, bool EQ);	//greater than (or equal)
	set<Addr> FindLessGreater(K kl, K kg, bool EQL, bool EQG);
	void InsertKey(K k, Addr p);
	void Insert_Leaf(IndexNode<K>& C, K k, Addr p);
	void Insert_Parent(IndexNode<K>& C, K k, IndexNode<K>& D);
	void DeleteKey(K k, Addr p);
	void Delete_Aux(IndexNode<K>& C, K k, Addr p);
	void Coalesce(IndexNode<K>& C, IndexNode<K>& D, K k2);
	void Redistribute(IndexNode<K>& C, IndexNode<K>& D, K k2, int i, int j);
	void UpdateKey(K oldk, K newk, Addr p);
};

template<class K>
BpTree<K>::BpTree(string IndexFileName, char datatype) {
	this->Data_Type = datatype;
	this->N = this->SeekN();
	this->Current_Off = 0;
	this->Index_FileName = IndexFileName;
	this->RootAddr.BlockNum = -1;
	this->RootAddr.FileOff = -1;
	this->FileOff_bin.clear();
	blocks.CreateFile(IndexFileName);
	cout << "NODE_SIZE: " << NODE_SIZE << endl;
	cout << "N: " << N << endl;
	cout << "MIN_KEY_LEAF: " << MIN_KEY_LEAF << endl;
	cout << "MIN_POINTS_NONLEAF: " << MIN_POINTS_NONLEAF << endl;
	cout << "MIN_POINTS_ROOT: " << MIN_POINTS_ROOT << endl;
}

template<class K>
BpTree<K>::BpTree(string IndexFileName) {
	int i, s, n;
	this->Index_FileName = IndexFileName;
	int BlockNum = blocks.Allocate(IndexFileName, 0);
	char* p = blocks.buffer[BlockNum].data;
	memcpy(&this->Data_Type, p, sizeof(char));
	p += sizeof(char);
	memcpy(&this->N, p, sizeof(int));
	p += sizeof(int);
	memcpy(reinterpret_cast<char*>(&this->RootAddr.FileOff), p, sizeof(int));
	p += sizeof(int);
	memcpy(reinterpret_cast<char*>(&this->Current_Off), p, sizeof(int));
	p += sizeof(int);
	memcpy(reinterpret_cast<char*>(&s), p, sizeof(int));
	p += sizeof(int);
	for (i = 0; i < s; i++) {
		memcpy(reinterpret_cast<char*>(&n), p, sizeof(int));
		p += sizeof(int);
		this->FileOff_bin.push_back(n);
	}
}

template<class K>
void BpTree<K>::DisposeTree(void) {
	blocks.DeleteFile(this->Index_FileName);
}

template<class K>
int BpTree<K>::SeekN(void) {
	// NODE_REAL_SIZE = 1 + (N-1)*(sizeof(K)+1) + 2*N*sizeof(int)			 ...由于叶节点要存放的大小比非叶节点多一点，所以这里按照叶节点计算
	//				  = (sizeof(K)+9)*N - sizeof(K) <= NODE_SIZE = 4096
	// ->
	// N <= (NODE_SIZE+sizeof(K)) / (sizeof(K)+9)
	// N_max = (NODE_SIZE+sizeof(K)) / (sizeof(K)+9)
	int a = NODE_SIZE + sizeof(K);
	int b = sizeof(K) + 9;
	return a / b;
}

template<class K>
void BpTree<K>::Test(string filename) {
	int m;
	char buf[100];
	vector<IndexNode<K> > Nodes;
	fstream bin;
	int Off = 1;
	bin.open(filename, ios::in | ios::binary);
	while (Off <= this->Current_Off) {
		IndexNode<K> Node = IndexNode<K>(N);
		bin.seekg(BLOCK_SIZE*Off);
		bin.read(reinterpret_cast<char*>(&Node.NodeState), sizeof(char));
		Node.self.BlockNum = -1;
		Node.self.FileOff = Off++;
		for (m = 0; m < N - 1; m++) {
			stringstream temp;
			bin.read(&Node.v[m], sizeof(char));
			if (Node.v[m] == '1') {
				if (this->Data_Type == STRING) {
					bin.read(buf, sizeof(string));
					stringstream temp;
					temp << buf;
					temp >> Node.k[m];
				}
				else {
					bin.read(reinterpret_cast<char*>(&Node.k[m]), sizeof(K));
				}
			}
			else {
				bin.read(buf, sizeof(K));
			}
		}
		if (Node.NodeState == LEAF) {
			for (m = 0; m < N - 1; m++) {
				bin.read(reinterpret_cast<char*>(&Node.p[m].BlockNum), sizeof(int));
			}
		}
		for (m = 0; m < N; m++) {
			bin.read(reinterpret_cast<char*>(&Node.p[m].FileOff), sizeof(int));
		}
		Node.parent.BlockNum = -1;
		bin.read(reinterpret_cast<char*>(&Node.parent.FileOff), sizeof(int));
		if (bin.eof())
			break;
		Nodes.push_back(Node);
	}
	cout << "Root File Offset Is: " << this->RootAddr.FileOff << endl;
	bin.close();
	Nodes.clear();
}

template<class K>
int BpTree<K>::CurrentOff(void) {
	return this->Current_Off;
}

template<class K>
int BpTree<K>::RootFileOff(void) {
	return this->RootAddr.FileOff;
}

template<class K>
void BpTree<K>::Node2Block(IndexNode<K> Node) {
	//结点在一个块当中的存储顺序是：NodeState, k[N], v[N], p[N].FileOff, parent.FileOff
	int i;
	Block& B = blocks.buffer[Node.self.BlockNum];
	char* p = B.data;
	memcpy(p, reinterpret_cast<char*>(&Node.NodeState), sizeof(char));
	p += sizeof(char);
	for (i = 0; i < N-1; i++) {
		stringstream temp;
		string s;
		memcpy(p, &Node.v[i], sizeof(char));
		p += sizeof(char);
		if (Node.v[i] == '1') {
			if (this->Data_Type == STRING) {
				stringstream temp;
				string s;
				temp << Node.k[i];
				temp >> s;
				memcpy(p, s.c_str(), sizeof(string));
			}
			else {
				memcpy(p, reinterpret_cast<char*>(&Node.k[i]), sizeof(K));
			}
		}
		p += sizeof(K);
	}
	if (Node.NodeState == LEAF) {
		for (i = 0; i < N - 1; i++) {
			memcpy(p, reinterpret_cast<char*>(&Node.p[i].BlockNum), sizeof(int));
			p += sizeof(int);
		}
	}
	for (i = 0; i < N; i++) {
		memcpy(p, reinterpret_cast<char*>(&Node.p[i].FileOff), sizeof(int));
		p += sizeof(int);
	}
	memcpy(p, reinterpret_cast<char*>(&Node.parent.FileOff), sizeof(int));
	blocks.Dirt(Node.self.BlockNum);						//设为脏块
	blocks.Lock(Node.self.BlockNum);						//上锁
}

template<class K>
void BpTree<K>::Block2Node(int BlockNum, IndexNode<K>& Node) {
	int i;
	char buf[100];
	char* p = blocks.buffer[BlockNum].data;
	memcpy(&Node.NodeState, p, sizeof(char));
	p += sizeof(char);
	for (i = 0; i < N - 1; i++) {
		stringstream temp;
		memcpy(&Node.v[i], p, sizeof(char));
		p += sizeof(char);
		if (Node.v[i] == '1') {
			if (this->Data_Type == STRING) {
				stringstream temp;
				memcpy(buf, p, sizeof(string));
				temp << buf;
				temp >> Node.k[i];
			}
			else {
				memcpy(reinterpret_cast<char*>(&Node.k[i]), p, sizeof(K));
			}
		}
		p += sizeof(K);
	}
	if (Node.NodeState == LEAF) {
		for (i = 0; i < N - 1; i++) {
			memcpy(reinterpret_cast<char*>(&Node.p[i].BlockNum), p, sizeof(int));
			p += sizeof(int);
		}
	}
	for (i = 0; i < N; i++) {
		memcpy(reinterpret_cast<char*>(&Node.p[i].FileOff), p, sizeof(int));
		p += sizeof(int);
	}
	memcpy(reinterpret_cast<char*>(&Node.parent.FileOff), p, sizeof(int));
}

template<class K>
void BpTree<K>::UpdateBlock(IndexNode<K> Node) {
	Block B = blocks.buffer[Node.self.BlockNum];
	if (Node.self.FileOff != B.FileOff || this->Index_FileName != B.FileName) {
		//如果这一块已经被别人占领，需要另辟新的一块
		Node.self.BlockNum = blocks.Allocate(this->Index_FileName, Node.self.FileOff);
	}
	this->Node2Block(Node);
	blocks.Update(blocks.Find(Node.self.BlockNum));
}

template<class K>
void BpTree<K>::UpdateTree(void) {
	int i, s = this->FileOff_bin.size();
	int BlockNum = blocks.Find(this->Index_FileName, 0);
	if (BlockNum == -1) {
		BlockNum = blocks.Allocate(this->Index_FileName, 0);
	}
	char* p = blocks.buffer[BlockNum].data;
	memcpy(p, &this->Data_Type, sizeof(char));
	p += sizeof(char);
	memcpy(p, reinterpret_cast<char*>(&this->N), sizeof(int));
	p += sizeof(int);
	memcpy(p, reinterpret_cast<char*>(&this->RootAddr.FileOff), sizeof(int));
	p += sizeof(int);
	memcpy(p, reinterpret_cast<char*>(&this->Current_Off), sizeof(int));
	p += sizeof(int);
	memcpy(p, reinterpret_cast<char*>(&s), sizeof(int));
	p += sizeof(int);
	for (i = 0; i < s && i < 1000; i++) {
		memcpy(p, reinterpret_cast<char*>(&this->FileOff_bin.back()), sizeof(int));
		p += sizeof(int);
		this->FileOff_bin.pop_back();
	}
	blocks.Lock(BlockNum);
}

template<class K>
void BpTree<K>::InsertNode(IndexNode<K>& Node) {
	Addr p;
	if (this->FileOff_bin.empty()) {
		Node.self.FileOff = ++this->Current_Off;
	}
	else{
		Node.self.FileOff = this->FileOff_bin.back();
		this->FileOff_bin.pop_back();
	}
	Node.self.BlockNum = blocks.Allocate(this->Index_FileName, Node.self.FileOff);	//为该结点申请buffer中的一块内存，块号存于Block_Num中,并上锁
	this->Node2Block(Node);															//将结点信息导入块当中
}

template<class K>
void BpTree<K>::DeleteNode(IndexNode<K> &Node) {
	this->FileOff_bin.push_back(Node.self.FileOff);
	Block B = blocks.buffer[Node.self.BlockNum];
	if (Node.self.FileOff != B.FileOff || this->Index_FileName != B.FileName) {
		//如果这一块已经被别人占领，需要另辟新的一块
		Node.self.BlockNum = blocks.Allocate(this->Index_FileName, Node.self.FileOff);
	}
	blocks.Free(Node.self.BlockNum);
}

template<class K>
void BpTree<K>::LockNode(IndexNode<K> Node) {
	blocks.Lock(Node.self.BlockNum);
}

template<class K>
int BpTree<K>::IsRoot(IndexNode<K> Node) {
	return Node.parent.FileOff == -1;
}

template<class K>
int BpTree<K>::IsLeaf(IndexNode<K> Node) {
	return Node.NodeState == LEAF;
}

template<class K>
int BpTree<K>::IsFew(IndexNode<K> Node) {
	int i;
	if (this->IsLeaf(Node)) {
		for (i = 0; i < N - 1 && Node.v[i] == '1'; i++);
		return i < MIN_KEY_LEAF;
	}
	else {
		for (i = 0; i < N && Node.p[i].FileOff != -1; i++);
		return i < MIN_POINTS_NONLEAF;
	}
}

template<class K>
int BpTree<K>::CanFit(IndexNode<K> A, IndexNode<K> B) {
	int i, j;
	if (this->IsLeaf(A) && this->IsLeaf(B)){
		for (i = 0; i < N - 1 && A.v[i] == '1'; i++);
		for (j = 0; j < N - 1 && B.v[j] == '1'; j++);
		return i + j <= N - 1;
	}
	else if (!this->IsLeaf(A) && !this->IsLeaf(B)) {
		for (i = 0; i < N && A.p[i].FileOff != -1; i++);
		for (j = 0; j < N && B.p[j].FileOff != -1; j++);
		return i + j <= N;
	}
	else
		return 0;
}

template<class K>
void BpTree<K>::FindNode(Addr p, IndexNode<K>& Node) {
	if (p.FileOff == -1) {
		cout << "Wrong address!" << endl;
		system("pause");
		exit(1);
	}
	int BlockNum = blocks.Find(this->Index_FileName, p.FileOff);		//先找该块是否已在buffer当中
	if (BlockNum == -1) {
		BlockNum = blocks.Allocate(this->Index_FileName, p.FileOff);	//如果没有，再申请一块
	}
	Node.self.BlockNum = BlockNum;										//地址p中的块号不可信
	Node.self.FileOff = p.FileOff;
	this->Block2Node(BlockNum, Node);									//将块内信息分类导入结点当中
}

template<class K>
int BpTree<K>::HaveK(IndexNode<K> C, K k) {
	int i;
	for (i = 0; i < N - 1 && C.v[i] == '1' && C.k[i] != k; i++);
	if (i == N - 1 || C.v[i] == '0')		return 0;
	else									return 1;
}

template<class K>
int BpTree<K>::FindKey(K k, IndexNode<K>& C) {
	IndexNode<K> D(N);
	int i;
	if (this->RootAddr.FileOff == -1)		return -1;	//如果是空树，直接返回-1
	this->FindNode(this->RootAddr, C);
	while (C.NodeState != LEAF) {
		for (i = 0; i < N - 1 && C.v[i] == '1' && k > C.k[i]; i++);
		if (i == N - 1 || C.v[i] == '0') {
			this->FindNode(C.p[i], C);
		}
		else if (k == C.k[i]) {
			this->FindNode(C.p[i], D);
			if(this->HaveK(D, k))
				this->FindNode(C.p[i], C);			//如果C.p[i]当中有k，则C = this->FindNode(C.p[i]);
			else
				this->FindNode(C.p[i + 1], C);		//如果C.p[i]当中无k，则C = this->FindNode(C.p[i + 1]);
		}
		else if (k < C.k[i]) {
			this->FindNode(C.p[i], C);
		}
	}
	for (i = 0; i < N - 1 && C.v[i] == '1'&& k != C.k[i]; i++);
	if (i == N - 1 || C.v[i] == '0') {
		return -1;		//未找到
	}
	else {
		return i;		//找到了
	}
}

template<class K> 
int BpTree<K>::FindNextKey(K k, Addr& p) {
	int i;
	IndexNode<K> C(N);
	int start = this->FindKey(k, C);
	if (start == -1)
		start = 0;
	while (1) {
		for (i = start; i < N - 1 && C.v[i] == '1' && C.k[i] <= k; i++);
		if ((i == N - 1 || C.v[i] == '0') && C.p[N - 1].FileOff == -1) {
			i = -1;
			break;									//到头了，返回叶结点链最后一个键的位置
		}
		else if (i == N - 1 || C.v[i] == '0') {		//找叶结点链的下一个结点
			start = 0;
			this->FindNode(C.p[N - 1], C);
		}
		else if (C.k[i] > k) {
			break;									//找到下一个键的第一个位置
		}
	}
	p = C.self;
	return i;
}

template<class K>
int BpTree<K>::FindFirstKey(K k, Addr& p) {
	int i, pos;
	p = this->RootAddr;
	IndexNode<K> C(N);
	IndexNode<K> D(N);
	this->FindNode(p, C);
	while (C.NodeState != LEAF) {
		for (i = 0; i < N - 1 && C.v[i] == '1' && k > C.k[i]; i++);
		if (i == N - 1 || C.v[i] == '0') {
			p = C.p[i];
		}
		else if (k == C.k[i]) {
			this->FindNode(C.p[i], D);
			if (this->HaveK(D, k))
				p = C.p[i];			//如果C.p[i]当中有k，则C = this->FindNode(C.p[i]);
			else
				p = C.p[i + 1];		//如果C.p[i]当中无k，则C = this->FindNode(C.p[i + 1]);
		}
		else if (k < C.k[i]) {
			p = C.p[i];
		}
		this->FindNode(p, C);
	}
	for (pos = 0; pos < N - 1 && C.k[pos] < k; pos++);
	return pos;
}

template<class K>
Addr BpTree<K>::FindLeafAddr(K k, Addr p) {
	int start, i, flag = 0;
	IndexNode<K> C(N);
	Addr retp = { -1, -1 };
	start = this->FindKey(k, C);
	while (1) {
		for (i = start; i < N - 1 && C.v[i] == '1' && C.k[i] == k; i++) {
			if (C.p[i].FileOff == p.FileOff) {
				flag = 1;	break;			//找到了
			}
		}
		if (flag == 1) {
			retp = C.self;
			break;
		}
		else if((i == N - 1 || C.v[i] == '0') && C.p[N - 1].FileOff == -1){
			break;
		}
		else if (i == N - 1 || C.v[i] == '0') {
			start = 0;
			this->FindNode(C.p[N - 1], C);
		}
		else if (C.k[i] != k) {
			break;
		}
	}
	return retp;
}

template<class K>
set<Addr> BpTree<K>::FindEQ(K k) {
	IndexNode<K> C(N);
	Addr Cp;
	int i;
	set<Addr> ret;
	int pos = this->FindFirstKey(k, Cp);
	this->FindNode(Cp, C);			//C.k[pos]是第一个键值为k的地方
	if (pos == -1)
		return ret;					//找不到该键值，返回空数组
	while (1) {
		for (i = pos; i < N - 1 && C.v[i] == '1' && C.k[i] == k; i++) {
			ret.insert(C.p[i]);
		}
		if ((i == N - 1 || C.v[i] == '0') && C.p[N - 1].FileOff == -1) {
			break;									//到头了
		}
		else if (i == N - 1 || C.v[i] == '0') {		//找叶结点链的下一个结点
			pos = 0;
			this->FindNode(C.p[N - 1], C);
		}
		else if (C.k[i] != k) {
			break;									//找到第一个不再是这个键的位置
		}
	}
	return ret;
}

template<class K>
set<Addr> BpTree<K>::FindNEQ(K k) {
	set<Addr> s1 = this->FindGreater(k, false);
	set<Addr> s2 = this->FindLess(k, false);
	set<Addr>::iterator it;
	for (it = s2.begin(); it != s2.end(); it++) {
		s1.insert(*it);
	}
	s2.clear();
	return s1;
}

template<class K>
set<Addr> BpTree<K>::FindLess(K k, bool EQ) {
	IndexNode<K> C(N);
	set<Addr> ret;
	int i, pos = 0;
	if (this->RootAddr.FileOff == -1)
		return ret;
	this->FindNode(this->RootAddr, C);
	while (!this->IsLeaf(C)) {
		this->FindNode(C.p[0], C);
	}
	while (1) {
		if (EQ == false) {
			for (i = pos; i < N - 1 && C.v[i] == '1' && C.k[i] < k; i++) {
				ret.insert(C.p[i]);
			}
			if (C.k[i] >= k) {
				break;
			}
		}
		else {
			for (i = pos; i < N - 1 && C.v[i] == '1' && C.k[i] <= k; i++) {
				ret.push_back(C.p[i]);
			}
			if (C.k[i] > k) {
				break;
			}
		}
		if ((i == N - 1 || C.v[i] == '0') && C.p[N - 1].FileOff == -1) {
			break;
		}
		else if (i == N - 1 || C.v[i] == '0') {
			pos = 0;
			this->FindNode(C.p[N - 1], C);
		}
	}
	return ret;
}

template<class K>
set<Addr> BpTree<K>::FindGreater(K k, bool EQ) {
	IndexNode<K> C(N);
	set<Addr> ret;
	int i, pos;
	Addr Cp;
	if (this->RootAddr.FileOff == -1)
		return ret;
	if (EQ == false) {
		pos = this->FindNextKey(k, Cp);
	}
	else {
		pos = this->FindFirstKey(k, Cp);
	}
	this->FindNode(Cp, C);
	while (1) {
		for (i = pos; i < N - 1 && C.v[i] == '1'; i++) {
			ret.insert(C.p[i]);
		}
		if ((i == N - 1 || C.v[i] == '0') && C.p[N - 1].FileOff == -1) {
			break;
		}
		else if (i == N - 1 || C.v[i] == '0') {
			pos = 0;
			this->FindNode(C.p[N - 1], C);
		}
	}
	return ret;
}

template<class K>
set<Addr> BpTree<K>::FindLessGreater(K kl, K kg, bool EQL, bool EQG) {
	IndexNode<K> C(N);
	set<Addr> ret;
	int i, pos;
	Addr Cp;
	if (this->RootAddr.FileOff == -1)
		return ret;
	if (EQL == false) {
		pos = this->FindNextKey(kl, Cp);
	}
	else {
		pos = this->FindFirstKey(kl, Cp);
	}
	this->FindNode(Cp, C);
	while (1) {
		if (EQG == false) {
			for (i = pos; i < N - 1 && C.v[i] == '1' && C.k[i] < kg; i++) {
				ret.insert(C.p[i]);
			}
			if (C.k[i] >= kg) {
				break;
			}
		}
		else {
			for (i = pos; i < N - 1 && C.v[i] == '1' && C.k[i] <= kg; i++) {
				ret.insert(C.p[i]);
			}
			if (C.k[i] > kg) {
				break;
			}
		}
		if ((i == N - 1 || C.v[i] == '0') && C.p[N - 1].FileOff == -1) {
			break;
		}
		else if (i == N - 1 || C.v[i] == '0') {
			pos = 0;
			this->FindNode(C.p[N - 1], C);
		}
	}
	return ret;
}

template<class K>
void BpTree<K>::InsertKey(K k, Addr p) {
	int i;
	IndexNode<K> C(N);
	if (this->RootAddr.FileOff == -1) {
		C.NodeState = LEAF;		//空树
		C.parent = { -1, -1 };
		C.v[0] = '1';		C.k[0] = k;		C.p[0] = p;
		this->InsertNode(C);
		this->RootAddr = C.self;
		this->UpdateBlock(C);
		return;
	}
	Addr Cp;
	int temp = this->FindFirstKey(k, Cp);	//不是空树
	IndexNode<K> A(N);
	this->FindNode(Cp, A);
	if (A.v[N-2] == '0') {
		this->Insert_Leaf(A, k, p);		//有空
		this->UpdateBlock(A);
		return;
	}
	this->InsertNode(C);				//结点满了，添加新结点
	IndexNode<K> B(N);
	IndexNode<K> D(N);
	this->FindNode(Cp, B);
	this->FindNode(C.self, D);
	IndexNode<K> T = B;
	this->Insert_Leaf(T, k, p);
	for (i = 0; i < N - 1; i++) {
		B.p[i] = { -1, -1 };			//清空B.p[0]到B.p[N - 2]
		B.v[i] = '0';					//清空B.v[0]到B.v[N - 2]
	}
	for (i = 0; i < MIN_POINTS_NONLEAF; i++) {		//更新旧结点
		B.p[i] = T.p[i];
		B.k[i] = T.k[i];
		B.v[i] = '1';
	}
	for (; i < N; i++) {							//更新新结点
		D.p[i - MIN_POINTS_NONLEAF] = T.p[i];
		D.k[i - MIN_POINTS_NONLEAF] = T.k[i];
		D.v[i - MIN_POINTS_NONLEAF] = '1';
	}
	D.NodeState = LEAF;
	D.p[N - 1].BlockNum = B.p[N - 1].BlockNum;	//新结点除父指针外更新完毕，可以插入原树当中
	D.p[N - 1].FileOff = B.p[N - 1].FileOff;
	
	B.p[N - 1] = D.self;		//旧节点除父结点外更新完毕
	K k2 = D.k[0];
	Insert_Parent(B, k2, D);
}

template<class K>
void BpTree<K>::Insert_Leaf(IndexNode<K>& C, K k, Addr p) {
	this->LockNode(C);
	//拿到对应地址的引用，对C修改即可对原树修改
	int pos, i, j;
	for (i = 0; i < N && C.v[i] == '1'; i++);							//第i位起有空
	for (pos = 0; pos < N && C.v[pos] == '1' && C.k[pos] < k; pos++);	//pos及以后需要搬迁
	for (j = i; j > pos; j--) {
		C.v[j] = C.v[j - 1];
		C.k[j] = C.k[j - 1];
		C.p[j] = C.p[j - 1];
	}
	C.k[pos] = k;
	C.p[pos] = p;
	C.v[pos] = '1';
}

template<class K>
void BpTree<K>::Insert_Parent(IndexNode<K>& C, K k, IndexNode<K> & D) {
	this->LockNode(C);
	this->LockNode(D);
	int i, j, pos;
	Addr C_Addr = C.self;
	if (this->IsRoot(C)) {
		IndexNode<K> R(N);		//C本身就是根
		R.NodeState = INTERNAL;
		R.parent = { -1, -1 };
		R.k[0] = k;
		R.v[0] = '1';
		R.p[0] = C.self;
		R.p[1] = D.self;

		this->InsertNode(R);
		C.parent = R.self;
		this->RootAddr = R.self;
		D.parent = R.self;
		this->UpdateBlock(C);
		this->UpdateBlock(D);
		this->UpdateBlock(R);
		return;
	}
	//C不是根
	IndexNode<K> P(N);
	this->FindNode(C.parent, P);
	if (P.p[N - 1].FileOff == -1) {
		for (pos = 0; pos < N && P.p[pos].FileOff != C.self.FileOff; pos++);	//P还有空位
		for (i = 0; i < N && P.p[i].FileOff != -1; i++);
		for (j = i; j > pos + 1; j--) {
			P.v[j - 1] = P.v[j - 2];
			P.k[j - 1] = P.k[j - 2];
			P.p[j] = P.p[j - 1];
		}
		P.v[pos] = '1';
		P.k[pos] = k;
		P.p[pos + 1] = D.self;
		P.NodeState = INTERNAL;
		//C的父结点不用改变
		D.parent = P.self;
		this->UpdateBlock(C);
		this->UpdateBlock(D);
		this->UpdateBlock(P);
		return;
	}
	//P没有空位
	Ext_IndexNode<K> T = Ext_IndexNode<K>(N);
	//拷贝P到T中，顺便清空P
	for (i = 0; i < N-1; i++) {
		T.k[i] = P.k[i];
		T.v[i] = P.v[i];	P.v[i] = '0';
		T.p[i] = P.p[i];	P.p[i] = { -1, -1 };
	}
	T.p[N - 1] = P.p[N - 1];	P.p[N - 1] = { -1, -1 };
	T.p[N] = { -1, -1 };
	//插入新的一对
	for (pos = 0; pos < N + 1 && T.p[pos].FileOff != C.self.FileOff; pos++);
	for (i = 0; i < N + 1 && T.p[i].FileOff != -1; i++);
	for (j = i; j > pos+1; j--) {
		T.v[j - 1] = T.v[j - 2];
		T.k[j - 1] = T.k[j - 2];
		T.p[j] = T.p[j - 1];
	}
	T.v[pos] = '1';
	T.k[pos] = k;		//pos在不在P决定低层的结点选谁为父结点
	T.p[pos + 1] = D.self;
	IndexNode<K> Q(N);
	//重新对P和Q赋值
	for (i = 0; i < MIN_POINTS_NONLEAF - 1; i++) {
		P.k[i] = T.k[i];
		P.v[i] = T.v[i];
		P.p[i] = T.p[i];
	}
	P.p[i] = T.p[i];	//i == MIN_POINTS_NONLEAF - 1
	K k2 = T.k[i];
	i++;				//i == MIN_POINTS_NONLEAF
	for (; i < N; i++) {
		Q.k[i - MIN_POINTS_NONLEAF] = T.k[i];
		Q.p[i - MIN_POINTS_NONLEAF] = T.p[i];
		Q.v[i - MIN_POINTS_NONLEAF] = T.v[i];
	}
	Q.p[i - MIN_POINTS_NONLEAF] = T.p[i];	//i == N
	Q.NodeState = INTERNAL;
	this->InsertNode(Q);
	//对成为Q的子结点，更新其父结点地址
	for (i = 0; i < N && Q.p[i].FileOff != -1; i++) {
		if (Q.p[i].FileOff == C.self.FileOff) {
			C.parent = Q.self;
		}
		else {
			IndexNode<K> E(N);
			this->FindNode(Q.p[i], E);
			E.parent = Q.self;
			this->UpdateBlock(E);
		}
	}
	if (pos < MIN_POINTS_NONLEAF - 1) {
		D.parent = P.self;
	}
	else {
		D.parent = Q.self;
	}
	this->UpdateBlock(C);
	this->UpdateBlock(D);
	this->Insert_Parent(P, k2, Q);		//级联递归
}

template<class K>
void BpTree<K>::DeleteKey(K k, Addr p) {
	Addr pos = this->FindLeafAddr(k, p);
	if (pos.FileOff != -1) {
		IndexNode<K> C(N);
		this->FindNode(pos, C);
		this->Delete_Aux(C, k, p);
	}
	else
		//cout << "Cannot find the key!" << endl;
	return;
}

template<class K>
void BpTree<K>::Delete_Aux(IndexNode<K>& C, K k, Addr p) {
	this->LockNode(C);
	IndexNode<K> D(N);
	int pos, i, j, m, n, flag = 0;
	for (i = 0; i < N - 1 && C.k[i] != k; i++);
	for (j = i + 1; j < N - 1; j++) {
		C.k[j - 1] = C.k[j];
		C.v[j - 1] = C.v[j];
	}
	C.v[N - 2] = '0';										//删掉k
	if (this->IsLeaf(C)) {
		for (i = 0; i < N - 1 && C.p[i].FileOff != p.FileOff; i++);
		for (j = i + 1; j < N - 1; j++) {
			C.p[j - 1] = C.p[j];
		}
		C.p[N - 2] = { -1, -1 };
	}
	else {
		for (i = 0; i < N && C.p[i].FileOff != p.FileOff; i++);
		for (j = i + 1; j < N; j++) {
			C.p[j - 1] = C.p[j];
		}
		C.p[N - 1] = { -1, -1 };
	}														//删掉p
	if (this->IsRoot(C)) {
		if (this->IsLeaf(C)) {								//整棵树只剩一个结点
			if (C.v[0] == '0') {							//根没有键值
				this->RootAddr = C.p[0];					//清空树
				this->DeleteNode(C);
			}
			else {
				//若还有键值，则保留
				this->UpdateBlock(C);
			}
		}
		else {												//根还有孩子
			if (C.p[1].FileOff == -1) {						//根只有一个孩子
				this->FindNode(C.p[0], D);
				D.parent = C.parent;
				this->UpdateBlock(D);
				this->RootAddr = C.p[0];
				this->DeleteNode(C);						//根转移至根的孩子
			}
			else {
				//若根还有更多孩子，则保留
				this->UpdateBlock(C);
			}
		}
		return;
	}
	//非根情况
	if (!this->IsFew(C)) {
		this->UpdateBlock(C);
		return;
	}
	//指针数或键值数太少，考虑合并或者分摊
	j = -1;
	IndexNode<K> P(N);
	this->FindNode(C.parent, P);
	for (i = 0; i < N && P.p[i].FileOff != C.self.FileOff; i++);	//P.p[i] == C.self
	if (i+1 < N && P.p[i + 1].FileOff != -1) {
		this->FindNode(P.p[i + 1], D);
		if ((i == 0 && CanFit(C, D) ||
			(i + 1 < N && P.p[i + 1].FileOff != -1 && CanFit(C, D)))) {
			j = i + 1;		//若右邻与之可合并，则赋D = P_i+1
			flag = 1;
		}
	}
	if (i > 0) {
		this->FindNode(P.p[i - 1], D);
		if (((i + 1 == N || P.p[i + 1].FileOff == -1) && CanFit(C, D)) ||
			(i > 0 && CanFit(C, D))) {
			j = i - 1;		//若左邻与之可合并，则赋D = P_i-1
			flag = 1;
		}
	}
	//当左右邻皆可合并时，优先选D = P_i-1
	if (!flag) {
		j = (i == 0) ? 1 : i - 1;
		//若找不到可合并的邻居，优先选左邻居
	}
	this->FindNode(P.p[j], D);
	K k2 = (i < j) ? P.k[i] : P.k[j];
	if (flag) {
		//合并过程
		if (j == i + 1) {
			this->Coalesce(D, C, k2);
		}
		else if(j == i-1) {
			this->Coalesce(C, D, k2);
		}
	}
	else {
		//分摊过程
		this->Redistribute(C, D, k2, i, j);
	}
	return;
}

template<class K>
void BpTree<K>::Coalesce(IndexNode<K>& C, IndexNode<K>& D, K k2) {
	this->LockNode(C);
	this->LockNode(D);
	IndexNode<K> E(N);
	IndexNode<K> P(N);
	int m, pos;
	if (!this->IsLeaf(C)) {
		//非叶节点之间的合并
		for (pos = 0; pos < N - 1 && D.v[pos] == '1'; pos++);	//D.k[pos]是空的，D.p[pos+1]是空的
		D.k[pos] = k2;
		D.v[pos] = '1';
		pos++;
		for (m = 0; C.v[m] == '1'; m++) {
			D.k[pos + m] = C.k[m];
			D.p[pos + m] = C.p[m];
			D.v[pos + m] = C.v[m];
		}
		D.p[pos + m] = C.p[m];
		for (m = 0; m < N && C.p[m].FileOff != -1; m++) {
			this->FindNode(C.p[m], E);
			E.parent = D.self;
			this->UpdateBlock(E);
		}
	}
	else {
		//叶节点之间的合并
		for (pos = 0; pos < N - 1 && D.v[pos] == '1'; pos++);	//D.k[pos]是空的，D.p[pos]是空的
		for (m = 0; C.v[m] == '1'; m++) {
			D.k[pos + m] = C.k[m];
			D.p[pos + m] = C.p[m];
			D.v[pos + m] = C.v[m];
		}
		D.p[N - 1] = C.p[N - 1];
	}
	this->UpdateBlock(C);
	this->UpdateBlock(D);
	Addr temp_p = C.self;
	this->FindNode(C.parent, P);
	this->Delete_Aux(P, k2, C.self);
	this->FindNode(temp_p, E);
	this->DeleteNode(E);
	return;
}

template<class K>
void BpTree<K>::Redistribute(IndexNode<K>& C, IndexNode<K>& D, K k2, int i, int j) {
	this->LockNode(C);
	this->LockNode(D);
	IndexNode<K> P(N);
	IndexNode<K> E(N);
	this->FindNode(C.parent, P);
	int m, n;
	//分四种情况讨论
	if (j < i) {
		//D是C的左邻
		if (!this->IsLeaf(C)) {
			for (m = 0; m < N && D.p[m].FileOff != -1; m++);
			m--;		//D.p[m]是D中最后一个有效指针
			C.p[N - 1] = C.p[N - 2];
			for (n = N - 2; n >= 1; n--) {
				C.k[n] = C.k[n - 1];
				C.v[n] = C.v[n - 1];
				C.p[n] = C.p[n - 1];
			}
			C.k[0] = k2;
			C.v[0] = '1';
			C.p[0] = D.p[m];							//分出来的一块插入C中
			this->FindNode(D.p[m], E);
			E.parent = C.self;		//更新被移动结点的父亲
			this->UpdateBlock(E);
			P.k[j] = D.k[m - 1];						//更新CD之间的键值
			D.p[m] = { -1,-1 };
			D.v[m - 1] = '0';							//删除D中被分出去的那一块
		}
		else {
			for (m = 0; m < N - 1 && D.v[m] == '1'; m++);
			m--;		//(D.p[m],D.k[m])是D中最后一组有效数据
			for (n = N - 2; n >= 1; n--) {
				C.k[n] = C.k[n - 1];
				C.v[n] = C.v[n - 1];
				C.p[n] = C.p[n - 1];
			}
			C.k[0] = D.k[m];
			C.v[0] = '1';
			C.p[0] = D.p[m];							//分出来的一块插入C中
			P.k[j] = D.k[m];		//更新CD之间的键值
			D.v[m] = '0';
			D.p[m] = { -1, -1 };						//删除D中被分出去的那一块
		}
	}
	else {
		//D是C的右邻
		if (!this->IsLeaf(C)) {
			for (m = 0; m < N && C.p[m].FileOff != -1; m++);		//C.p[m]和C.k[m-1]是空的
			C.k[m - 1] = k2;
			C.v[m - 1] = '1';
			C.p[m] = D.p[0];
			this->FindNode(D.p[0], E);
			E.parent = C.self;
			this->UpdateBlock(E);
			P.k[i] = D.k[0];
			for (n = 1; n < N - 1; n++) {
				D.k[n - 1] = D.k[n];
				D.v[n - 1] = D.v[n];
				D.p[n - 1] = D.p[n];
			}
			D.p[N - 2] = D.p[N - 1];
			D.p[N - 1] = { -1, -1 };
			D.v[N - 2] = '0';
		}
		else {
			for (m = 0; m < N - 1 && C.v[m] == '1'; m++);		//C.k[m]和C.p[m]是空的
			C.k[m] = D.k[0];
			C.v[m] = '1';
			C.p[m] = D.p[0];
			P.k[i] = D.k[1];
			for (n = 1; n < N - 1; n++) {
				D.k[n - 1] = D.k[n];
				D.v[n - 1] = D.v[n];
				D.p[n - 1] = D.p[n];
			}
			D.p[N - 2] = { -1, -1 };
			D.v[N - 2] = '0';
		}
	}
	this->UpdateBlock(C);
	this->UpdateBlock(D);
	this->UpdateBlock(P);
	return;
}

template<class K>
void BpTree<K>::UpdateKey(K oldk, K newk, Addr p) {
	this->DeleteKey(oldk, p);
	this->InsertKey(newk, p);
	return;
}