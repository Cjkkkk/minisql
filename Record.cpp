#include "Record.h"
#include <iostream>
#include <fstream>
#include "./Buffer.h"
#include <string.h>
extern Buffer blocks;
//extern enum DataType;

Record::Record(void) {
	this->RecordState = VALID;
	this->self = { -1, -1 };
}

int Record::Findi(int c) {
	int i;
	for (i = 0; i < KI.size(); i++) {
		if (KI[i].Column == c)break;
	}
	if (i < KI.size())
		return KI[i].Value;
	else {
		cout << "Cannot Find this Column!" << endl;
		return -1;
	}
}

float Record::Findf(int c) {
	int i;
	for (i = 0; i < KF.size(); i++) {
		if (KF[i].Column == c)break;
	}
	if (i < KF.size())
		return KF[i].Value;
	else {
		cout << "Cannot Find this Column!" << endl;
		return -1.0;
	}
}

string Record::Finds(int c) {
	int i;
	for (i = 0; i < KS.size(); i++) {
		if (KS[i].Column == c)break;
	}
	if (i < KS.size())
		return KS[i].Value;
	else {
		cout << "Cannot Find this Column!" << endl;
		return "";
	}
}

bool Record::Check(condition C) {
	if (C.type == 50000) {
		int Record_Key = this->Findi(C.colunmID);
		switch (C.op) {
		case 0: return (Record_Key == C.key.intV);
		case 1: return (Record_Key >= C.key.intV);
		case 2: return (Record_Key > C.key.intV);
		case 3: return (Record_Key <= C.key.intV);
		case 4: return (Record_Key < C.key.intV);
		case 5: return (Record_Key != C.key.intV);
		default: return false;
		}
	}
	else if (C.type == 90000) {
		float Record_Key = this->Findf(C.colunmID);
		switch (C.op) {
		case 0: return (Record_Key == C.key.floatV);
		case 1: return (Record_Key >= C.key.floatV);
		case 2: return (Record_Key > C.key.floatV);
		case 3: return (Record_Key <= C.key.floatV);
		case 4: return (Record_Key < C.key.floatV);
		case 5: return (Record_Key != C.key.floatV);
		default: return false;
		}
	}
	else if (C.type > 120000) {
		string Record_Key = this->Finds(C.colunmID);
		switch (C.op) {
		case 0: return (Record_Key == C.key.charV);
		case 1: return (Record_Key >= C.key.charV);
		case 2: return (Record_Key > C.key.charV);
		case 3: return (Record_Key <= C.key.charV);
		case 4: return (Record_Key < C.key.charV);
		case 5: return (Record_Key != C.key.charV);
		default: return false;
		}
	}
	else {
		return false;
	}
}

RecordSet::RecordSet(string RecordFileName, vector<int> Cato_TypeTable) {
	int int_n = 0, float_n = 0, string_n = 0;
	int i;
	this->Columns = Cato_TypeTable.size();
	this->Record_FileName = RecordFileName;
	this->FreeAddr.clear();
	//this->FirstFreeRecord = { -1, -1 };
	this->Top = { -1, -1 };
	for (i = 0; i < Cato_TypeTable.size(); i++) {
		if (Cato_TypeTable[i] == 50000) {
			int_n++;
			this->TypeTable.push_back(INT);
		}
		else if (Cato_TypeTable[i] == 90000) {
			float_n++;
			this->TypeTable.push_back(FLOAT);
		}
		else if (Cato_TypeTable[i] > 120000) {
			string_n++;
			this->TypeTable.push_back(STRING);
		}
	}
	this->RECORD_SIZE = sizeof(char) +
		int_n * sizeof(int) +
		float_n * sizeof(float) +
		string_n * sizeof(string);
	blocks.CreateFile(RecordFileName);
	cout << "RECORD_SIZE: " << this->RECORD_SIZE << endl;
	cout << "MAX_RECORD: " << MAX_RECORD << endl; 
}

