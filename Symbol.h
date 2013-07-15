#ifndef _H_SYMBOL
#define _H_SYMBOL

#include "stdafx.h"

// Symbol������typeȡֵ
	
#define TYPE_DOUBLE	0		// ����������
#define TYPE_INT	1		// ��������
#define TYPE_STRING	2		// �ַ�������
#define TYPE_BOOL	3		// ��������
#define TYPE_VOID	4		// ������

// Symbol������kindȡֵ
#define KIND_CONST	20		//����
#define KIND_VAR	21		//����
#define KIND_TVAR	22		//��ʱ����
#define	KIND_PROC	23		//����ͷ��
#define KIND_FUNC	24		//����ͷ��

class Symbol
{
public:
	string name;		// ������
	int type;			// ��������
	int kind;			// ��������
	double value;		// ����ֵ

	Symbol();
	Symbol(string name, int type, int kind);
	Symbol(string name, int type, int kind, double value);
	~Symbol();
};

#endif // !_H_SYMBOL
