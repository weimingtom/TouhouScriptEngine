#include "Parser.h"

Parser::Parser():lexer(NULL)
{

}

Parser::Parser(Lexer* lexer):lexer(lexer)
{
	fileManager = 0;
	fileManager = fileManager->Instance();
}

void Parser::Move()
{
	look = lexer->ScanWord();
}

void Parser::Retrack(int num)
{
	look = lexer->RetrackWord(num);
}

void Parser::Match(int t, int id)
{
	if (look == NULL)
		return ;

	if (look->tag == t)
	{
		Move();
	}
	else
	{
		Error("ƥ�����");
	}
}

void Parser::Error(string s)
{
	cout << "Error: " + s << endl;
}

void Parser::ScriptAnalysis()
{
	ScriptHeader();		// �����ű�ͷ�������������ű�����
	Varible();			// ������������

	while (FuncHeader() != -1)		// ����ͷ����
	{
		Block();			// ���������
	}
}

void Parser::ScriptHeader()
{
	Move();
	string str = look->ToString();


	while (((Word*)look)->lexeme[0] == '#')
	{
		Move();
		// TO-DO: �����Ӧ������

		cout << look->ToString() << endl;
		Move();
	}

	if (look->tag == STAGEMAIN)		// �ؿ��ű�
	{
		
	}

	cout << look->ToString() << endl;
}

void Parser::Varible()
{
	Move();

	while (look->tag == VARTK)
	{
		
	}
}

int Parser::FuncHeader()
{
	return 1;
}

Stmt* Parser::Block()
{
	return NULL;
}