#include "RecordManager.h"

RecordManager::RecordManager(){
	this->Direction = "file/record/";
}

void RecordManager::CreateRecordFile(TableInfo T) {
	string filename;
	filename = Direction + T.tableName + "_rcd.dat";	//Direction��·�����������ļ�����
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
		return -1;						//�����ַ�������ļ�ĩβ���򷵻�״̬-1
	int Found = RS.FindRecord(p, R);	//�ҳ���Ӧ��¼
	//RS.Addp(p);						//��ַ����
	if (Found == 0)
		return 0;						//Found == 0˵���ü�¼�ѱ���ɾ�����򷵻�״̬0
	//�������������͸�value�Ĳ�ͬ������ֵ
	if (RS.TypeTable[I.indexID] == INT) {
		v.type = 50000;					//50000����Ŀ�����INT���͵Ķ���
		v.intV = R.Findi(I.indexID);
	}
	else if (RS.TypeTable[I.indexID] == FLOAT) {
		v.type = 90000;					//90000����Ŀ�����FLOAT���͵Ķ���
		v.floatV = R.Findf(I.indexID);
	}
	else if (RS.TypeTable[I.indexID] == STRING) {
		v.type == 130000;				//120000+����Ŀ�����STRING���͵Ķ���
		v.charV = R.Finds(I.indexID);
	}
	return 1;							//�ɹ����ؼ�ֵ������״̬1
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
			break;					//�Ѿ������¼�ļ�ĩβ�ˣ�����ѭ��
		if (Found == 0)
			continue;				//������¼�Ѿ�����ɾ����ֱ�Ӳ鿴��һ��
		else {						//������¼��Ч�����������
			bool flag = true;
			int i;
			for (i = 0; i < S.c_list->size(); i++) {
				if (R.Check(S.c_list->at(i)) == false) {
					flag = false;	//����һ�����������㣬ֱ����̭
					break;
				}
			}
			if (flag == true) {
				ans.insert(p);		//�������������ģ������ַ������������
			}
		}
		RS.Addp(p);					//��ַ����
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
			continue;				//�õ�ַ�ϵļ�¼��Ч��ֱ�Ӽ����һ��
		else {
			bool flag = true;
			int i;
			for (i = 0; i < S.c_list->size(); i++) {
				if (R.Check(S.c_list->at(i)) == false) {
					flag = false;	//����һ�����������㣬ֱ����̭
					break;
				}
			}
			if (flag == true) {
				ans.insert(*it);		//�������������ģ������ַ������������
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


void RecordManager::LoadAllRecordSet(vector<TableInfo> Ts) {
	int i;
	for (i = 0; i < Ts.size(); i++) {
		TableInfo T = Ts.at(i);
		string filename = Direction + T.tableName + "_rcd.dat";
		RecordSet NewRS = RecordSet(filename);
		this->Total_Record.insert(pair<string, RecordSet>(filename, NewRS));
	}
}