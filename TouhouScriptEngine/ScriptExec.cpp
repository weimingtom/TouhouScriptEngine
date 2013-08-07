#include "THScript.h"
#include "ScriptExec.h"
#include "stdafx.h"

class ScriptExec_Impl
{
public:
	ScriptExec_Impl(THScript* script):_script(script)
	{
		_initialize();
	}

private:
	THScript* const	_script;		// �����õĽű��������ɸı�
	SymbolTable*	_symRoot;	// ִ��������ı����� 

	// ��ʼ��Exec
	void _initialize()
	{
		_symRoot = new SymbolTable(*_script->symRoot);	// ��ûд���ƹ���= = ��������� �Ҿ�����������copy�Ļ�����Clone()��
	}
};

inline void Run()
{

}

ScriptExec::ScriptExec(THScript* script)
{
	_pImpl = new ScriptExec_Impl(script);
}

ScriptExec::~ScriptExec()
{
	delete _pImpl;
	_pImpl = NULL;
}