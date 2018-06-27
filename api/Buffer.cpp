#include "Buffer.h"
#include <fstream>
#include <iostream>
#include <string.h>
Block::Block(void) {
	this->BlockClear();
}

void Block::BlockClear(void) {
	this->FileName = "";
	this->FileOff = -1;
	memset(this->data, 0, sizeof(this->data));
}

void Block::BlockClear_Back(void) {
	memset(this->data, 0, sizeof(this->data));
	this->WriteFile();
	this->FileName = "";
	this->FileOff = -1;
}

void Block::BlockSet(string FileName, int FileOff) {
	this->FileName = FileName;
	this->FileOff = FileOff;
}

void Block::ReadFile(void) {
	ifstream in;
	in.open(this->FileName, ios::in | ios::binary);
	if (in.bad()) {
		cout << this->FileName << ": No such a file!" << endl;
		system("pause");
		exit(1);
	}
	in.seekg(this->FileOff * BLOCK_SIZE);
	//cout << in.tellg() << endl;
	in.read(reinterpret_cast<char*> (this->data), BLOCK_SIZE);
	in.close();
}

void Block::WriteFile(void) {
	ofstream out;
	if (out.bad()) {
		cout << this->FileName << ": No such a file!" << endl;
		system("pause");
		exit(1);
	}
	out.open(this->FileName, ios::out | ios::in | ios::binary);
	out.seekp(this->FileOff * BLOCK_SIZE);
	//cout << out.tellp() << endl;
	out.write(reinterpret_cast<char*>(this->data), BLOCK_SIZE);
	out.close();
}

Buffer::Buffer(void){
	int i;
	for (i = 0; i < MAX_BLOCKS; i++) {
		this->Empty_Block.push_back(i);
		this->UnDirt(i);
		this->UnLock(i);
	}
	this->Occupy_Block.clear();
}

list<int>::iterator Buffer::Find(int BlockNum) {		//���ؿ���ռ�������е�λ��
	list<int>::iterator it;
	for (it = this->Occupy_Block.begin(); it != this->Occupy_Block.end() && *it != BlockNum; it++);
	return it;
}

int Buffer::Find(string FileName, int FileOff) {		//���ض�Ӧ���
	int pos;
	list<int>::iterator it;
	for (it = this->Occupy_Block.begin(); it != this->Occupy_Block.end(); it++) {
		if (this->buffer[*it].FileName == FileName && this->buffer[*it].FileOff == FileOff) {
			pos = *it;
			this->Update(it);						//�����������
			return pos;
		}
	}
	return -1;
}

int Buffer::Allocate(string FileName, int FileOff) {
	int pos;
	if (this->Empty_Block.empty()) {
		//û�пտ飬ֻ�ܸ���LRUԭ���滻
		list<int>::iterator it;
		for (it = this->Occupy_Block.begin(); it != this->Occupy_Block.end(); it++) {
			if (Pin[*it] == 0)	break;				//�ҵ���Զ�޸���û�������Ŀ�
		}
		if (it == this->Occupy_Block.end()) {
			cout << "Blocks are not enough!" << endl;
			system("pause");
			exit(1);
		}
		if (Dirty[*it] == 1) {
			this->buffer[*it].WriteFile();			//���޸ģ���д�ش���
		}
		pos = *it;
		it = this->Occupy_Block.erase(it);
	}
	else {
		//���пտ飬ȡ������
		pos = this->Empty_Block.front();
		this->Empty_Block.pop_front();
	}
	this->buffer[pos].BlockClear();					//��ոÿ�
	this->buffer[pos].BlockSet(FileName, FileOff);
	this->buffer[pos].ReadFile();
	this->Occupy_Block.push_back(pos);
	this->UnDirt(pos);
	this->Lock(pos);							//����������һ�θ��µ���֮ǰ���ñ��滻��ȥ
	return pos;
}

void Buffer::Update(list<int>::iterator it) {
	int pos = *it;
	it = this->Occupy_Block.erase(it);
	this->Occupy_Block.push_back(pos);
	this->Dirt(pos);
	this->UnLock(pos);							//������棬���Ա��滻��ȥ
}

void Buffer::LoadData(int BlockNum) {
	this->buffer[BlockNum].ReadFile();
}

void Buffer::SaveData(int BlockNum) {
	this->buffer[BlockNum].WriteFile();
	this->UnDirt(BlockNum);
}

void Buffer::SaveDataAll(void) {
	list<int>::iterator it;
	for (it = this->Occupy_Block.begin(); it != this->Occupy_Block.end(); it++) {
		this->SaveData(*it);
	}
}

void Buffer::Lock(int BlockNum) {
	this->Pin[BlockNum] = 1;
}

void Buffer::UnLock(int BlockNum) {
	this->Pin[BlockNum] = 0;
}

void Buffer::Dirt(int BlockNum) {
	this->Dirty[BlockNum] = 1;
}

void Buffer::UnDirt(int BlockNum) {
	this->Dirty[BlockNum] = 0;
}

void Buffer::Free(int BlockNum) {
	int pos;
	list<int>::iterator it;
	it = this->Find(BlockNum);
	if (it != this->Occupy_Block.end()) {			//B�ڱ�ռ��������
		pos = *it;
		it = this->Occupy_Block.erase(it);			//��ռ�ÿ�������ɾȥ
		this->Empty_Block.push_back(pos);			//��ӽ��տ�������
		this->buffer[pos].BlockClear_Back();
		this->UnDirt(pos);
		this->UnLock(pos);
	}
}

void Buffer::FreeAll(void) {
	int pos;
	list<int>::iterator it;
	for (it = this->Occupy_Block.begin(); it != this->Occupy_Block.end();) {
		pos = *it;
		it = this->Occupy_Block.erase(it);
		this->Empty_Block.push_back(pos);
		this->buffer[pos].BlockClear_Back();
		this->Dirty[pos] = this->Pin[pos] = 0;
	}
}

void Buffer::CreateFile(string filename) {
	ofstream out;
	out.open(filename);
	if (out.good()) {
		out.close();
	}
	else {
		cout << "Create file " << filename << " failed!" << endl;
		system("pause");
		exit(1);
	}
}

void Buffer::DeleteFile(string filename) {
	int pos;
	list<int>::iterator it;
	for (it = this->Occupy_Block.begin(); it != this->Occupy_Block.end();) {
		if (this->buffer[*it].FileName == filename) {
			pos = *it;
			this->buffer[pos].BlockClear();				//�����ļ���buffer�еĿ�ȫ�����
			this->UnDirt(pos);
			this->UnLock(pos);
			it = this->Occupy_Block.erase(it);
			this->Empty_Block.push_back(pos);
		}
		else {
			it++;
		}
	}
	if (remove(filename.c_str()) != 0) {
		cout << "Delete file " << filename << " failed!" << endl;
		system("pause");
		exit(1);
	}
}