#ifndef _H_SYMBOL
#define _H_SYMBOL

#include "stdafx.h"

// Symbol������typeȡֵ
	
#define DOUBLE	0		// ����������
#define INT		1		// ��������
#define STRING	2		// �ַ�������
#define BOOL	3		// ��������
#define VOID	4		// ������

class Symbol
{
public:
	string name;		// ������
	int type;			// ��������
	int kind;			// ��������
	double value;		// ����ֵ

	Symbol();
	Symbol(string name, int type, int kind);

	~Symbol();
};

#endif // !_H_SYMBOL
