#include "IndexManager.h"

IndexManager::IndexManager(){
	this->Direction = "";
}

void IndexManager::CreateIndexFile(IndexInfo I) {
	string filename;
	filename = Direction + I.tableName + "_" + I.colunmName + "_idx.dat";
	if (I.type == 50000) {
		BpTree<int> Tree_I = BpTree<int>(filename, INT);
		this->BpTrees_I.insert(pair<string, BpTree<int> > (filename, Tree_I));
	}
	else if (I.type == 90000) {
		BpTree<float> Tree_F = BpTree<float>(filename, FLOAT);
		this->BpTrees_F.insert(pair<string, BpTree<float> >(filename, Tree_F));
	}
	else if (I.type > 120000) {
		BpTree<string> Tree_S = BpTree<string>(filename, STRING);
		this->BpTrees_S.insert(pair<string, BpTree<string> >(filename, Tree_S));
	}
}

void IndexManager::DropIndexFile(IndexInfo I) {
	string filename;
	filename = Direction + I.tableName + "_" + I.colunmName + "_idx.dat";
	if (I.type == 50000) {
		map<string, BpTree<int> >::iterator it;
		it = this->BpTrees_I.find(filename);
		it->second.DisposeTree();
		it = this->BpTrees_I.erase(it);
	}
	else if (I.type == 90000) {
		map<string, BpTree<float> >::iterator it;
		it = this->BpTrees_F.find(filename);
		it->second.DisposeTree();
		it = this->BpTrees_F.erase(it);
	}
	else if (I.type > 120000) {
		map<string, BpTree<string> >::iterator it;
		it = this->BpTrees_S.find(filename);
		it->second.DisposeTree();
		it = this->BpTrees_S.erase(it);
	}
}

BpTree<int>& IndexManager::FindBpTree_I(string filename) {
	map<string, BpTree<int> >::iterator it = this->BpTrees_I.find(filename);
	return it->second;
}

BpTree<float>& IndexManager::FindBpTree_F(string filename) {
	map<string, BpTree<float> >::iterator it = this->BpTrees_F.find(filename);
	return it->second;
}

BpTree<string>& IndexManager::FindBpTree_S(string filename) {
	map<string, BpTree<string> >::iterator it = this->BpTrees_S.find(filename);
	return it->second;
}

void IndexManager::InsertSuchKey(IndexInfo I, Addr p, value v) {
	string filename = Direction + I.tableName + "_" + I.colunmName + "_idx.dat";
	if (v.type == 50000) {
		BpTree<int>& Tree = FindBpTree_I(filename);
		Tree.InsertKey(v.intV, p);
	}
	else if (v.type == 90000) {
		BpTree<float>& Tree = FindBpTree_F(filename);
		Tree.InsertKey(v.floatV, p);
	}
	else if (v.type > 120000) {
		BpTree<string>& Tree = FindBpTree_S(filename);
		Tree.InsertKey(v.charV, p);
	}
}

set<Addr> IndexManager::FindSuchKey(STMT S) {
	string filename;
	int i;
	set<Addr> ans, temp1, temp2;
	for (i = 0; i < S.c_list->size(); i++) {
		condition C = S.c_list->at(i);
		if (!C.isIndex)
			continue;						//�������index��Լ���������Թ�
		//����ǰ�������temp2��Ϊ�м����
		temp2.clear();
		temp2 = ans;
		ans.clear();
		temp1.clear();
		filename = Direction + S.tableName + "_" + C.colunmName + "_idx.dat";
		if (C.type == 50000) {
			BpTree<int>& Tree = FindBpTree_I(filename);
			switch (C.op) {
			case 0: temp1 = Tree.FindEQ(C.key.intV);			break;
			case 1: temp1 = Tree.FindGreater(C.key.intV, true); break;
			case 2: temp1 = Tree.FindGreater(C.key.intV, false);break;
			case 3: temp1 = Tree.FindLess(C.key.intV, true);	break;
			case 4: temp1 = Tree.FindLess(C.key.intV, false);	break;
			case 5: temp1 = Tree.FindNEQ(C.key.intV);			break;
			default: 
			}
		}
		else if (C.type == 90000) {
			BpTree<float>& Tree = FindBpTree_F(filename);
			switch (C.op) {
			case 0: temp1 = Tree.FindEQ(C.key.floatV);				break;
			case 1: temp1 = Tree.FindGreater(C.key.floatV, true);	break;
			case 2: temp1 = Tree.FindGreater(C.key.floatV, false);	break;
			case 3: temp1 = Tree.FindLess(C.key.floatV, true);		break;
			case 4: temp1 = Tree.FindLess(C.key.floatV, false);		break;
			case 5: temp1 = Tree.FindNEQ(C.key.floatV);				break;
			default:
			}
		}
		else if (C.type > 120000) {
			BpTree<string>& Tree = FindBpTree_S(filename);
			switch (C.op) {
			case 0: temp1 = Tree.FindEQ(C.key.charV);				break;
			case 1: temp1 = Tree.FindGreater(C.key.charV, true);	break;
			case 2: temp1 = Tree.FindGreater(C.key.charV, false);	break;
			case 3: temp1 = Tree.FindLess(C.key.charV, true);		break;
			case 4: temp1 = Tree.FindLess(C.key.charV, false);		break;
			case 5: temp1 = Tree.FindNEQ(C.key.charV);				break;
			default:
			}
		}
		//temp1����һ��ɸѡ�����ĵ�ַ���ϣ�temp2��ǰ�漸���ܹ�ɸѡ�����ĵ�ַ���
		//��������ȡ����������ans����
		set<Addr>::iterator it;
		it = temp1.begin();
		while (it != temp1.end()) {
			if (temp2.find(*it) != temp2.end())
				ans.insert(*it);
			it++;
		}
	}
	return ans;
}

void IndexManager::DeleteSuchKey(IndexInfo I, Addr p, value v) {
	string filename = Direction + I.tableName + "_" + I.colunmName + "_idx.dat";
	if (v.type == 50000) {
		BpTree<int>& Tree = FindBpTree_I(filename);
		Tree.DeleteKey(v.intV, p);
	}
	else if (v.type == 90000) {
		BpTree<float>& Tree = FindBpTree_F(filename);
		Tree.DeleteKey(v.floatV, p);
	}
	else if (v.type > 120000) {
		BpTree<string>& Tree = FindBpTree_S(filename);
		Tree.DeleteKey(v.charV, p);
	}
}

void IndexManager::SaveAllBpTree(void) {
	map<string, BpTree<int> >::iterator it_i;
	for (it_i = BpTrees_I.begin(); it_i != BpTrees_I.end(); it_i++) {
		it_i->second.UpdateTree();
	}
	map<string, BpTree<float> >::iterator it_f;
	for (it_f = BpTrees_F.begin(); it_f != BpTrees_F.end(); it_f++) {
		it_f->second.UpdateTree();
	}
	map<string, BpTree<string> >::iterator it_s;
	for (it_s = BpTrees_S.begin(); it_s != BpTrees_S.end(); it_s++) {
		it_s->second.UpdateTree();
	}
	BpTrees_I.clear();
	BpTrees_F.clear();
	BpTrees_S.clear();
}