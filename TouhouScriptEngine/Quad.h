#ifndef _H_QUAD
#define _H_QUAD

#include "stdafx.h"

class Quad 
{
public:
	string op, arg1, arg2, obj;		// ��Ԫʽ���ĸ�����
	string lineID;					// ��Ԫʽ��Ӧ����ת�к�

	Quad();
	Quad(string v_op, string v_arg1, string v_arg2, string v_obj);
};

#endif // !_H_QUAD
