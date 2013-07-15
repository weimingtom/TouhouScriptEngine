#ifndef _H_Parser
#define _H_Parser

#include "stdafx.h"
#include "Lexer.h"
#include "Node.h"
#include "THScriptMgr.h"

class Parser
{
public:
	FileMgr* fileManager;		// �ļ�������
	THScriptMgr* scriptMgr;		// �ű�������
	Lexer* lexer;				// �ʷ�������
	Token* look;

	Parser();
	Parser(Lexer* lexer);

	void Move();				// �ӵ�����Ԥ��һ������
	void Retrack(int num);		// �˻�ָ���ĵ�����
	void Match(int t, int id);	// ƥ���ַ����ͣ�����ͬ�Ļ��򱨴�
	void Error(string s);		// ��ʾ������Ϣ

	void ScriptAnalysis();		// �ű��������
	void ScriptHeader();		// �ű�ͷ����ȡ
	void Varible();				// ��������
	int FuncHeader();			// ����ͷ
	Stmt* Block();				// �����
	Stmt* Stmts();				// �����
	Stmt* StmtOne();			// ���

};

#endif