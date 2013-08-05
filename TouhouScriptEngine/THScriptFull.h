#ifndef _H_THSCRIPTFULL
#define _H_THSCRIPTFULL

#include "THScript.h"

class THScriptFull : public THScript
{
public:
	vector<string> scriptStream;	// �ű��ļ������ű���Ԫʽ�γɺ��û������
	int _streamIdx;				// �ű��ļ���λ��
	QuadGroup* _lastGroup;		// ���һ�β����Ľű��飬�����ͷ�
	int _tableId;				// ��ǰ��������

	THScriptFull();
	THScriptFull(const THScriptFull& rhs);
	THScriptFull& operator=(const THScriptFull& rhs);
	~THScriptFull();

	void	TranslateScript();			// ����ű��м���
	void	AddToStream(string str);	// ����ַ�������������

	string	_NextWord();				// ��ýű��ļ�������һ����
	string	_RetrackWord(int num);		// �˻ؽű��ļ���֮ǰ��ָ��������Ŀ
	void	_AddTempToTable(string name);	// �����ʱ���������ű���ȥ
	void	_MakeNewQuad(string op, string arg_1, string arg_2, string obj, string lineID);		// �½�һ��ű�		
	
};

#endif // !_H_THSCRIPTFULL
