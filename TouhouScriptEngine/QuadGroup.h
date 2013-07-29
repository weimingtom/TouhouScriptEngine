#ifndef _H_QUADGROUP
#define _H_QUADGROUP

#include "Quad.h"

class QuadGroup
{
public:
	string type;				// �ű�������
	vector<Quad*> quadList;		// ��Ԫʽ��
	int nowQuad;				// ��ǰ����ִ�еĽű����

	QuadGroup();
	QuadGroup(string v_type);
	void AddQuad(Quad* quad);	// �����Ԫʽ
	
	~QuadGroup();
};

#endif // !_H_QUADGROUP
