#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER

#include "stdafx.h"

class FileMgr {
public:
	vector<string> codeFile;
	string fileName;			// �ű��ļ���
	ifstream inFile;
	ofstream outFile;

	FileMgr* Instance();
	void ReadCodeFile(string fileName);		// ��ȡĿ���ļ�
	char ReadCh();							// ��ȡһ���ַ�
	void Retrack(int t);					// ����t���ַ�
	int line,row;

	~FileMgr();
protected:
	FileMgr();

private:
	static FileMgr* _instance;
};

#endif