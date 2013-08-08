#ifndef _H_THSCRIPT
#define _H_THSCRIPT

#include "stdafx.h"
#include "SymbolTable.h"
#include "QuadGroup.h"

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

	vector<QuadGroup*>	scriptGroup;	// �ű������
	SymbolTable*		symRoot;		// �ű�������

	THScript();
	THScript(const THScript& rhs);
	THScript& operator= (const THScript& rhs);
	~THScript();

	void SetValue(string varStr, string value);		// �趨�ű�����ֵ
	
};
#endif // !_H_THSCRIPT
