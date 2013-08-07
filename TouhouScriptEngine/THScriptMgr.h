#ifndef _H_THSCRIPTMGR
#define _H_THSCRIPTMGR

#include "stdafx.h"
#include "THScript.h"
#include "ScriptTrans.h"

class THScriptMgr
{
public:
	THScript* lastScript;					// ���������ӵĽű�
	Translator* lastTranslator;				// ���������ӵķ�����	
	THScriptMgr* Instance();
	
	void AddTHScript(THScript* script);					// ���TH�ű��ļ�
	THScript* GetTHScriptByFileName(string fileName);	// ���ݽű��ļ�����ȡָ���ű�

protected:
	THScriptMgr();

private:
	map<string, THScript*> _scriptMap;
	static THScriptMgr* _instance;
};

#endif // !_H_THSCRIPTMGR
