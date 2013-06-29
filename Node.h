#ifndef _H_NODE
#define _H_NODE

#include "stdafx.h"
#include "Lexer.h"

/// ����֮Դ�������ڵ�
//////////////////////////////////////////////////////////////////////////

class Node {
public:
	int lexline;
	static int labels;
	
	Node();
	Node(int l);
	void error(string s);
	int newlabel();

	~Node();
};

/// ���ʽ����
//////////////////////////////////////////////////////////////////////////

class Expr : public Node {
public:
	Token* op;
	Type* type;

	Expr();
	Expr(Token* token, Type* type);

	virtual Expr* gen();
	virtual Expr* reduce();
	virtual void jumping(int t, int f);
	void emitjumps(string test, int t, int f);
	virtual string ToString();

	~Expr();
};

/// ��ַ
//////////////////////////////////////////////////////////////////////////

class Id : public Expr {
public:
	int offset;
	Id();
	Id(Word* id, Type* type, int l_offset);
};

/// ������
//////////////////////////////////////////////////////////////////////////

class Op : public Id {
public:
	Op();
	Op(Token* token, Type* type);

	Expr* reduce();

	~Op();
};

/// ˫Ŀ�����
//////////////////////////////////////////////////////////////////////////

class Arith : public Op {
public:
	Expr *l_expr, *r_expr;
	Arith();
	Arith(Token* token, Expr* l_expr, Expr* r_expr);

	Expr* gen();
	string ToString();

	~Arith();
};

/// ��Ŀ�����
//////////////////////////////////////////////////////////////////////////

class Unary : public Op {
public:
	Expr *expr;
	Unary();
	Unary(Token* token, Expr* expr);

	Expr* gen();
	string ToString();

	~Unary();
};

/// ��ʱ����
//////////////////////////////////////////////////////////////////////////

class Temp : public Expr {
public:
	static int count;
	int number;

	Temp();
	Temp(Type* type);
	string ToString();

	~Temp();
};

/// ����
//////////////////////////////////////////////////////////////////////////

class Constant : public Expr {
public:
	Constant();
	Constant(double value);
	Constant(int value);
	Constant(Token* token, Type* type);

	void jumping(int t, int f);

	~Constant();
};

/// �߼������
//////////////////////////////////////////////////////////////////////////

class Logical : public Expr {
public:
	Expr *l_expr, *r_expr;
	Logical();
	Logical(Token* token, Expr* l_expr, Expr* r_expr);

	virtual Type* check(Type* l_type, Type* r_type);
	Expr* gen();
	string ToString();

	~Logical();
};

/// ������
//////////////////////////////////////////////////////////////////////////

class Or : public Logical {
public:
	Or();
	Or(Token* token, Expr* l_expr, Expr* r_expr);
	
	
	void jumping(int t, int f);

	~Or();
};

/// ������
//////////////////////////////////////////////////////////////////////////

class And : public Logical {
public:
	And();
	And(Token* token, Expr* l_expr, Expr* r_expr);

	void jumping(int t, int f);

	~And();
};

/// ������
//////////////////////////////////////////////////////////////////////////

class Not : public Logical {
public:
	Not();
	Not(Token* token, Expr* r_expr);

	void jumping(int t, int f);
	string ToString();
};

/// ��ϵ�����
//////////////////////////////////////////////////////////////////////////

class Rel : public Logical {
public:
	Rel();
	Rel(Token* token, Expr* l_expr, Expr* r_expr);

	Type* check(Type* l_type, Type* r_type);
	void jumping(int t, int f);

	~Rel();
};

#endif