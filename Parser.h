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
	SymbolTable* symTop;		// ��ǰ������ű�
	Lexer* lexer;				// �ʷ�������
	Token* look;

	Parser();
	Parser(Lexer* lexer);

	void Move();				// �ӵ�����Ԥ��һ������
	void Retrack(int num);		// �˻�ָ���ĵ�����
	void Match(int t, int id);	// ƥ���ַ����ͣ�����ͬ�Ļ��򱨴�
	void Error(string s);		// ��ʾ������Ϣ

	void ScriptType();			// �ű�����
	void ScriptAnalysis();		// �ű��������
	void ScriptHeader();		// �ű�ͷ����ȡ
	void Varible();				// ��������
	int FuncHeader();			// ����ͷ
	Stmt* Block();				// �����
	Stmt* Stmts();				// �����
	Stmt* StmtOne();			// ���
	Stmt* Assign();				// ��ֵ���

	Expr* _bool();				// ���������
	Expr* _join();
	Expr* _equality();			
	Expr* _rel();	
	Expr* _exprOne();			
	Expr* _term();
	Expr* _unary();
	Expr* _factor();

};

#endif