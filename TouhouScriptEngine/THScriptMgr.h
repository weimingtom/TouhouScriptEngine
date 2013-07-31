#ifndef _H_THSCRIPTMGR
#define _H_THSCRIPTMGR

#include "stdafx.h"
#include "THScriptFull.h"

class THScriptMgr
{
public:
	map<string, THScriptFull*> scriptMap;
	THScriptFull* lastScript;					// ���������ӵĽű�

	THScriptMgr* Instance();
	
	void AddTHScript(THScriptFull* script);					// ���TH�ű���
	THScriptFull* GetTHScriptByFileName(string fileName);	// ���ݽű��ļ�����ȡָ���ű�
	THScriptFull* GetTHScriptByTitle(string title);			// ���ݽű���Ŀ��ȡָ���ű�

protected:
	THScriptMgr();

private:
	static THScriptMgr* _instance;
};

#endif // !_H_THSCRIPTMGR
