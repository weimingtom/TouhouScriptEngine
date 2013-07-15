#ifndef _H_SYMBOLTABLE
#define _H_SYMBOLTABLE


#include "Symbol.h"

class SymbolTable
{
public:
	SymbolTable* father;				// ����
	map<string, Symbol*> symbolMap;		// ����Map
	vector<SymbolTable*> son;			// �������ű�
	int sonIndex;						// ��һ��Ҫ��ȡ�ķ��ű�
	
	SymbolTable();
	SymbolTable(SymbolTable* father);

	void AddSymbol(Symbol* symbol);		// ���һ���·���=
	void ResetSymbolTableStatus();		// �������з��ű��״̬
	SymbolTable* MakeNewSymbolTable();	// ����һ���µķ��ű�
	SymbolTable* GetNextSymbolTable();	// �����һ�����ű�
	Symbol* GetSymbol(string name);		// ���һ������

	Symbol* _FindSymbol(SymbolTable* symTable,string name);	// ��ָ�����ű�������ָ�����Ƶķ���

	~SymbolTable();
	
};

#endif // !_H_SYMBOLTABLE
