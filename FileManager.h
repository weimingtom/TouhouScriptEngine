#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER

#include "stdafx.h"

class FileManager {
public:
	FileManager* Instance();
	vector<string> codeFile;
	ifstream inFile;
	ofstream outFile;

	void ReadCodeFile(string fileName);		// ��ȡĿ���ļ�
	char ReadCh();							// ��ȡһ���ַ�
	void Retrack(int t);					// ����t���ַ�
	int line,row;

	~FileManager();
protected:
	FileManager();

private:
	static FileManager* _instance;
};

#endif