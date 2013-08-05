#ifndef _H_LEXER
#define _H_LEXER

#include "stdafx.h"
#include "Tag.h"
#include "FileMgr.h"

class Token
{
public:
	int tag;			// ����ôʶ�Ӧ�ı��
	Token();
	Token(int t);
	virtual string ToString();
	virtual string ToSign();
};

class Num : public Token
{
public:
	int value;			// �õ��ʵ�ֵ
	Num();
	Num(int v);
	string ToString();
};

class Double : public Token
{
public:
	double value;
	Double();
	Double(double v);
	string ToString();
};

class Word : public Token
{
public:
	string lexeme;		// ���ַ���������
	Word();
	Word(string s, int tag);
	string ToString();

	static Word *eql, *neq, *leq, *geq, *lss, *gre, *and, *or, *not;
	static Word *plus, *minus, *plusplus, *minusminus, *mult, *div, *assign, *semicn, *comma, *dot;
	static Word *assign_plus, *assign_minus, *assign_mult, *assign_div;
	static Word *lparent, *rparent, *lbrace, *rbrace;
	static Word *True, *False, *temp;
	static Word *note, *note_a, *note_b;
	static Word *null;
};

class Type : public Word {
public:
	int width;			// ���ڷ���洢�ռ�
	static Type *Double, *Int, *Func, *String;

	Type();
	Type(string s, int tag, int w);
	
	static bool numeric(Type* p);
	static Type* max(Type* l_type, Type* r_type);

};



class Lexer
{
public:
	int lineID;			// ��ǰ����
	char peek;			// ��һ��Ҫ��ȡ���ַ�
	int line;			// ��ǰ��ȡ���ʵ�����
	int nowWord;		// ��ǰ��ȡ�ĵ���

	FileMgr* fileManager;	// �ļ�������
	vector<Token*> wordStream;	// ������
	map<string, Word*> words;	// �洢��
	vector<int>	wordLine;		// ��������Ӧ������

	Lexer();			
	Token* Scan();		// ��ȡһ������
	void ReadCh();		// ��ȡһ���ַ�
	bool ReadCh(char ch);		// ��ȡ�ж��ַ��ǲ���ch
	void Reserve(Word* w);		// ���汣����
	void MakeWordStream();		// ���쵥����

	Token* ScanWord();			// ��ȡ��������һ������
	Token* RetrackWord(int num);	// ����ָ�������ĵ���

	string getString();			// ��ȡһ���ַ���

};
#endif