RecordSet::RecordSet(std::string RecordFileName) {
	int i, s;
	this->Record_FileName = RecordFileName;
	int BlockNum = blocks.Allocate(RecordFileName, 0);
	char* p = blocks.buffer[BlockNum].data;
	memcpy(reinterpret_cast<char*>(&this->Columns), p, sizeof(int));
	p += sizeof(int);
	memcpy(reinterpret_cast<char*>(&this->RECORD_SIZE), p, sizeof(int));
	p += sizeof(int);
	memcpy(reinterpret_cast<char*>(&this->Top.BlockNum), p, sizeof(int));
	p += sizeof(int);
	memcpy(reinterpret_cast<char*>(&this->Top.FileOff), p, sizeof(int));
	p += sizeof(int);
	memcpy(reinterpret_cast<char*>(&s), p, sizeof(int));			//FreeAddr�����size()
	p += sizeof(int);
	for (i = 0; i < s; i++) {
		Addr New;
		memcpy(reinterpret_cast<char*>(&New.BlockNum), p, sizeof(int));
		p += sizeof(int);
		memcpy(reinterpret_cast<char*>(&New.FileOff), p, sizeof(int));
		p += sizeof(int);
		this->FreeAddr.push_back(New);
	}
	for (i = 0; i < this->Columns; i++) {
		char type;
		memcpy(&type, p, sizeof(char));
		p += sizeof(char);
		this->TypeTable.push_back(type);
	}
	cout << "Rebuild Success!" << endl;
	cout << "RECORD_SIZE: " << this->RECORD_SIZE << endl;
	cout << "MAX_RECORD: " << MAX_RECORD << endl;
}

void RecordSet::DisposeSet(void) {
	blocks.DeleteFile(this->Record_FileName);
}

void RecordSet::UpdateSet(void) {
	int i, s;
	s = this->FreeAddr.size();
	int BlockNum = blocks.Find(this->Record_FileName, 0);
	if (BlockNum == -1) {
		BlockNum = blocks.Allocate(this->Record_FileName, 0);
	}
	char* p = blocks.buffer[BlockNum].data;
	memcpy(p, reinterpret_cast<char*>(&this->Columns), sizeof(int));
	p += sizeof(int);
	memcpy(p, reinterpret_cast<char*>(&this->RECORD_SIZE), sizeof(int));
	p += sizeof(int);
	memcpy(p, reinterpret_cast<char*>(&this->Top.BlockNum), sizeof(int));
	p += sizeof(int);
	memcpy(p, reinterpret_cast<char*>(&this->Top.FileOff), sizeof(int));
	p += sizeof(int);
	memcpy(p, reinterpret_cast<char*>(&s), sizeof(int));
	p += sizeof(int);
	for (i = 0; i < s; i++) {
		memcpy(p, reinterpret_cast<char*>(&this->FreeAddr[i].BlockNum), sizeof(int));
		p += sizeof(int);
		memcpy(p, reinterpret_cast<char*>(&this->FreeAddr[i].FileOff), sizeof(int));
		p += sizeof(int);
	}
	for (i = 0; i < this->Columns; i++) {
		memcpy(p, &this->TypeTable[i], sizeof(char));
		p += sizeof(char);
	}
	blocks.Lock(BlockNum);
}

