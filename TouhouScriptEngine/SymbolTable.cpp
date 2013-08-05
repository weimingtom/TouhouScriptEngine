#include "SymbolTable.h"

int SymbolTable::_nextId = 0;

SymbolTable::SymbolTable():father(NULL),sonIndex(-1),tableId(-1)
{

}

SymbolTable::SymbolTable(SymbolTable* father):father(father),sonIndex(-1),tableId(-1)
{

}

SymbolTable* SymbolTable::MakeNewSymbolTable()
{
	SymbolTable* symTable = new SymbolTable(this);

	symTable->tableId = _nextId;
	_nextId++;

	son.push_back(symTable);

	return symTable;
}

void SymbolTable::ResetSymbolTableStatus()
{
	sonIndex = -1;

	for (int index = 0; index < son.size(); ++index)
	{
		son[index]->ResetSymbolTableStatus();
	}
}

void SymbolTable::ResetSymbolTableValue()
{
	for (map<string, Symbol*>::iterator itor = symbolMap.begin(); itor != symbolMap.end(); ++itor)
	{
		Symbol* symbol = (*itor).second;

		// �Ժ���չ���ͺ��ٲ���
		if (true || symbol->type == TYPE_DOUBLE)
			symbol->value = 0;
	}

	for (vector<SymbolTable*>::iterator itor = son.begin(); itor != son.end(); ++itor)
		(*itor)->ResetSymbolTableValue();
}

SymbolTable* SymbolTable::GetNextSymbolTable()
{
	++sonIndex;

	if (sonIndex < son.size())
	{
		return son[sonIndex];
	}
	else
	{
		return father;
	}
}

void SymbolTable::AddSymbol(Symbol* symbol)
{
	if (symbol != NULL)
		symbolMap.insert(make_pair(symbol->name, symbol));
}

Symbol* SymbolTable::GetSymbol(string name)
{
	SymbolTable* nowSym = this;
	Symbol* retSym = NULL;

	while (nowSym != NULL && (retSym = _FindSymbol(nowSym, name)) == NULL) {
		nowSym = nowSym->father;
	}

	return retSym;
}

Symbol* SymbolTable::_FindSymbol(SymbolTable* symTable, string name)
{
	map<string, Symbol*>::iterator itor = symTable->symbolMap.find(name);
	
	if (itor == symTable->symbolMap.end())
	{
		return NULL;
	}
	else
	{
		return itor->second;
	}
}

SymbolTable* SymbolTable::_FindSymbolTable(int id) 
{
	if (tableId == id)
		return this;

	for (int idx = 0; idx < son.size(); ++idx)
	{
		SymbolTable* tempTable = son[idx]->_FindSymbolTable(id);

		if (tempTable != NULL)
			return tempTable;
	}

	return NULL;
}

SymbolTable::~SymbolTable()
{
	for (map<string, Symbol*>::iterator itor = symbolMap.begin(); itor != symbolMap.end(); )
		itor = symbolMap.erase(itor);
	symbolMap.clear();

	for (vector<SymbolTable*>::iterator itor = son.begin(); itor != son.end(); )
	{
		if (*itor != NULL)
		{
			delete *itor;
			*itor = NULL;
			itor = son.erase(itor);
		}
		else
		{
			itor++;
		}
	}
	son.clear();
}