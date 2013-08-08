#ifndef _H_SYMBOLTABLE
#define _H_SYMBOLTABLE

#include "Symbol.h"

class SymbolTable
{
public:
	static int _nextId;					// ��һ��Id

	SymbolTable* father;				// ����
	map<string, Symbol*> symbolMap;		// ����Map
	vector<SymbolTable*> son;			// �������ű�
	int sonIndex;						// ��һ��Ҫ��ȡ�ķ��ű�
	int tableId;						// ���ű�Id���������ֲ�ͬ�ķ��ű�
	
	SymbolTable();
	explicit SymbolTable(SymbolTable* father);
	explicit SymbolTable(const SymbolTable& rhs);
	

	void AddSymbol(Symbol* symbol);		// ���һ���·���=
	void ResetSymbolTableStatus();		// �������з��ű��״̬
	void ResetSymbolTableValue();		// �������з��ű�ĳ�ʼ����
	SymbolTable* MakeNewSymbolTable();	// ����һ���µķ��ű�
	SymbolTable* GetNextSymbolTable();	// �����һ�����ű�
	Symbol* GetSymbol(string name);		// ���һ������

	Symbol* _FindSymbol(SymbolTable* symTable,string name);	// ��ָ�����ű�������ָ�����Ƶķ���
	SymbolTable* _FindSymbolTable(int id);					// ����ָ����IdѰ�Ҹ÷��ű�����ͬId�ķ��ű�����

	~SymbolTable();

private:
	SymbolTable* operator= (const SymbolTable& ths);		// ��ֹ��ֵ���ƹ���
};

#endif // !_H_SYMBOLTABLE
