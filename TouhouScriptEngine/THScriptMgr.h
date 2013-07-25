#ifndef _H_THSCRIPTMGR
#define _H_THSCRIPTMGR

#include "stdafx.h"
#include "THScript.h"

class THScriptMgr
{
public:
	map<string, THScript*> scriptMap;
	THScript* lastScript;					// ���������ӵĽű�

	THScriptMgr* Instance();
	
	void AddTHScript(THScript* script);					// ���TH�ű���
	THScript* GetTHScriptByFileName(string fileName);	// ���ݽű��ļ�����ȡָ���ű�
	THScript* GetTHScriptByTitle(string title);			// ���ݽű���Ŀ��ȡָ���ű�

protected:
	THScriptMgr();

private:
	static THScriptMgr* _instance;
};

#endif // !_H_THSCRIPTMGR
