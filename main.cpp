#include "stdafx.h"
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"

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
	
	return 0;
}