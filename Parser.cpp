#include "Parser.h"

Parser::Parser():lexer(NULL)
{

}

Parser::Parser(Lexer* lexer):lexer(lexer),fileManager(0),scriptMgr(0)
{
	fileManager = fileManager->Instance();
	scriptMgr = scriptMgr->Instance();
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
	// �����µĽű�����
	THScript* scriptData = new THScript();
	scriptData->fileName = fileManager->fileName;
	scriptMgr->AddTHScript(scriptData);

	ScriptHeader();					// �����ű�ͷ�������������ű�����
	Varible();						// ����ͷ����������

	while (FuncHeader() != -1)		// ����ͷ����
	{
		Block();					// ���������
	}
}

void Parser::ScriptHeader()
{
	Move();
	string str = look->ToString();
	string varStr = ((Word*)look)->lexeme;
	
	while (varStr[0] == '#')		// ��ȡ�ű�ͷ������
	{
		Move();
		scriptMgr->lastScript->SetValue(varStr, look->ToString());
		Move();
		varStr = ((Word*)look)->lexeme;
	}


	if (scriptMgr->lastScript->touhouScript == "Stage")		// ��֤��������ű�����һ����
		Match(STAGEMAIN, -1);
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