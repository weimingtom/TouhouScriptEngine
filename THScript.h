#ifndef _H_THSCRIPT
#define _H_THSCRIPT

#include "stdafx.h"
#include "SymbolTable.h"

class THScript
{
public:
	string fileName;			// �ű��ļ���
	string touhouScript;		// �ű�����
	string title;				// �ű�����
	string text;				// �ű�����
	string music;				// �ű�����
	string image;				// �ű���ͼ
	string background;			// �ű�����
	string player;				// �������
	string scriptVersion;		// �ű��汾��

	SymbolTable* top;			// �ű�������

	void SetValue(string varStr, string value);

	THScript();
};

#endif // !_H_THSCRIPT