int RecordSet::FindRecord(Addr p, Record& R) {
	int i;
	if (p.BlockNum > this->Top.BlockNum || (p.BlockNum == this->Top.BlockNum && p.FileOff > this->Top.FileOff))
		return -1;					//��ַ���ܳ����ļ����һ�м�¼�ĵ�ַ
	R.self = p;						//��¼�ṹ�а����Լ���λ�ã����㴫��
	int BlockNum = blocks.Find(this->Record_FileName, p.BlockNum);
	if (BlockNum == -1) {
		BlockNum = blocks.Allocate(this->Record_FileName, p.BlockNum);
	}
	char* Src = blocks.buffer[BlockNum].data + p.FileOff*this->RECORD_SIZE;
	memcpy(&R.RecordState, Src, sizeof(char));
	Src += sizeof(char);
	for (i = 0; i < this->Columns; i++) {
		if (this->TypeTable[i] == INT) {
			Keyi Newi(i);
			memcpy(reinterpret_cast<char*>(&Newi.Value), Src, sizeof(int));
			Src += sizeof(int);
			R.KI.push_back(Newi);
		}
		else if (this->TypeTable[i] == FLOAT) {
			Keyf Newf(i);
			memcpy(reinterpret_cast<char*>(&Newf.Value), Src, sizeof(float));
			Src += sizeof(float);
			R.KF.push_back(Newf);
		}
		else if (this->TypeTable[i] == STRING) {
			char buf[100];
			memcpy(buf, Src, sizeof(string));
			Src += sizeof(string);
			Keys News(i);
			News.Value = buf;
			R.KS.push_back(News);
		}
	}
	int ret = (R.RecordState == VALID) ? 1 : 0;
	return ret;
}


void RecordSet::LoadTestRecord(string filename) {
	int i, count = 0;
	ifstream in(filename);
	while (!in.eof()) {
		Record R;
		in >> R.RecordState >> R.self.BlockNum >> R.self.FileOff;
		for (i = 0; i < this->Columns; i++) {
			if (this->TypeTable[i] == INT) {
				Keyi Newi(i);
				in >> Newi.Value;
				R.KI.push_back(Newi);
			}
			else if (this->TypeTable[i] == FLOAT) {
				Keyf Newf(i);
				in >> Newf.Value;
				R.KF.push_back(Newf);
			}
			else if (this->TypeTable[i] == STRING) {
				Keys News(i);
				in >> News.Value;
				R.KS.push_back(News);
			}
		}
		Addr p = this->InsertRecord(R);
		count++;
		if (count % 10000 == 0) {
			cout << count << " records: Done!" << endl;
		}
	}

	in.close();
}

void RecordSet::Test(string filename) {
	char buf[135];
	int i, j = 1, k = 0;
	vector<Record> Records;
	ifstream bin;
	bin.open(filename, ios::in | ios::binary);
	while (1) {
		if (k % MAX_RECORD == 0) {
			bin.seekg(j*BLOCK_SIZE);
			j++;
		}
		k++;
		Record R;
		bin.read(&R.RecordState, sizeof(char));
		for (i = 0; i < this->Columns; i++) {
			if (this->TypeTable[i] == INT) {
				Keyi Newi(i);
				bin.read(reinterpret_cast<char*>(&Newi.Value), sizeof(int));
				R.KI.push_back(Newi);
			}
			else if (this->TypeTable[i] == FLOAT) {
				Keyf Newf(i);
				bin.read(reinterpret_cast<char*>(&Newf.Value), sizeof(float));
				R.KF.push_back(Newf);
			}
			else if (this->TypeTable[i] == STRING) {
				Keys News(i);
				bin.read(buf, sizeof(string));
				News.Value = buf;
				R.KS.push_back(News);
			}
		}
		if (bin.eof())
			break;
		Records.push_back(R);
	}
	bin.close();
	Records.clear();
}

void RecordSet::SaveRecord(Record& R) {
	int i;
	int in = 0, fn = 0, sn = 0;
	int BlockNum = blocks.Find(this->Record_FileName, R.self.BlockNum);
	if (BlockNum == -1) {
		BlockNum = blocks.Allocate(this->Record_FileName, R.self.BlockNum);
	}
	char* Dst = blocks.buffer[BlockNum].data + R.self.FileOff*this->RECORD_SIZE;
	memcpy(Dst, &R.RecordState, sizeof(char));
	Dst += sizeof(char);
	for (i = 0; i < this->Columns; i++) {
		if (this->TypeTable[i] == INT) {
			memcpy(Dst, reinterpret_cast<char*>(&R.KI[in++].Value), sizeof(int));
			Dst += sizeof(int);
		}
		else if (this->TypeTable[i] == FLOAT) {
			memcpy(Dst, reinterpret_cast<char*>(&R.KF[fn++].Value), sizeof(float));
			Dst += sizeof(float);
		}
		else if (this->TypeTable[i] == STRING) {
			memcpy(Dst, R.KS[sn++].Value.c_str(), sizeof(string));
			Dst += sizeof(string);
		}
	}
	blocks.Dirt(BlockNum);
	blocks.UnLock(BlockNum);
}

