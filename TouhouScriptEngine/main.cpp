#include "stdafx.h"
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "THScriptMgr.h"
#include "Object.h"
#include "ScriptExec.h"
#include "Point2d.h"
#include "Vector2d.h"


int main()
{
	FileMgr* fileManager = 0;
	fileManager = fileManager->Instance();

	Lexer* lexer = new Lexer();

	// ��ȡ�����дʷ�����
	fileManager->ReadCodeFile("test.ths");
	lexer->MakeWordStream();

	cout << "---------------------" << endl;

	Parser* parser = new Parser(lexer);
	parser->ScriptAnalysis();
	
	THScriptMgr* scriptMgr = 0;
	scriptMgr = scriptMgr->Instance();

	// ת��Ϊ��ִ�нű�
	ScriptExec* scriptexec = new ScriptExec(scriptMgr->GetTHScriptByFileName("test.ths"));
	scriptexec->Run();

	return 0;
}