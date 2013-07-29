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

	vector<string> scriptStream;	// �ű��ļ��������������Ԫʽ�����ᱻ����
	vector<QuadGroup*> scriptGroup;	// �ű������
	SymbolTable* symRoot;		// �ű�������

	QuadGroup* _lastGroup;		// ���һ�β����Ľű���
	int _streamIdx;				// �ű��ļ���λ��

	
	void AddToStream(string str);	// ����ַ�������������
	void SetValue(string varStr, string value);		// �趨�ű�����ֵ
	void TranslateScript();			// ����ű��м���

	string	_NextWord();				// ��ýű��ļ�������һ����
	string	_RetrackWord(int num);		// �˻ؽű��ļ���֮ǰ��ָ��������Ŀ
	void	_MakeNewQuad(string op, string arg_1, string arg_2, string obj, string lineID);		// �½�һ��ű�				
	THScript();
	~THScript();
};

#endif // !_H_THSCRIPT
