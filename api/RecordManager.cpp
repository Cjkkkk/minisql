#include "RecordManager.h"

RecordManager::RecordManager(){
	this->Direction = "";
}

void RecordManager::CreateRecordFile(TableInfo T) {
	string filename;
	filename = Direction + T.tableName + "_rcd.dat";	//Direction是路径，后面是文件名称
	RecordSet NewRS = RecordSet(filename, T.type);
	this->Total_Record.insert(pair<string, RecordSet>(filename, NewRS));
}

void RecordManager::DropRecordFile(TableInfo T) {
	string filename;
	filename = Direction + T.tableName + "_rcd.dat";
	map<string, RecordSet>::iterator it = this->Total_Record.find(filename);
	it->second.DisposeSet();
	it = this->Total_Record.erase(it);
}

RecordSet& RecordManager::FindRecordSet(string filename) {
	map<string, RecordSet>::iterator it = this->Total_Record.find(filename);
	return it->second;
}

int RecordManager::ReturnKP(IndexInfo I, Addr p, value& v) {
	int state;
	Record R;
	string filename = Direction + I.tableName + "_rcd.dat";
	RecordSet& RS = FindRecordSet(filename);
	if (RS.Greaterp(p, RS.Top.BlockNum, RS.Top.FileOff))
		return -1;						//如果地址超出了文件末尾，则返回状态-1
	int Found = RS.FindRecord(p, R);	//找出对应记录
	//RS.Addp(p);						//地址自增
	if (Found == 0)
		return 0;						//Found == 0说明该记录已被软删除，则返回状态0
	//根据索引的类型给value的不同分量赋值
	if (RS.TypeTable[I.indexID] == INT) {
		v.type = 50000;					//50000是项目顶层对INT类型的定义
		v.intV = R.Findi(I.indexID);
	}
	else if (RS.TypeTable[I.indexID] == FLOAT) {
		v.type = 90000;					//90000是项目顶层对FLOAT类型的定义
		v.floatV = R.Findf(I.indexID);
	}
	else if (RS.TypeTable[I.indexID] == STRING) {
		v.type == 130000;				//120000+是项目顶层对STRING类型的定义
		v.charV = R.Finds(I.indexID);
	}
	return 1;							//成功返回键值，返回状态1
}

set<Addr> RecordManager::FindSuchRecord(STMT S) {
	set<Addr> ans;
	Addr p = { 1, 0 };
	Record R;
	string filename = Direction + S.tableName + "_rcd.dat";
	RecordSet& RS = this->FindRecordSet(filename);
	while (1) {
		int Found = RS.FindRecord(p, R);
		if (Found == -1)
			break;					//已经到达记录文件末尾了，跳出循环
		if (Found == 0)
			continue;				//这条记录已经被软删除，直接查看下一条
		else {						//这条记录有效，继续检查它
			bool flag = true;
			int i;
			for (i = 0; i < S.c_list->size(); i++) {
				if (R.Check(S.c_list->at(i)) == false) {
					flag = false;	//若有一个条件不满足，直接淘汰
					break;
				}
			}
			if (flag == true) {
				ans.insert(p);		//满足所有条件的，将其地址插入结果集合中
			}
		}
		RS.Addp(p);					//地址自增
	}
	return ans;
}

set<Addr> RecordManager::FindSuchRecord(STMT S, set<Addr>ps) {
	set<Addr> ans;
	set<Addr>::iterator it;
	Record R;
	string filename = Direction + S.tableName + "_rcd.dat";
	RecordSet& RS = this->FindRecordSet(filename);
	for (it = ps.begin(); it != ps.end(); it++) {
		int Found = RS.FindRecord(*it, R);
		if (Found != 1)
			continue;				//该地址上的记录无效，直接检查下一条
		else {
			bool flag = true;
			int i;
			for (i = 0; i < S.c_list->size(); i++) {
				if (R.Check(S.c_list->at(i)) == false) {
					flag = false;	//若有一个条件不满足，直接淘汰
					break;
				}
			}
			if (flag == true) {
				ans.insert(*it);		//满足所有条件的，将其地址插入结果集合中
			}
		}
	}
	return ans;
}

void RecordManager::InsertSuchRecord(STMT S, Addr& p) {
	string filename = Direction + S.tableName + "_rcd.dat";
	RecordSet& RS = this->FindRecordSet(filename);
	int column;
	Record R;
	for (column = 0; column < S.v_list->size(); column++) {
		struct value v = S.v_list->at(column);
		if (v.type == 50000) {
			Keyi Newi(column);
			Newi.Value = v.intV;
			R.KI.push_back(Newi);
		}
		else if (v.type == 90000) {
			Keyf Newf(column);
			Newf.Value = v.floatV;
			R.KF.push_back(Newf);
		}
		else if (v.type > 120000) {
			Keys News(column);
			News.Value = v.charV;
			R.KS.push_back(News);
		}
	}
	R.RecordState = VALID;
	p = RS.InsertRecord(R);
}

void RecordManager::PrintRecord(STMT S, set<Addr> ps) {
	string filename = Direction + S.tableName + "_rcd.dat";
	RecordSet& RS = this->FindRecordSet(filename);
	Record R;
	cout << "To be done..." << endl;
}

void RecordManager::DeleteSuchRecord(STMT S, set<Addr> ps) {
	string filename = Direction + S.tableName + "_rcd.dat";
	RecordSet& RS = this->FindRecordSet(filename);
	Record R;
	RS.DeleteRecord(ps);
}

set<Addr> RecordManager::FindandDelete(STMT S) {
	set<Addr> target = this->FindSuchRecord(S);
	this->DeleteSuchRecord(S, target);
	return target;
}

set<Addr> RecordManager::FindandDelete(STMT S, set<Addr>ps) {
	set<Addr> target = this->FindSuchRecord(S, ps);
	this->DeleteSuchRecord(S, target);
	return target;
}

void RecordManager::FindandPrint(STMT S) {
	set<Addr> target = this->FindSuchRecord(S);
	this->PrintRecord(S, target);
}

void RecordManager::FindandPrint(STMT S, set<Addr>ps) {
	set<Addr> target = this->FindSuchRecord(S, ps);
	this->PrintRecord(S, target);
}

void RecordManager::SaveAllRecordSet(void) {
	map<string, RecordSet>::iterator it;
	for (it = this->Total_Record.begin(); it != this->Total_Record.end(); it++) {
		it->second.UpdateSet();
	}
	this->Total_Record.clear();
}