Addr RecordSet::InsertRecord(Record& R) {
	if (!this->FreeAddr.empty()) {
		//���Դӿ�������ȡ������ż�¼
		Record Q;
		Addr temp;
		do {
			temp = this->FreeAddr.back();
			this->FreeAddr.pop_back();
		} while (!Lessp(temp, this->Top.BlockNum, this->Top.FileOff) && !this->FreeAddr.empty());
		//��ֹѭ��ʱ��������������ҵ��˱�TopС�ĵ�ַ����FreeAddr�����˶�û��
		if (Lessp(temp, this->Top.BlockNum, this->Top.FileOff)) {
			int not_important = this->FindRecord(temp, Q);
			Q = R;
			Q.RecordState = VALID;						//ǿ��Q�Ѿ�������Ч��
			Q.self = temp;
			this->SaveRecord(Q);
			return temp;
		}
	}
	//�����Ϳյ�����͵�һ��if�����FreeAddr�Ϳյ�����������洦��
	if(this->FreeAddr.empty()) {
		Addp(this->Top);
		R.self = this->Top;
		R.RecordState = VALID;
		this->SaveRecord(R);
		return this->Top;
	}
}

void RecordSet::DeleteRecord(Addr p) {
	Record R, Q;
	if (p.FileOff >= MAX_RECORD || p.FileOff < 0)
		return;
	if (p.BlockNum > this->Top.BlockNum || p.BlockNum <= 0)
		return;
	int Found = this->FindRecord(p, R);
	if (Found != 1 || R.RecordState == EMPTY)
		return;
	R.RecordState = EMPTY;
	if (Equalp(p, Top.BlockNum, Top.FileOff)) {
		do {										//�䶯Top��ַ
			Subp(this->Top);
		} while (!this->FindRecord(this->Top, Q) && !Equalp(this->Top, -1, -1));
		//����ѭ��ʱ������������ҵ��˵�һ��VALID�ļ�¼�������ļ��ǿյ�
	}
	else {
		this->FreeAddr.push_back(p);				//�䶯��������
	}
	this->SaveRecord(R);
}

void RecordSet::DeleteRecord(set<Addr> ps) {
	set<Addr>::iterator it;
	for (it = ps.begin(); it != ps.end(); it++) {
		this->DeleteRecord(*it);
	}
}

bool RecordSet::Equalp(Addr p, int BlockNum, int FileOff) {
	return (p.BlockNum == BlockNum && p.FileOff == FileOff);
}

bool RecordSet::Greaterp(Addr p, int BlockNum, int FileOff) {
	if (p.BlockNum > BlockNum)
		return true;
	if (p.BlockNum == BlockNum && p.FileOff > FileOff)
		return true;
	return false;
}

bool RecordSet::Lessp(Addr p, int BlockNum, int FileOff) {
	if (p.BlockNum < BlockNum)
		return true;
	if (p.BlockNum == BlockNum && p.FileOff < FileOff)
		return true;
	return false;
}

void RecordSet::Addp(Addr& p) {
	if (Equalp(p, -1, -1)) {
		p.BlockNum = 1;
		p.FileOff = 0;
	}
	else if(p.FileOff == MAX_RECORD-1){
		p.FileOff = 0;
		p.BlockNum++;
	}
	else {
		p.FileOff++;
	}
}

void RecordSet::Subp(Addr& p) {
	if (Equalp(p, 1, 0)) {
		p.BlockNum = -1;
		p.FileOff = -1;
	}
	else if (p.FileOff == 0) {
		p.FileOff = MAX_RECORD - 1;
		p.BlockNum--;
	}
	else {
		p.FileOff--;
	}
}