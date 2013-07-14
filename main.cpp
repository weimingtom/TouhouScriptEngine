#include "stdafx.h"
#include "Lexer.h"
#include "Parser.h"

int main()
{
	FileManager* fileManager = 0;
	fileManager = fileManager->Instance();

	Lexer* lexer = new Lexer();

	// ��ȡ�����дʷ�����
	fileManager->ReadCodeFile("test.txt");
	lexer->MakeWordStream();

	cout << "---------------------" << endl;

	Parser* parser = new Parser(lexer);
	parser->ScriptAnalysis();



	return 0;
}