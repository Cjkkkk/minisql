#include <iostream>
#include <string>
#include "Buffer.h"
#include "Record.h"
#include "BpTree2.h"
using namespace std;
Buffer blocks;

void previous_test(void) {
	//vector<int> from_catolog;
	//from_catolog.push_back(90000);
	//from_catolog.push_back(50000);
	//from_catolog.push_back(130000);
	////TypeTable: float, int, string
	//RecordSet RS("../Record.dat", from_catolog);
	//RS.LoadTestRecord("../Test.txt");
	//RS.DeleteRecord({ 2, 1 });
	//RS.DeleteRecord({ 1, 2 });
	//RS.LoadTestRecord("../Test1.txt");
	//BpTree<int>Tree = BpTree<int>("../Index_int.dat", INT);
	//int i;
	//for (i = 1; i <= 100000; i++) {
	//	Tree.InsertKey(i, { 1, i });
	//	if(i % 1000 == 0)
	//		cout << i << ": Done!" << endl;
	//}
	//BpTree<string> Tree = BpTree<string>("../Index.dat", STRING);
	//Tree.InsertKey("Brand",		{ 1, 0 });
	//Tree.InsertKey("Calif",		{ 1, 1 });
	//Tree.InsertKey("Einst",		{ 1, 2 });
	//Tree.InsertKey("Elsaid",	{ 1, 3 });
	//Tree.InsertKey("Crick",		{ 1, 4 });
	//Tree.InsertKey("Gold",		{ 1, 5 });
	//Tree.InsertKey("Katz",		{ 1, 6 });
	//Tree.InsertKey("Mozart",	{ 1, 7 });
	//Tree.InsertKey("Singh",		{ 1, 8 });
	//Tree.InsertKey("Kim",		{ 1, 9 });
	//Tree.InsertKey("Srin",		{ 1, 10 });
	//Tree.InsertKey("Wu",		{ 1, 11 });
	//Tree.InsertKey("Adams",		{ 1, 12 });
	//Tree.InsertKey("Lamport",	{ 1, 13 });
	//---------------------------------------
	//Tree.DeleteKey("Adams", { 1, 12 });
	//Tree.DeleteKey("Crick", { 1, 4 });
	//Tree.DeleteKey("Wu",	{ 1, 11 });
	//Tree.DeleteKey("Kim",	{ 1, 9 });
	//Tree.DeleteKey("Elsaid",{ 1, 3 });
	//Tree.DeleteKey("Brand", { 1, 0 });
	//Tree.DeleteKey("Gold",	{ 1, 5 });
	//Tree.DeleteKey("Srin",	{ 1, 10 });
	//Tree.DeleteKey("Calif", { 1, 1 });
	//Tree.DeleteKey("Einst", { 1, 2 });
	//Tree.DeleteKey("Mozart",{ 1, 7 });
	//Tree.DeleteKey("Lamport",{1, 13 });
	//Tree.DeleteKey("Katz",	{ 1, 6 });
	//Tree.DeleteKey("Singh", { 1, 8 });
	//vector<Addr> ans;
	//ans = Tree.FindLessGreater("Lamport", "Srin",false,  true);
	//Tree.UpdateTree();
	//blocks.SaveDataAll();
	//Tree.Test("../Index_int.dat");
	//RS.UpdateSet();
	//blocks.SaveDataAll();
	//RS.Test("../Record.dat");
}

int main(void) {
	vector<int> from_catolog;
	from_catolog.push_back(50000);
	from_catolog.push_back(90000);
	from_catolog.push_back(130000);
	//TypeTable: float, int, string
	RecordSet RS("../Record_10.dat", from_catolog);
	RS.LoadTestRecord("../RT_10.txt");
	RS.UpdateSet();
	RS.DisposeSet();
	blocks.SaveDataAll();
	system("pause");
	return 0;
}